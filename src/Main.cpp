/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Main.cpp:
 *
 */

#include <iostream>
#include <thread>

#include "../include/Doorbell.hpp"
#include "../include/WebApp.hpp"
#include "../include/DisplayWindow.hpp"

int main(int argc, char *argv[]) {
    char *copy_argv[]{};
    copy_argv[0] = argv[0];

    std::thread serverThread([argc, argv] {
        WebApp::startApplication(argc, argv);
    });

    // Give some time for the server to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    Doorbell doorbell(copy_argv);

    serverThread.join();

    return 0;
}
