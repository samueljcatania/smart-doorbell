/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Doorbell.cpp:
 *
 */

#include "../include/Doorbell.hpp"

Doorbell::Doorbell() {
    camera_thread = std::thread(&Camera::detect_motion, camera, std::ref(shared_queue), std::ref(mutex_lock),
                                std::ref(cond_var));

    //recorder_thread
    manager_thread = std::thread(&Doorbell::thread_manager, this);

    camera_thread.join();
    manager_thread.join();
}

void Doorbell::thread_manager() {

}

Doorbell::~Doorbell() = default;

//void Doorbell::thread_manager() {
//    std::string readData;
//
//    while (1) {
//        // Critical Section
//        std::unique_lock<std::mutex> unique_lock{mutex_lock};
//        cond_var.wait(unique_lock, [&] { return !shared_queue.empty(); });
//
//        while (!shared_queue.empty()) {
//            readData += shared_queue.front();
//            shared_queue.pop();
//        }
//    }
//}
