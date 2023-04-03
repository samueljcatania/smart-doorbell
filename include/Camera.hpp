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
#include "VideoRecorder.hpp"
#include "CircularBuffer.hpp"
#include "WebApp.hpp"

class Camera {
private:
    cv::VideoCapture video_capture;
    cv::Mat average_frame;
    CircularBuffer<cv::Mat> lead_up_buffer = CircularBuffer<cv::Mat>(0);
    std::chrono::time_point<std::chrono::system_clock> last_motion_time, last_face_detection_time;
    FaceDetector face_detector;
    int frame_rate;
    int last_number_of_faces_detected = 0;
    bool motion_detected = false;

    int measure_camera_frame_rate();

public:
    Camera();

    ~Camera();

    void detect_motion(bool &recording, std::queue<cv::Mat> &shared_queue, std::mutex &queue_lock,
                       std::mutex &camera_lock, std::mutex &buffer_lock, CircularBuffer<cv::Mat> &shared_lead_up_buffer,
                       std::condition_variable &recording_updated, std::condition_variable &buffer_updated,
                       std::condition_variable &queue_updated);

    int get_frame_rate() const;

};

#endif // GROUP_17_CAMERA_HPP
