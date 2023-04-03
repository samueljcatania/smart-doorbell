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

class FaceDetector {
private:
/// Face detection network
    cv::dnn::Net network;
/// Input image width
    const int width;
/// Input image height
    const int height;
/// Scale factor when creating image blob
    const double scale_factor;
/// Mean normalization values network was trained with
    const cv::Scalar mean_values;
/// Face detection confidence threshold
    const float confidence_threshold;

public:
    explicit FaceDetector();

    std::vector<cv::Rect> detect_face_rectangles(const cv::Mat &frame);
};


#endif //GROUP_17_FACEDETECTOR_HPP
