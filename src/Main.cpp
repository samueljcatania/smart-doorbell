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

int main() {
    //Doorbell doorbell;

    CircularBuffer<int> buff = CircularBuffer<int>(5);

    for(int x = 0; x < 2; x++){
        buff.push(x);
    }

    for(int x = 0; x < 10; x++){
        std::cout << "Position: " << x << " Element: " << buff.pop() << std::endl;
    }

//    DisplayWindow displayWindow;
//    displayWindow.openGui();

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
