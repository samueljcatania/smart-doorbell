/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Camera.h:
 *
 */

#ifndef INC_33307B_GROUP_17_PROJECT_CAMERA_H
#define INC_33307B_GROUP_17_PROJECT_CAMERA_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "../lib/opencv4/opencv2/opencv.hpp"


class Camera {
private:
    cv::VideoCapture video_capture;
    cv::Mat first_frame, average_frame;

public:
    Camera();

    ~Camera();

    void detectMotion(std::queue<char> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var);
};

#endif //INC_33307B_GROUP_17_PROJECT_CAMERA_H
