/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Wednesday, March 8, 2023
 *
 * Description of Camera.hpp:
 *
 */



#ifndef GROUP_17_FACEDETECTOR_HPP
#define GROUP_17_FACEDETECTOR_HPP

#include <vector>
#include <opencv2/dnn.hpp>

/**
 * @brief Face Detector contains the methods
 *
 * Doorbell has methods to create threads, as well as the thread manager.
 * This threading is necesary to make use of various processes running consecutively.
 * There are also the initialization and cleanup methods for the GUI.
 *
 * @author Samuel Catania
 *
 */


class FaceDetector {
private:
/**
 * Face detection network
 *
 */
    cv::dnn::Net network = cv::dnn::readNetFromCaffe("../assets/deploy.prototxt",
                                                     "../assets/res10_300x300_ssd_iter_140000_fp16.caffemodel");;
/**
 * Input image width
 *
 */
    const int width = 300;
/**
 * Input image height
 *
 */
    const int height = 300;
/**
 * Scale factor when creating image blob
 *
 */
    const double scale_factor = 1.0;
/**
 *Mean normalization values network was trained with
 *
 */
    const cv::Scalar mean_values = {104., 177.0, 123.0};
/**
 * Face detection confidence threshold
 *
 */
    const float confidence_threshold = 0.5;

public:
    /**
     * @brief Constructor for Face
     *
     */
    explicit FaceDetector();

    std::vector<cv::Rect> detect_face_rectangles(const cv::Mat &frame);
};


#endif //GROUP_17_FACEDETECTOR_HPP
