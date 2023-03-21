/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Camera.hpp:
 *
 */

#ifndef GROUP_17_CAMERA_HPP
#define GROUP_17_CAMERA_HPP

#include <chrono>
#include <ctime>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>
#include "../include/CircularBuffer.hpp"

class Camera {
private:
    cv::VideoCapture video_capture;
    cv::VideoWriter video_writer = cv::VideoWriter("../recordings/output.avi",
                                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                                   15,
                                                   cv::Size(640, 480));
    cv::Mat average_frame;
    CircularBuffer<cv::Mat> lead_up_buffer = CircularBuffer<cv::Mat>(400);
    std::chrono::time_point<std::chrono::system_clock> last_motion_time, recent_motion_time;

public:
    Camera();

    ~Camera();

    void detectMotion(std::queue<char> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var);
};

#endif // GROUP_17_CAMERA_HPP
