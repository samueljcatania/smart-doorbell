//
// Created by Meg Zhang on 10/03/23.
//

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/VideoRecorder.hpp"

VideoRecorder::VideoRecorder() = default;

VideoRecorder::~VideoRecorder() {
    video_writer.release();
}



//void VideoRecorder::recordVideo(const basic_string<char> &filename) {
//    this->frame = cv::Mat();
//    this->writer = cv::VideoWriter(filename, cv::VideoWriter::fourcc('M','J', 'P', 'G'), 30, cv::Size(640,480));
//    captureFrame();
//}



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


