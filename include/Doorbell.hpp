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
    std::queue<cv::Mat> shared_queue;
    std::mutex mutex_lock;
    std::condition_variable cond_var;
    std::thread camera_thread, recorder_thread, master_thread;

    void thread_manager();

public:
    Doorbell();

    ~Doorbell();

    int open_window(int argc, char *argv[]);
};


#endif // GROUP_17_DOORBELL_HPP
