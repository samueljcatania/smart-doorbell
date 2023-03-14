/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Camera.cpp:
 *
 */

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ctime>

#include "../include/Camera.h"

Camera::Camera() {
    cv::Mat frame;

    // Open the default video camera
    video_capture.open(0, cv::CAP_V4L2);

    // Set the video size to 512 by 288 to process faster
    video_capture.set(3, 512);
    video_capture.set(4, 288);

    // Check if the camera was successfully opened
    if (video_capture.isOpened()) {
        video_capture.read(frame);

        // Convert the first frane to grayscale and set is as firstFrame
        cvtColor(frame, first_frame, cv::COLOR_BGR2GRAY);
        GaussianBlur(first_frame, first_frame, cv::Size(21, 21), 0);

    } else {
        std::cout << "Cannot open the video camera" << std::endl;
    }
}


Camera::~Camera() {
    // Cleanup the camera and close any open windows
    video_capture.release();
    cv::destroyAllWindows();
}

void Camera::detectMotion(std::queue<char> &shared_queue, std::mutex &mutex_lock, std::condition_variable &cond_var) {
    cv::Mat frame;
    std::vector<std::vector<cv::Point> > contours;

    if (first_frame.empty()) {
        std::cout << "Since the camera did not initialize properly, this function cannot be called." << std::endl;
        return;
    }

    while (video_capture.read(frame)) {
        cv::Mat frame_delta, gray, thresh, absolute_difference;
        std::string camera_description = "No Motion";

        // Convert the current frame to greyscale
        cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, cv::Size(21, 21), 0);

        // If the average frame is uninitialized, then initialize it
        if (average_frame.empty()) {
            average_frame = cv::Mat::zeros(gray.size(), CV_32F);
            continue;
        }

        // Accumulate the weighted average between the current frame and previous frames
        accumulateWeighted(gray, average_frame, 0.1);

        // Compute the difference between the current frame
        convertScaleAbs(average_frame, absolute_difference);
        absdiff(gray, absolute_difference, frame_delta);

        // Calculate the threshold of the delta image
        threshold(frame_delta, thresh, 25, 255, cv::THRESH_BINARY);

        // Dilate the threshold image to fill in holes, then find contours on threshold image
        dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);
        findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Loop over all the contours
        for (const auto &contour: contours) {

            // Check each contour against a minimum size of 500 pixels, which defines a region of the frame to be
            // considered actual “motion”. If the contour is too small, skip it
            if (contourArea(contour) < 500) {
                continue;
            }

            // Generate a green bounding box for the contour to draw on the frame, and update the frame description
            cv::Rect rect = cv::boundingRect(contour);
            cv::rectangle(frame, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height),
                          CV_RGB(0, 255, 0), 2);
            camera_description = "Motion Detected";

            std::lock_guard<std::mutex> lock_guard{mutex_lock};
            shared_queue.push('g');
            cond_var.notify_all();
        }

        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        // draw the text and timestamp on the frame
        cv::putText(frame, "Room Status:" + camera_description, cv::Point(10, 20),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 0), 1);
        cv::putText(frame, std::ctime(&end_time), cv::Point(10, frame.size[0] - 10),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 0), 1);

        // Show the raw frame, thresh frame, and frame delta frame
        imshow("Camera", frame);
        imshow("Thresh", thresh);
        imshow("Frame Delta", frame_delta);

        //If the Escape key is pressed, break the while loop.
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
}
