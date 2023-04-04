
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
     * head location in queue
     */
    size_t head = 0;

    /**
     * tail location in queue
     */
    size_t tail = -1;

    /**
     * current size of the queue
     */
    size_t current_size = 0;

    /**
     * maximum size of the queue
     */
    size_t max_size;

    /**
     * element in the queue
     */
    std::vector<T> vector;

public:
    /**
     * Constructor for the CircularBuffer
     * @param size the size of the CircularBuffer
     */
    explicit CircularBuffer(size_t size);

    /**
     * Constructor for CircularBuffer
     * @param circular_buffer camera frame to load into the Circular buffer.
     */
    explicit CircularBuffer(const CircularBuffer<cv::Mat> &circular_buffer);

    /**
     * Destructor for Circular Buffer
     */
    ~CircularBuffer();

    /**
     * Push element to the buffer
     * @param element the element to be pushed
     */
    void push(T element);

    /**
     * Pop element off of the buffer
     * @return the element that was popped out of the buffer.
     */
    T pop();

    /**
     * Get the size of the buffer
     * @return the size of the buffer
     */
    size_t get_size();

    /**
     * Return the max capacity of the buffer
     * @return the max capacity of the buffer
     */
    size_t get_capacity();

    /**
     * Set a new max buffer size
     * @param new_max_size new size to be set.
     */
    void set_capacity(size_t new_max_size);


    /**
     * Clears elements from the queue.
     */
    void clear();
};


#endif //GROUP_17_CIRCULARBUFFER_HPP
