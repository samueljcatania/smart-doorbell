//
// Created by Meg Zhang on 10/03/23.
//

#include "VideoRecorder.hpp"
#include <windows.h>
#include <future>

using namespace cv;
using namespace std;

VideoRecorder::VideoRecorder() = default;

void VideoRecorder::openCamera(){
    this->cap = cv::VideoCapture(0);
    if(!cap.isOpened()){
        throw std:: runtime_error("Unable to open camera.");
    }
    recording = true;
}

void VideoRecorder::closeCamera(){
    recording = false;
    this->writer.release();
    this->cap.release();
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
void VideoRecorder::duration(){
    INPUT ip;

    int time = 5; //Put the actual time you want here
    int newtime = 2489.678 + 1965.318 * (time); //sleep_for gives unexpected results. tested randomly and did regression to see times. will this vary by device?
    //i.e. for a 10 second video, input

    std::this_thread::sleep_for(10000ms);
    //rel_time = 50000ms, video 24 seconds, 24, 24
    //rel_time = 30000ms, video 14 seconds
    //rel_time = 25000, video 12 seconds
    //rel_time= 20000ms, video 9 seconds
    //rel_time = 15000ms, video 6seconds
    //rel_time= 10000ms, video 3 seconds
    //rel_time= 5000, video 2 seconds


    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press Q
    ip.ki.wVk = 0x51; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press

    SendInput(1, &ip, sizeof(INPUT));

    // release key (is this neccesary? I thinkproblemsn might come otherwise?
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));


}


void VideoRecorder::recordVideo() {
    this->frame = cv::Mat();
    this->writer = cv::VideoWriter("hello world.avi", cv::VideoWriter::fourcc('M','J', 'P', 'G'), 30, cv::Size(640,480));
    captureFrame();
}

void VideoRecorder::recordVideo(const basic_string<char> &filename) {
    this->frame = cv::Mat();
    this->writer = cv::VideoWriter(filename, cv::VideoWriter::fourcc('M','J', 'P', 'G'), 30, cv::Size(640,480));
    captureFrame();
}

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

        auto delayed_call = std::async(std::launch::async, [&]{
            // std::this_thread::sleep_for(1000);
            duration();
        });

        if (waitKey(5) >= 0 || recording == false) {
            break;
        }
    }
}




