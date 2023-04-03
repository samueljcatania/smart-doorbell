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

VideoRecorder::VideoRecorder(const CircularBuffer<cv::Mat> &buffer)
        : lead_up_buffer(buffer) {

    video_writer = cv::VideoWriter(generate_timestamped_filename(),
                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                   15,
                                   cv::Size(640, 480));
}

VideoRecorder::~VideoRecorder() {
    video_writer.release();
}

void VideoRecorder::write_frames(std::queue<cv::Mat> &shared_queue, std::mutex &mutex_lock,
                                 std::condition_variable &cond_var) {
    std::cout << lead_up_buffer.capacity() << std::endl;
    int a = 1;
    while (lead_up_buffer.size() > 0) {
        video_writer.write(lead_up_buffer.pop());
        std::cout << a << std::endl;
        a++;
    }

}


