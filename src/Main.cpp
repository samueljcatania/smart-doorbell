
/**
 * Main function for the Smart Doorbell
 * This is the entry point for the program.
 * 4/3/23
 * @authors Samuel Catania, Meg Zhang, Quintin Peter Phillips, Jonathan Enjie Lee, Junhong Lin
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
