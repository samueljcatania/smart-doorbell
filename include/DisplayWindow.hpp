//
// Created by Jonathan Lee on 2023-03-13.
//

#ifndef GROUP_17_DISPLAYWINDOW_HPP
#define GROUP_17_DISPLAYWINDOW_HPP

#include <gtkmm.h>
#include <atomic>

class DisplayWindow : public Gtk::Window {
public:
    DisplayWindow(std::atomic<bool> *show_raw_camera_param);

    ~DisplayWindow() override;

    std::atomic<bool> *show_raw_camera;


protected:
    //Child widgets:
    Gtk::Box main_box, face_detection_box;
    Gtk::ScrolledWindow face_detection_scrolled_window;
    Gtk::Grid camera_grid, face_detection_grid, recordings_grid;
    Gtk::Notebook notebook;
    Gtk::Label camera_tab_label, raw_camera_label, thresh_camera_label, delta_camera_label, faces_tab_label, recordings_tab_label;

    Gtk::ButtonBox button_box;
    Gtk::Button raw_camera_button, thresh_camera_button, delta_camera_button;

    //Signal handlers:
    void on_notebook_switch_page(Gtk::Widget *page, guint page_num);

    void on_button_clicked(const Glib::ustring &data);
};

#endif // GROUP_17_DISPLAYWINDOW_HPP
