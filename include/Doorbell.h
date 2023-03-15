/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Doorbell.h:
 *
 */

#ifndef INC_33307B_GROUP_17_PROJECT_DOORBELL_H
#define INC_33307B_GROUP_17_PROJECT_DOORBELL_H

#include <thread>

#include "Camera.h"

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


#endif //INC_33307B_GROUP_17_PROJECT_DOORBELL_H
