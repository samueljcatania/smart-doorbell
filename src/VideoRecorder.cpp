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

void VideoRecorder::write_frames(std::queue<char> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var) {

}



//void VideoRecorder::recordVideo(const basic_string<char> &filename) {
//    this->frame = cv::Mat();
//    this->writer = cv::VideoWriter(filename, cv::VideoWriter::fourcc('M','J', 'P', 'G'), 30, cv::Size(640,480));
//    captureFrame();
//}



