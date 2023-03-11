//
// Created by Meg Zhang on 10/03/23.
//

#ifndef GROUP17_VIDEORECORDER_HPP
#define GROUP17_VIDEORECORDER_HPP
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


class VideoRecorder {
public:
    // Constructor for VideoRecorder - creates a new VideoRecorder object.
    explicit VideoRecorder();

    // deconstructor
    ~VideoRecorder();

    void openCamera(); // Opens up the camera.

    void closeCamera(); // Closes the camera.

    void peek(); // Shows camera footage but doesn't save it.

    // Shows and saves camera footage.
    int recordVideo();


private:
    cv::VideoCapture cap;
    cv::VideoWriter writer;
    cv::Mat frame;
};


#endif //GROUP17_VIDEORECORDER_HPP
