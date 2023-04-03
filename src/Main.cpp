/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Main.cpp:
 *
 */

#include "../include/Doorbell.hpp"
#include "../include/WebApp.hpp"

#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
    Doorbell doorbell1;

//int main(int argc, char **argv) {
//
//    WebApp::startApplication(argc, argv);
//    WebApp::sendMessage("Hello World");

    std::thread serverThread([argc, argv] {
        WebApp::startApplication(argc, argv);
    });


    // Give some time for the server to start
    std::this_thread::sleep_for(std::chrono::seconds(1));


    // Create a second thread to execute the sendMessage function
//    std::thread messageThread([] {
//        WebApp::sendMessage("Hello World!");
//    });

//    messageThread.join();
    Doorbell doorbell;
    doorbell.open_window(argc, argv);

//    DisplayWindow displayWindow;
//    displayWindow.open_window(argc, argv);
//
//    VideoRecorder vr; // creates a new VideoRecorder object.
//    vr.openCamera(); // Open up the camera.
//    vr.recordVideo(); // Start recording video.
    serverThread.join();

   // WebApp::sendMessage("Hello World!");

//
//
//    // Note: The code gets hung on the previous step until a key is pressed. To close it using closeCamera(),
//    // maybe try multithreading.
//    vr.closeCamera();
//
//    DisplayWindow test;
//    test.openGui();
    return 0;
}
