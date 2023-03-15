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
#include "../include/Camera.hpp"
#include "../include/DisplayWindow.hpp"

class Doorbell {
private:
    Camera camera, camera1;
    std::queue<char> shared_queue;
    std::mutex mutex_lock;
    std::condition_variable cond_var;
    std::thread camera_thread, camera_thread_one, recorder_thread, manager_thread;

    void managerThread();

public:
    Doorbell();

    ~Doorbell();
};


#endif // GROUP_17_DOORBELL_HPP
