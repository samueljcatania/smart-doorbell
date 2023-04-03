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

int main(int argc, char *argv[]) {
    Doorbell doorbell;
    doorbell.open_window(argc, argv);

//    DisplayWindow displayWindow;
//    displayWindow.open_window(argc, argv);
//
//    VideoRecorder vr; // creates a new VideoRecorder object.
//    vr.openCamera(); // Open up the camera.
//    vr.recordVideo(); // Start recording video.
//
//    // Note: The code gets hung on the previous step until a key is pressed. To close it using closeCamera(),
//    // maybe try multithreading.
//    vr.closeCamera();
//
//    DisplayWindow test;
//    test.openGui();
    return 0;
}
