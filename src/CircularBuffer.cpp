/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Friday, March 17, 2023
 *
 * Description of Camera.cpp:
 *
 */

#include "../include/CircularBuffer.hpp"

template<typename T>
CircularBuffer<T>::CircularBuffer(size_t size) {
    max_size = size;
    vector.resize(size);
    std::fill(vector.begin(), vector.end(), T());
}

template<typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer<cv::Mat> &circular_buffer) {
    head = circular_buffer.head;
    tail = circular_buffer.tail;
    current_size = circular_buffer.current_size;
    max_size = circular_buffer.max_size;
    vector = circular_buffer.vector;
}

template<typename T>
CircularBuffer<T>::~CircularBuffer() = default;

template<typename T>
void CircularBuffer<T>::push(T element) {
    tail = (tail + 1) % max_size;
    vector[tail] = element;
    current_size++;

    if (current_size > max_size) {
        current_size = max_size;

        if (tail == head) {
            head = (head + 1) % max_size;
        }
    }
}

template<typename T>
T CircularBuffer<T>::pop() {
    if (current_size == 0) {
        return T();

    } else {
        T element = vector[head];
        head = (head + 1) % max_size;
        current_size--;

        return element;
    }
}

template<typename T>
size_t CircularBuffer<T>::get_size() {
    return current_size;
}

template<typename T>
size_t CircularBuffer<T>::get_capacity() {
    return max_size;
}

template<typename T>
void CircularBuffer<T>::set_capacity(size_t new_max_size) {
    max_size = new_max_size;
    clear();
}

template<typename T>
void CircularBuffer<T>::clear() {
    vector.clear();
    vector.resize(max_size);
    std::fill(vector.begin(), vector.end(), T());
}

template
class CircularBuffer<cv::Mat>;
