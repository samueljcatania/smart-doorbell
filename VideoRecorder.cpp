//
// Created by Meg Zhang on 10/03/23.
//

#include "VideoRecorder.hpp"

using namespace cv;
using namespace std;

VideoRecorder::VideoRecorder() = default;

void VideoRecorder::openCamera(){
    this->cap = cv::VideoCapture(0);
    if(!cap.isOpened()){
        throw std:: runtime_error("Unable to open camera.");
    }
}

void VideoRecorder::closeCamera(){
    this->cap.release();
}

void VideoRecorder::peek() {
    if(!cap.isOpened()){
        throw std:: runtime_error("Unable to open camera.");
    }
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;

    for(;;){
        cap.read(frame);
        if (frame.empty()){
            throw std::runtime_error("Blank frame grabbed.");
        }

        imshow("Live Camera Footage", frame);
        //writer.write(frame);
        if(waitKey(5) >= 0){
            break;
        }
    }
}

int VideoRecorder::recordVideo() {
    this->frame = cv::Mat();
    this->writer = cv::VideoWriter("hello world.avi", cv::VideoWriter::fourcc('M','J', 'P', 'G'), 30, cv::Size(640,480));

    if(!cap.isOpened()){
        throw std:: runtime_error("Unable to open camera.");
    }
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;

    for(;;){
        cap.read(frame);
        if (frame.empty()){
            throw std::runtime_error("Blank frame grabbed.");
        }

        imshow("Live Camera Footage", frame);
        writer.write(frame);
        if(waitKey(5) >= 0){
            break;
        }
    }

    return 0;
}

VideoRecorder::~VideoRecorder() {
    cap.release();
    writer.release();
    frame.release();
    cv::destroyAllWindows();
}


