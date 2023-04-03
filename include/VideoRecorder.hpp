/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Friday, March 17, 2023
 *
 * Description of Camera.cpp:
 *
 */

#ifndef GROUP_17_VIDEORECORDER_HPP
#define GROUP_17_VIDEORECORDER_HPP

#include <chrono>
#include <ctime>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>

#include "CircularBuffer.hpp"

class VideoRecorder {
private:
    CircularBuffer<cv::Mat> lead_up_buffer;
    cv::VideoWriter video_writer;

    static std::string generate_timestamped_filename();

public:
    // Constructor for VideoRecorder - creates a new VideoRecorder object.
    explicit VideoRecorder(const CircularBuffer<cv::Mat> &buffer, int frame_rate);

    // Destructor
    ~VideoRecorder();

    void write_frames(bool &recording, std::queue<cv::Mat> &shared_queue,
                      std::mutex &mutex_lock, std::condition_variable &recording_updated,
                      std::condition_variable &queue_updated);
};


#endif // GROUP_17_VIDEORECORDER_HPP
