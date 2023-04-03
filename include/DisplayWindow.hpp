//
// Created by Jonathan Lee on 2023-03-13.
//

#ifndef GROUP_17_DISPLAYWINDOW_HPP
#define GROUP_17_DISPLAYWINDOW_HPP

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include "VideoRecorder.hpp"

class DisplayWindow : public Gtk::Window {
public:
    DisplayWindow();

    ~DisplayWindow() override;

protected:
    Gtk::Box window_box;
    Gtk::Button toggle_camera_button, start_recording_button, stop_recording_button;

    void on_button_clicked(const Glib::ustring &data);
};


#endif // GROUP_17_DISPLAYWINDOW_HPP
