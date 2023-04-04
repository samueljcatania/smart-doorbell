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

class Doorbell {
private:
    Camera camera;
    bool recording = false;
    std::queue<cv::Mat> shared_queue;
    CircularBuffer<cv::Mat> shared_lead_up_buffer = CircularBuffer<cv::Mat>(0);
    std::mutex queue_lock, camera_lock, buffer_lock;
    std::condition_variable recording_updated, queue_updated, buffer_updated;
    std::thread camera_thread, recorder_thread, master_thread;

    void thread_manager();

    void create_video_recorder_thread();

public:
    Doorbell(char **argv);

    ~Doorbell();

    int open_window(char **argv, std::atomic<bool> *show_raw_camera);
};


#endif // GROUP_17_DOORBELL_HPP
