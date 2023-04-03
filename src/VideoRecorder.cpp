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

VideoRecorder::VideoRecorder(const CircularBuffer<cv::Mat> &buffer, int frame_rate)
        : lead_up_buffer(buffer) {

    video_writer = cv::VideoWriter(generate_timestamped_filename(),
                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                   frame_rate,
                                   cv::Size(640, 480));
}

VideoRecorder::~VideoRecorder() {
    video_writer.release();
}

void VideoRecorder::write_frames(bool &recording, std::queue<cv::Mat> &shared_queue,
                                 std::mutex &mutex_lock, std::condition_variable &recording_updated,
                                 std::condition_variable &queue_updated) {

    std::cout << lead_up_buffer.get_capacity() << std::endl;
    int a = 1;
    while (lead_up_buffer.get_size() > 0) {
        video_writer.write(lead_up_buffer.pop());
        std::cout << a << std::endl;
        a++;
    }

    while (1) {
        // Critical Section
        std::unique_lock<std::mutex> unique_lock{mutex_lock};
        queue_updated.wait(unique_lock, [&] {
            return shared_queue.empty();
        });

        video_writer.write(shared_queue.front());
        shared_queue.pop();
    }

//    // Critical Section
//    std::unique_lock<std::mutex> unique_lock{mutex_lock};
//    recording_updated.wait(unique_lock, [&] {
//        return !recording;
//    });

}


