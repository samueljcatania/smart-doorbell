//
// Created by Meg Zhang on 10/03/23.
//

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/VideoRecorder.hpp"

using namespace cv;
using namespace std;

VideoRecorder::VideoRecorder() = default;

void VideoRecorder::openCamera(){
    cap = cv::VideoCapture(0);
    if(!cap.isOpened()){
        throw std:: runtime_error("Unable to open camera.");
    }
    recording = true;
}

void VideoRecorder::closeCamera(){
    recording = false;
    writer.release();
    cap.release();
    cv::destroyAllWindows();
}

void VideoRecorder::peek() {
    if(!cap.isOpened()){
        throw std:: runtime_error("Camera has not been opened. Please open the camera by calling openCamera()");
    }
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;

    for(;;){
        cap.read(frame);
        if (frame.empty()){
            throw std::runtime_error("Blank frame grabbed.");
        }

        imshow("Live Camera Footage", frame);
        if(waitKey(5) >= 0){
            break;
        }
    }
}

void VideoRecorder::recordVideo() {
    this->frame = cv::Mat();
    this->writer = cv::VideoWriter("../recordings/output.mp4", cv::VideoWriter::fourcc('a','v', 'c', '1'), 30, cv::Size(640,480));
    captureFrame();
}

//void VideoRecorder::recordVideo(const basic_string<char> &filename) {
//    this->frame = cv::Mat();
//    this->writer = cv::VideoWriter(filename, cv::VideoWriter::fourcc('M','J', 'P', 'G'), 30, cv::Size(640,480));
//    captureFrame();
//}

VideoRecorder::~VideoRecorder() {
    recording = false;
    cap.release();
    writer.release();
    frame.release();
    cv::destroyAllWindows();
}

void VideoRecorder::captureFrame() {
    if(!cap.isOpened()){
        throw std:: runtime_error("Camera has not been opened. Please open the camera by calling openCamera()");
    }
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;

    for(;;) {
        cap.read(frame);
        if (frame.empty()) {
            throw std::runtime_error("Blank frame grabbed.");
        }

        imshow("Live Camera Footage", frame);
        writer.write(frame);
        if (waitKey(5) >= 0 || !recording) {
            break;
        }
    }

    cap.release();
}


