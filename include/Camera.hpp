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
#include <opencv2/core/utils/logger.hpp>

#include "FaceDetector.hpp"
#include "CircularBuffer.hpp"
#include "WebApp.hpp"

class Camera {
private:
    cv::VideoCapture video_capture;
    cv::Mat average_frame;
    CircularBuffer<cv::Mat> lead_up_buffer = CircularBuffer<cv::Mat>(15 * 10);
    std::chrono::time_point<std::chrono::system_clock> camera_start_time, last_motion_time;

    FaceDetector face_detector;

public:
    Camera();

    ~Camera();

    void detect_motion(std::queue<cv::Mat> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var);
};

#endif // GROUP_17_CAMERA_HPP
