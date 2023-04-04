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

/**
 * @brief The video recorder class contains functionality to record the live camera feed
 *
 * VideoRecorder uses multithreading for the video recording process. There are methods
 * to take live feed frames and generate a video using OpenCV's VideoWriter. The video
 * is overlayed with additional details, and the recording process will terminate
 * when VideoRecorder is terminated.
 *
 * @author Samuel Catania
 */


class VideoRecorder {
private:
    CircularBuffer<cv::Mat> lead_up_buffer = CircularBuffer<cv::Mat>(0);
    cv::VideoWriter video_writer;

    /**
     * @brief Create a timestamp for the recorded video
     *
     * A timestamp corresponding to the current time is created. The recorded video will
     * be titled according to this timestamp, in the form "YYYYMMDD_HHMMSS", where YYYY is the year
     * MM is the month, DD is the day, HH is hour, MM is minutes, and SS is seconds.
     *
     * @return
     */
    static std::string generate_timestamped_filename();

public:
    /**
     * @brief Constructor for the VideoRecorder class
     *
     * This function will create a new VideoRecorder object and then begin recording the camera live feed.
     *
     * @param frame_rate The number of frames to save per second
     */
    explicit VideoRecorder(int frame_rate);

    /**
     * @brief Destructor for the VideoRecorder class
     *
     * This function will terminate and destroy the VideoRecorder object. When this occurs, the recording of the
     * live video also terminates, but the live video and other camera functionalities continue operating.
     *
     */
    ~VideoRecorder();

    /**
     * @brief This function writes the collection of frames which eventually becomes a video
     *
     * This method will continue writing individual frames to our output video file; as these consecutive frames
     * come together to form a video. This method will begin grabbing frames after the creation of a VideoRecorder
     * object, and will stop when the shared queue of frames is empty, which occurs when VideoRecorder is destroyed.
     *
     *
     * @param recording Boolean that represents the state of the camera, recording or not recording
     * @param shared_queue The collection of captured live-feed frames
     * @param queue_lock TODO
     * @param camera_lock TODO
     * @param buffer_lock TODO
     * @param shared_lead_up_buffer TODO
     * @param recording_updated TODO
     * @param buffer_updated Boolean representing the TODO
     * @param queue_updated TODO
     */
    void write_frames(bool &recording, std::queue<cv::Mat> &shared_queue, std::mutex &queue_lock,
                      std::mutex &camera_lock, std::mutex &buffer_lock,
                      CircularBuffer<cv::Mat> &shared_lead_up_buffer,
                      std::condition_variable &recording_updated, std::condition_variable &buffer_updated,
                      std::condition_variable &queue_updated);
};


#endif // GROUP_17_VIDEORECORDER_HPP
