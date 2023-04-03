
#ifndef GROUP_17_CIRCULARBUFFER_HPP
#define GROUP_17_CIRCULARBUFFER_HPP


#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @brief Circular buffer class to aid in computations for motion detection
 *
 * CircularBuffer contains the constructor, getter, setter, and cleanup functions
 * for the CircularBuffer. The CircularBuffer is utilized within Camera's motion detection
 * method to perform the frame comparison computations.
 *
 * @author Samuel Catania
 *
 */

template<typename T>

class CircularBuffer {
private:
    size_t head = 0;
    size_t tail = -1;
    size_t current_size = 0;
    size_t max_size;
    std::vector<T> vector;

public:
    explicit CircularBuffer(size_t size);

    explicit CircularBuffer(const CircularBuffer<cv::Mat> &circular_buffer);

    ~CircularBuffer();

    void push(T element);

    T pop();

    size_t get_size();

    size_t get_capacity();

    void set_capacity(size_t new_max_size);

    void clear();
};


#endif //GROUP_17_CIRCULARBUFFER_HPP
