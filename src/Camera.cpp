/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Camera.cpp:
 *
 */

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/Camera.hpp"

#define SECONDS_TO_WAIT_FOR_MOTION 5
#define SECONDS_TO_WAIT_FOR_CAMERA_TO_START 2
#define NUMBER_OF_FRAMES_TO_TEST_FRAME_RATE 120
#define SECONDS_OF_LEAD_UP_FOOTAGE 15

int Camera::measure_camera_frame_rate() {
    // Variable for storing video frames
    cv::Mat frame;

    // Start time
    auto start = std::chrono::system_clock::now();

    // Read frames
    for (int i = 0; i < NUMBER_OF_FRAMES_TO_TEST_FRAME_RATE; i++) {
        video_capture >> frame;
    }

    // End time
    auto end = std::chrono::system_clock::now();

    // Calculate the time that has elapsed
    long seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // Calculate the frame rate
    return (int) ((NUMBER_OF_FRAMES_TO_TEST_FRAME_RATE / seconds) / 2);
}

Camera::Camera() {
    cv::Mat frame;

    // Open the default video camera
    video_capture.open(0, cv::CAP_V4L2);

    // Check if the camera was successfully opened
    if (video_capture.isOpened()) {

    } else {
        std::cout << "Cannot open the video camera" << std::endl;
    }

    frame_rate = 15;
//    frame_rate = measure_camera_frame_rate();

    lead_up_buffer.set_capacity(SECONDS_OF_LEAD_UP_FOOTAGE * frame_rate);

    camera_start_time = std::chrono::system_clock::now();
}


Camera::~Camera() {
    // Cleanup the camera and close any open windows
    video_capture.release();
    average_frame.release();
    cv::destroyAllWindows();
}

void
Camera::detect_motion(bool &recording, std::queue<cv::Mat> &shared_queue, std::mutex &camera_lock,
                      std::mutex &buffer_lock, CircularBuffer<cv::Mat> &shared_lead_up_buffer,
                      std::condition_variable &recording_updated, std::condition_variable &buffer_updated,
                      std::condition_variable &queue_updated) {
    cv::Mat frame;
    std::vector<std::vector<cv::Point> > contours;

    while (video_capture.read(frame)) {

        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()
                                                             - last_motion_time).count() <=
            SECONDS_TO_WAIT_FOR_MOTION && std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - camera_start_time).count() >= SECONDS_TO_WAIT_FOR_CAMERA_TO_START) {

            // Critical Section
//            std::lock_guard<std::mutex> lock_guard{mutex_lock};
//            shared_queue.push(frame);
//            queue_updated.notify_all();

        } else {
            //Add the frame to the 15-second lead-up buffer
            lead_up_buffer.push(frame);

            std::cout << lead_up_buffer.get_capacity() << std::endl;
            std::cout << lead_up_buffer.get_size() << std::endl;

            if (active_video_writer) {
                active_video_writer = false;

                // Critical Section
                std::lock_guard<std::mutex> lock_guard{camera_lock};
                recording = false;
                recording_updated.notify_all();
            }
        }


        auto rectangles = face_detector.detect_face_rectangles(frame);
        for (const auto &r: rectangles) {
            cv::rectangle(frame, r, CV_RGB(255, 0, 0), 4);
        }

        // Set the frame size to 512 by 380 to process faster
        cv::resize(frame, frame, cv::Size(512, 380));

        cv::Mat frame_delta, gray, thresh, absolute_difference;
        std::string camera_description = "No Motion";
        WebApp *webAppInstance = WebApp::getInstance();


        if (webAppInstance) {
            webAppInstance->motionDetectedCurr = false;
        }


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
            if (contourArea(contour) < 2000) {
                continue;
            }

            // Generate a green bounding box for the contour to draw on the frame, and update the frame description
            cv::Rect rect = cv::boundingRect(contour);
            cv::rectangle(frame, cv::Point(rect.x, rect.y),
                          cv::Point(rect.x + rect.width, rect.y + rect.height),
                          CV_RGB(0, 255, 0),
                          2);
            camera_description = "Motion Detected";

            if (webAppInstance) {
                webAppInstance->motionDetectedCurr = true;
            }

            if (std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now() - camera_start_time).count() >=
                SECONDS_TO_WAIT_FOR_CAMERA_TO_START) {
                last_motion_time = std::chrono::system_clock::now();

                if (!active_video_writer) {
                    active_video_writer = true;

                    // Critical Section
                    std::lock_guard<std::mutex> lock_guard_one{camera_lock};
                    recording = true;
                    recording_updated.notify_all();

                    std::lock_guard<std::mutex> lock_guard_two{buffer_lock};
                    shared_lead_up_buffer = lead_up_buffer;
                    buffer_updated.notify_all();
                }
            }
        }

        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        // Draw the text and timestamp on the frame
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

    frame.release();
}

int Camera::get_frame_rate() const {
    return frame_rate;
}
