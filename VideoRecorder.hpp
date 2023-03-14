//
// Created by Meg Zhang on 10/03/23.
//

#ifndef GROUP17_VIDEORECORDER_HPP
#define GROUP17_VIDEORECORDER_HPP
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


class VideoRecorder {
public:
    // Constructor for VideoRecorder - creates a new VideoRecorder object.
    explicit VideoRecorder();

    // deconstructor
    ~VideoRecorder();

    void openCamera(); // Opens up the camera.

    void closeCamera(); // Closes the camera.

    void peek(); // Shows open camera footage in a window but doesn't save it.

    // Shows and saves open camera footage (default with filename hello world.avi)
    void recordVideo();


    // shows and saves open camera footage (with specified filename).
    void recordVideo(const std::basic_string<char> &filename);

    // sets the duration of recording for the video
    void duration();

private:
    void captureFrame(); // helper function - this opens up the window that shows the video and also writes to the file.

    cv::VideoCapture cap; // stores the object that captures video
    cv::VideoWriter writer; // stores the object that writes video to a file
    cv::Mat frame; // stores the current video frame
    bool recording = false; // recording or not recording.
};


#endif //GROUP17_VIDEORECORDER_HPP
