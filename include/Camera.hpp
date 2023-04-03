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

/**
 * @brief Camera class monitors the camera for motion, and also faces.
 *
 * Camera starts the hardware camera, and then performs calculations to see
 * if motion has been detected. Camera is also able to detect faces.
 *
 * @author Samuel Catania
 *
 */

class Camera {
private:
    /**
     * video_capture captures frames from the hardware camera.
     */
    cv::VideoCapture video_capture;

    /**
     * average_frame is used to determine if recent changes in the camera
     * mean that there is motion.
     */
    cv::Mat average_frame;

    /**
     * lead_up_buffer stores 15 seconds of video recorded. It writes these frames
     * into the video recording when motion is detected, so 15 seconds prior
     * to motion detection are also recorded.
     */
    CircularBuffer<cv::Mat> lead_up_buffer = CircularBuffer<cv::Mat>(0);

    /**
     * last_motion_time and last_face_detection_time store the time that each was
     * last detected by Camera.
     */
    std::chrono::time_point<std::chrono::system_clock> last_motion_time, last_face_detection_time;

    /**
     * face_detector is an object that scans frames to see if there are faces
     * being captured by the camera.
     */
    FaceDetector face_detector;

    /**
     * tracks frame rate of the camera
     */
    int frame_rate;

    /**
     * tracks how many faces were detected by the camera last.
     */
    int last_number_of_faces_detected = 0;

    /**
     * boolean to indicate whether motion has been detected.
     */
    bool motion_detected = false;

    /**
     * Function that measures the frame rate of the camera.
     *
     * @return calculated camera frame rate.
     */
    int measure_camera_frame_rate();

public:
    /**
     * Constructor for Camera. Creates a new Camera object.
     */
    Camera();

    /**
     * Destructor for Camera. Destroys the camera object.
     */
    ~Camera();

    /**
     * detectMotion performs calculations to determine if there is motion.
     *
     * @param recording whether the camera is currently recording.
     * @param shared_queue Shared queue shares captured frames between Camera and Doorbell.
     * @param queue_lock mutex lock to control access to the queue variable.
     * @param camera_lock mutex lock to control access to the camera variable.
     * @param buffer_lock mutex lock control access to the shared_lead_up_buffer.
     * @param shared_lead_up_buffer stores 15 seconds worth of frames before motion is detected.
     * @param recording_updated conditional variable to track whether or not recording boolean has been changed.
     * @param buffer_updated conditional variable to track if a frame was added to the buffer
     * @param queue_updated conditional variable to track if a frame was added to the queue.
     */
    void detect_motion(bool &recording, std::queue<cv::Mat> &shared_queue, std::mutex &queue_lock,
                       std::mutex &camera_lock, std::mutex &buffer_lock, CircularBuffer<cv::Mat> &shared_lead_up_buffer,
                       std::condition_variable &recording_updated, std::condition_variable &buffer_updated,
                       std::condition_variable &queue_updated);

    /**
     * This function returns the frame rate of the connected hardware camera.
     *
     * @return the calculated frame rate.
     */
    int get_frame_rate() const;

};

#endif // GROUP_17_CAMERA_HPP
