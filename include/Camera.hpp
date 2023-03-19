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

#include <queue>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>

class Camera {
private:
    cv::VideoCapture video_capture;
    cv::VideoWriter video_writer;
    cv::Mat average_frame;

public:
    Camera();

    ~Camera();

    void detectMotion(std::queue<char> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var);
};

#endif // GROUP_17_CAMERA_HPP
