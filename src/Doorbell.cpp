/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Doorbell.cpp:
 *
 */

#include <gtkmm/application.h>
#include <atomic>

#include "../include/Doorbell.hpp"

Doorbell::Doorbell(char **argv) {
    // Turn off OpenCV console logging output
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    while (1) {
        std::atomic<bool> show_raw_camera{false};
        std::atomic<bool> show_threshold_camera{false};
        std::atomic<bool> show_delta_camera{false};

        camera_thread = std::thread(&Camera::detect_motion,
                                    camera,
                                    std::ref(show_raw_camera),
                                    std::ref(show_threshold_camera),
                                    std::ref(show_delta_camera),
                                    std::ref(recording),
                                    std::ref(shared_queue),
                                    std::ref(queue_lock),
                                    std::ref(camera_lock),
                                    std::ref(buffer_lock),
                                    std::ref(shared_lead_up_buffer),
                                    std::ref(recording_updated),
                                    std::ref(buffer_updated),
                                    std::ref(queue_updated),
                                    std::ref(camera_stream_updated));

        //recorder_thread
        master_thread = std::thread(&Doorbell::thread_manager, this);

        open_window(argv, &show_raw_camera);

        while (1) {
            std::unique_lock<std::mutex> queue_unique_lock{queue_lock};
            camera_stream_updated.wait(queue_unique_lock);

            open_window(argv, &show_raw_camera);

            queue_unique_lock.unlock();
        }

        camera_thread.join();
        master_thread.join();
    }
}

Doorbell::~Doorbell() {
    cv::destroyAllWindows();
}

int Doorbell::open_window(char **argv, std::atomic<bool> *show_raw_camera) {
    int argc = 1;

    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    DisplayWindow display_window(show_raw_camera);

    // Shows the window and returns when it is closed
    return app->run(display_window);
}

void Doorbell::thread_manager() {
    cv::Mat frame;

    while (1) {
        // Critical Section
        std::unique_lock<std::mutex> unique_lock{camera_lock};
        recording_updated.wait(unique_lock, [&] {
            return recording;
        });

        unique_lock.unlock();

        create_video_recorder_thread();
    }
}

void Doorbell::create_video_recorder_thread() {
    VideoRecorder video_recorder(camera.get_frame_rate());

    recorder_thread = std::thread(&VideoRecorder::write_frames,
                                  video_recorder,
                                  std::ref(recording),
                                  std::ref(shared_queue),
                                  std::ref(queue_lock),
                                  std::ref(camera_lock),
                                  std::ref(buffer_lock),
                                  std::ref(shared_lead_up_buffer),
                                  std::ref(recording_updated),
                                  std::ref(buffer_updated),
                                  std::ref(queue_updated));

    recorder_thread.join();
}
