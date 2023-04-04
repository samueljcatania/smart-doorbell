
#include <iostream>
#include <atomic>
#include <pangomm/layout.h>

#include "../include/DisplayWindow.hpp"

DisplayWindow::DisplayWindow(std::atomic<bool> *show_raw_camera_param)
        : raw_camera_button("View Raw Camera"),
          thresh_camera_button("View Threshed Camera"),
          delta_camera_button("View Camera Delta"),
          camera_tab_label(
                  "Use these buttons below to open up the different views made available by the Doorbell's camera."),
          faces_tab_label("View the image capture by facial detection"),
          recordings_tab_label("View the recordings captured by the doorbell") {

    show_raw_camera = show_raw_camera_param;

    set_title("Control Panel");
    set_border_width(10);
    set_default_size(1000, 600);

    camera_grid.set_column_spacing(20);
    camera_grid.set_row_spacing(20);
    camera_grid.set_column_homogeneous(true);
    camera_grid.set_row_homogeneous(true);

    add(main_box);

    //Add the Notebook, with the button underneath:
    notebook.set_border_width(10);
    main_box.pack_start(notebook);

    camera_grid.attach(camera_tab_label, 0, 0, 1, 1);

    camera_grid.attach(raw_camera_button, 0, 1, 1, 1);
    raw_camera_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "1"));

    camera_grid.attach(thresh_camera_button, 0, 2, 1, 1);
    thresh_camera_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "2"));

    camera_grid.attach(delta_camera_button, 0, 3, 1, 1);
    delta_camera_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "3"));

    //Add the Notebook pages:
    notebook.append_page(camera_grid, "Camera");
    notebook.append_page(faces_tab_label, "Face Detection");
    notebook.append_page(recordings_tab_label, "Recordings");

    raw_camera_label.set_line_wrap(true);


    notebook.signal_switch_page().connect(sigc::mem_fun(*this,
                                                        &DisplayWindow::on_notebook_switch_page));

    show_all_children();
}

DisplayWindow::~DisplayWindow() = default;

void DisplayWindow::on_notebook_switch_page(Gtk::Widget * /* page */, guint page_num) {
    std::cout << "Switched to tab with index " << page_num << std::endl;

    //You can also use m_Notebook.get_current_page() to get this index.
}

void DisplayWindow::on_button_clicked(const Glib::ustring &data) {
    if (data == "1") {
        (*show_raw_camera) = true;
    }
}
