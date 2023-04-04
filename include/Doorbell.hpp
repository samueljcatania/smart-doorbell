/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Doorbell.h:
 *
 */

#ifndef GROUP_17_DOORBELL_HPP
#define GROUP_17_DOORBELL_HPP

#include <thread>

#include "Camera.hpp"
#include "DisplayWindow.hpp"


/**
 * @brief Doorbell class holds threading functionalities and GUI methods
 *
 * Doorbell has methods to create threads, as well as the thread manager.
 * This threading is necesary to make use of various processes running consecutively.
 * There are also the initialization and cleanup methods for the GUI.
 *
 * @author Samuel Catania
 *
 */
class Doorbell {
private:
    /**
     * Constructor for camera.
     */
    Camera camera;

    /**
     * variable tracking whether the camera is currently recording
     */
    bool recording = false;

    /**
     * shared queue for camera frames
     */
    std::queue<cv::Mat> shared_queue;

    /**
     * lead up buffer storing 15 seconds worth of frames prior to motion detection
     */
    CircularBuffer<cv::Mat> shared_lead_up_buffer = CircularBuffer<cv::Mat>(0);

    /**
     * mutex locks for controlling access to the queue, the camera, and the buffer
     */
    std::mutex queue_lock, camera_lock, buffer_lock;

    /**
     * Condition variables for tracking whether the recordings, queue or buffer were updated
     */
    std::condition_variable recording_updated, queue_updated, buffer_updated, camera_stream_updated;

    /**
     * camera_thread operates the camera, recorder_thread manages recording to a file, and master_thread
     * is the main thread of the program.
     */
    std::thread camera_thread, recorder_thread, master_thread, display_window_thread;

    /**
     * @brief Thread manager controls threading functionalities
     *
     * The thread manager creates new video recorder thread when recording begins.
     * It uses the create_video_recorder_thread for the thread creation process
     *
     */
    void thread_manager();


    /**
     * @brief Method to create threads for the video recorder
     *
     * This method is utilized by the thread manager in order to create
     * video recorder threads which are neccecsary to
     *
     */
    void create_video_recorder_thread();

public:

    /**
     * @brief Doorbell class constructor
     *
     *
     */
    Doorbell(char **argv);

    /**
     * @brief Doorbell class destructor
     *
     */
    ~Doorbell();

    /**
     * @brief Display and cleanup the GUI window
     *
     * open_window will create and show the GUI from VideoRecorder.
     *
     * @params argv - takes in the current directory of the program (first argv argument)
     * @params atomic boolean for determining whether raw footage is shown.
     *
     */
    int open_window(char **argv, std::atomic<bool> *show_raw_camera);
};


#endif // GROUP_17_DOORBELL_HPP
