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
    std::fill(vector.begin(), vector.end(), NULL);
}

template<typename T>
CircularBuffer<T>::~CircularBuffer() {

}

template<typename T>
void CircularBuffer<T>::push(T element) {
    tail = (tail + 1) % max_size;
    vector.insert(vector.begin() + tail, element);
    current_size++;
}

template<typename T>
T CircularBuffer<T>::pop() {
    T element;

    if (current_size == 0) {
        return element;

    } else {
        element = vector[head];
        head = (head + 1) * max_size;
        head--;

        return element;
    }
}

template<typename T>
T CircularBuffer<T>::element_at_index(size_t index) {
    return vector[index];
}


template<typename T>
size_t CircularBuffer<T>::size() {
    return current_size;
}

template<typename T>
size_t CircularBuffer<T>::capacity() {
    return max_size;
}

template<typename T>
void CircularBuffer<T>::clear() {
    vector.clear();
    vector.resize(max_size);
    std::fill(vector.begin(), vector.end(), NULL);
}

template class CircularBuffer<int>;
template class CircularBuffer<cv::Mat>;
