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
#include <chrono>
#include <thread>
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

void VideoRecorder::write_frames(bool &recording, std::queue<cv::Mat> &shared_queue, std::mutex &queue_lock,
                                 std::mutex &recorder_lock, std::mutex &buffer_lock,
                                 CircularBuffer<cv::Mat> &shared_lead_up_buffer,
                                 std::condition_variable &recording_updated, std::condition_variable &buffer_updated,
                                 std::condition_variable &queue_updated) {

//    // Critical Section
//    std::unique_lock<std::mutex> buffer_unique_lock{buffer_lock};
//
//    std::cout << shared_lead_up_buffer.get_capacity() << std::endl;
//    std::cout << shared_lead_up_buffer.get_size() << std::endl;
//
//    while (shared_lead_up_buffer.get_size() > 0) {
//        video_writer.write(shared_lead_up_buffer.pop());
////        std::this_thread::sleep_for(std::chrono::milliseconds(2000000));
//    }
//
//    buffer_unique_lock.unlock();

    // Critical Section
    std::unique_lock<std::mutex> recorder_unique_lock{recorder_lock};
    recording_updated.wait(recorder_unique_lock, [&] {
        return recording;
    });

    std::cout << "IN DA THREADDDD" << std::endl;

    while (recording) {

        recorder_unique_lock.unlock();

        std::cout << "After unlock" << std::endl;
         std::this_thread::sleep_for(std::chrono::seconds (2));

//        // Critical Section
//        std::unique_lock<std::mutex> queue_unique_lock{queue_lock};
//        queue_updated.wait(queue_unique_lock, [&] {
//            return shared_queue.empty();
//        });
//
//        video_writer.write(shared_queue.front());
//        shared_lead_up_buffer.pop();
//
//        queue_unique_lock.unlock();


        return;
//
//        std::cout << "its false now homie" << std::endl;
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


