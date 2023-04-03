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
//    cv::VideoWriter video_writer = cv::VideoWriter(generateTimestampedFilename(),
//                                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
//                                                   15,
//                                                   cv::Size(640, 480));
    cv::VideoWriter video_writer = cv::VideoWriter("TESToutput1234_21.avi",
                                                   cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                                                   15,
                                                   cv::Size(640, 480));
    cv::Mat average_frame;
    CircularBuffer<cv::Mat> lead_up_buffer = CircularBuffer<cv::Mat>(15 * 10);
    std::chrono::time_point<std::chrono::system_clock> last_motion_time, recent_motion_time;

    FaceDetector face_detector;

public:
    Camera();

    ~Camera();

    void detect_motion(std::queue<char> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var);

    // Function to generate the timestamped filename
    static std::string generateTimestampedFilename() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << "../recordings/" << std::put_time(std::localtime(&now_c), "%Y%m%d_%H%M%S") << ".avi";
        return ss.str();
    }

};

#endif // GROUP_17_CAMERA_HPP
