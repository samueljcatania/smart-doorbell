/*
 * Author: Samuel Catania
 * Username: scatani9
 * Student Number: 251175283
 * Date: Friday, March 17, 2023
 *
 * Description of Camera.cpp:
 *
 */

#ifndef GROUP_17_CIRCULARBUFFER_HPP
#define GROUP_17_CIRCULARBUFFER_HPP


#include <cstdio>
#include <vector>
#include <opencv2/opencv.hpp>

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

    ~CircularBuffer();

    void push(T element);

    T pop();

    size_t size();

    size_t capacity();

    void clear();
};

#endif //GROUP_17_CIRCULARBUFFER_HPP
