
#include <iostream>
#include <atomic>
#include <pangomm/layout.h>
#include <condition_variable>

#include "../include/DisplayWindow.hpp"

DisplayWindow::DisplayWindow(std::atomic<bool> *show_raw_camera_param, std::atomic<bool> *show_threshold_camera,
                             std::atomic<bool> *show_delta_camera, std::condition_variable *camera_stream_updated_param)
        : raw_camera_button("View Camera"),
          camera_tab_label(
                  "INSTRUCTIONS: Use this button below to preview the Doorbell's camera. When looking at the Camera, press the ESC key to return back to this menu. Press the X in the top right of this window when you are satisfied with the camera.") {

    show_raw_camera = show_raw_camera_param;
    camera_stream_updated = camera_stream_updated_param;

    set_title("Control Panel");
    set_border_width(10);
    set_default_size(600, 100);

    camera_grid.set_column_spacing(20);
    camera_grid.set_row_spacing(20);
    camera_grid.set_column_homogeneous(true);
    camera_grid.set_row_homogeneous(true);
    add(main_box);

    camera_tab_label.set_line_wrap(true);


//Add the Notebook, with the button underneath:
    notebook.set_border_width(10);
    main_box.pack_start(notebook);

    camera_grid.attach(camera_tab_label,
                       0, 0, 1, 1);

    camera_grid.attach(raw_camera_button,
                       0, 1, 1, 1);
    raw_camera_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "1"));

//Add the Notebook pages:
    notebook.append_page(camera_grid, "Camera");


    notebook.signal_switch_page().connect(sigc::mem_fun(*this, &DisplayWindow::on_notebook_switch_page));

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

    hide();
}
