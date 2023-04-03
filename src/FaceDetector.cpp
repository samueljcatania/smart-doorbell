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

FaceDetector::FaceDetector() :
        confidence_threshold(0.5),
        height(300),
        width(300),
        scale_factor(1.0),
        mean_values({104., 177.0, 123.0}) {
    // Note: The variables MODEL_CONFIGURATION_FILE
    // and MODEL_WEIGHTS_FILE are passed in via cmake
    network = cv::dnn::readNetFromCaffe("../assets/deploy.prototxt",
                                        "../assets/res10_300x300_ssd_iter_140000_fp16.caffemodel");
    if (network.empty()) {
        std::ostringstream ss;
        throw std::invalid_argument("Failed to load network with the following settings:\n");
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
                detection_matrix.at<float>(i, 3) * frame.cols);

        int y_left_bottom = static_cast<int>(
                detection_matrix.at<float>(i, 4) * frame.rows);

        int x_right_top = static_cast<int>(
                detection_matrix.at<float>(i, 5) * frame.cols);

        int y_right_top = static_cast<int>(
                detection_matrix.at<float>(i, 6) * frame.rows);

        faces.emplace_back(x_left_bottom,
                           y_left_bottom,
                           (x_right_top - x_left_bottom),
                           (y_right_top - y_left_bottom));
    }

    return faces;
}
