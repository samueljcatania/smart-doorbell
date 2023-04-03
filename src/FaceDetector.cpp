/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Camera.hpp:
 *
 */


#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "../include/FaceDetector.hpp"

FaceDetector::FaceDetector() {
    if (network.empty()) {
        throw std::invalid_argument("Failed to load network.\n");
    }
}

std::vector<cv::Rect> FaceDetector::detect_face_rectangles(const cv::Mat &frame) {
    cv::Mat input_blob = cv::dnn::blobFromImage(frame,
                                                scale_factor,
                                                cv::Size(width, height),
                                                mean_values,
                                                false,
                                                false);

    network.setInput(input_blob, "data");
    cv::Mat detection = network.forward("detection_out");
    cv::Mat detection_matrix(detection.size[2],
                             detection.size[3],
                             CV_32F,
                             detection.ptr<float>());

    std::vector<cv::Rect> faces;

    for (int i = 0; i < detection_matrix.rows; i++) {
        float confidence = detection_matrix.at<float>(i, 2);

        if (confidence < confidence_threshold) {
            continue;
        }

        int x_left_bottom = static_cast<int>(
                detection_matrix.at<float>(i, 3) * (float) frame.cols);

        int y_left_bottom = static_cast<int>(
                detection_matrix.at<float>(i, 4) * (float) frame.rows);

        int x_right_top = static_cast<int>(
                detection_matrix.at<float>(i, 5) * (float) frame.cols);

        int y_right_top = static_cast<int>(
                detection_matrix.at<float>(i, 6) * (float) frame.rows);

        faces.emplace_back(x_left_bottom,
                           y_left_bottom,
                           (x_right_top - x_left_bottom),
                           (y_right_top - y_left_bottom));
    }

    return faces;
}
