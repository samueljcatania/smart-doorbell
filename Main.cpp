// this is the file formerly known as Hello.cpp created by Samuel.
// it has now been repurposed and renamed to a much more bland "main.cpp"

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "VideoRecorder.hpp"

#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoRecorder vr; // creates a new VideoRecorder object.
    vr.openCamera(); // Open up the camera.
    vr.recordVideo("test.avi"); // Start recording video.

    // Note: The code gets hung on the previous step until a key is pressed. To close it using closeCamera(),
    // maybe try multithreading.
    vr.closeCamera();
}