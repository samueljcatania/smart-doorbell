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
     * TODO
     */
    Camera camera;

    /**
     * TODO
     */
    bool recording = false;

    /**
     * TODO
     */
    std::queue<cv::Mat> shared_queue;

    /**
     * TODO
     */
    CircularBuffer<cv::Mat> shared_lead_up_buffer = CircularBuffer<cv::Mat>(0);

    /**
     * TODO
     */
    std::mutex queue_lock, camera_lock, buffer_lock;

    /**
     * TODO
     */
    std::condition_variable recording_updated, queue_updated, buffer_updated;

    /**
     * TODO
     */
    std::thread camera_thread, recorder_thread, master_thread;

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
     * @params TODO
     * @params TODO
     *
     */
    int open_window(char **argv, std::atomic<bool> *show_raw_camera);
};


#endif // GROUP_17_DOORBELL_HPP
