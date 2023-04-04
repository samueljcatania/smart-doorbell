
#ifndef GROUP_17_CIRCULARBUFFER_HPP
#define GROUP_17_CIRCULARBUFFER_HPP


#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @tparam T Generic type so that the Circular Buffer can handle many different types of objects.
 */
template<typename T>

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
class CircularBuffer {
private:
    /**
     * TODO
     */
    size_t head = 0;

    /**
     * TODO
     */
    size_t tail = -1;

    /**
     * TODO
     */
    size_t current_size = 0;

    /**
     * TODO
     */
    size_t max_size;

    /**
     * TODO
     */
    std::vector<T> vector;

public:
    /**
     * Todo
     * @param size
     */
    explicit CircularBuffer(size_t size);

    /**
     * TODO
     * @param circular_buffer
     */
    explicit CircularBuffer(const CircularBuffer<cv::Mat> &circular_buffer);

    /**
     * TODO
     */
    ~CircularBuffer();

    /**
     * TODO
     * @param element
     */
    void push(T element);

    /**
     * TODO
     * @return
     */
    T pop();

    /**
     * TODO
     * @return
     */
    size_t get_size();

    /**
     * TODO
     * @return
     */
    size_t get_capacity();

    /**
     * TODO
     * @param new_max_size
     */
    void set_capacity(size_t new_max_size);


    /**
     * TODO
     */
    void clear();
};


#endif //GROUP_17_CIRCULARBUFFER_HPP
