//
// Created by Jonathan Lee on 2023-03-13.
//

#ifndef GROUP_17_DISPLAYWINDOW_HPP
#define GROUP_17_DISPLAYWINDOW_HPP

#include <gtkmm.h>
#include "../include/VideoRecorder.hpp"

class DisplayWindow {
private:
    VideoRecorder cam;

    void cameraButtonClick();

    void recordButtonClick();

    void stopRecordButtonClick();

public:
    DisplayWindow();

    ~DisplayWindow();

    int openGui(); // open gui
};


#endif // GROUP_17_DISPLAYWINDOW_HPP
