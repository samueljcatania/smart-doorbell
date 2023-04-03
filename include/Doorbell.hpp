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
    Camera camera;
    bool recording = false;
    std::queue<cv::Mat> shared_queue;
    CircularBuffer<cv::Mat> shared_lead_up_buffer = CircularBuffer<cv::Mat>(0);
    std::mutex queue_lock, camera_lock, recorder_lock, buffer_lock;
    std::condition_variable recording_updated, queue_updated, buffer_updated;
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
    Doorbell();

    /**
     * @brief Doorbell class destructor
     *
     *
     */
    ~Doorbell();

    /**
     * @brief Display and cleanup the GUI window
     *
     * open_window will create and show the GUI from VideoRecorder.
     *
     * @params
     * @params
     *
     */
    static int open_window(int argc, char *argv[]);
};


#endif // GROUP_17_DOORBELL_HPP
