/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Main.cpp:
 *
 */

#include <opencv2/core/utils/logger.hpp>
#include "../include/Doorbell.hpp"

int main(int argc, char *argv[]) {
    // Turn off OpenCV console logging output
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

//    Doorbell doorbell;

    DisplayWindow displayWindow;
    displayWindow.open_window(argc, argv);
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
