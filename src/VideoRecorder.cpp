/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Friday, March 17, 2023
 *
 * Description of Camera.cpp:
 *
 */

#include <opencv2/core.hpp>
#include "../include/VideoRecorder.hpp"

// Function to generate the timestamped filename
std::string VideoRecorder::generate_timestamped_filename() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << "../recordings/" << std::put_time(std::localtime(&now_c), "%Y%m%d_%H%M%S") << ".avi";

    return ss.str();
}

VideoRecorder::VideoRecorder(int frame_rate) {
    video_writer = cv::VideoWriter(generate_timestamped_filename(),
                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                   frame_rate,
                                   cv::Size(640, 480));
}

VideoRecorder::~VideoRecorder() {
    video_writer.release();
}

void VideoRecorder::write_frames(bool &recording, std::queue<cv::Mat> &shared_queue,
                                 std::mutex &recorder_lock, CircularBuffer<cv::Mat> &shared_lead_up_buffer,
                                 std::condition_variable &recording_updated,
                                 std::condition_variable &queue_updated) {
//    // Critical Section
//    std::unique_lock<std::mutex> unique_lock{recorder_lock};
//    recording_updated.wait(unique_lock, [&] {
//        return !recording;
//    });

    std::cout << shared_lead_up_buffer.get_capacity() << std::endl;
    std::cout << shared_lead_up_buffer.get_size() << std::endl;

    int a = 1;
    while (lead_up_buffer.get_size() > 0) {
        video_writer.write(lead_up_buffer.pop());
        std::cout << a << std::endl;
        a++;
    }

    std::cout << "IN DA THREADDDD" << std::endl;

    while (1) {

//        // Critical Section
//        std::unique_lock<std::mutex> unique_lock{recorder_lock};
////        queue_updated.wait(unique_lock, [&] {
////            return shared_queue.empty();
////        });
//        queue_updated.wait(unique_lock);


        // Critical Section
        std::unique_lock<std::mutex> unique_lock{recorder_lock};
        recording_updated.wait(unique_lock, [&] {
            return !recording;
        });

        std::cout << "its false now homie" << std::endl;
//
//
//        video_writer.write(shared_queue.front());
//        shared_queue.pop();
//        std::cout << "IN DA LOOOOp" << std::endl;

    }

//    // Critical Section
//    std::unique_lock<std::mutex> unique_lock{mutex_lock};
//    recording_updated.wait(unique_lock, [&] {
//        return !recording;
//    });


}


