//
// Created by Jonathan Lee on 2023-03-13.
//

#include <gtkmm/application.h>
#include "../include/DisplayWindow.hpp"

DisplayWindow::DisplayWindow() :
        toggle_camera_button("Camera ON/OFF"),
        start_recording_button("Record"),
        stop_recording_button("Stop recording") {

    // Set the title of the window
    set_title("Control Panel");

    // Sets the margin around the box
    window_box.set_margin(10);

    // Put the box into the main window
    set_child(window_box);

    // Set an event handler for each button, so upon button press the on_button_clicked() function is called
    toggle_camera_button.signal_clicked().connect(sigc::bind(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "1"));
    start_recording_button.signal_clicked().connect(sigc::bind(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "2"));
    stop_recording_button.signal_clicked().connect(sigc::bind(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "3"));

    // Add the buttons to the window
    window_box.append(toggle_camera_button);
    window_box.append(start_recording_button);
    window_box.append(stop_recording_button);

}

DisplayWindow::~DisplayWindow() = default;

void DisplayWindow::on_button_clicked(const Glib::ustring &data) {

    std::cout << "Hello World - " << data << " was pressed" << std::endl;

}

//void DisplayWindow::cameraButtonClick() { //Show camera when requested
//    cam.openCamera();
//    cam.peek();
//}
//
//void DisplayWindow::recordButtonClick() {//Start recording when asked
//    cam.openCamera();
//    cam.recordVideo();
//}
//
//void DisplayWindow::stopRecordButtonClick() {//Stop recording??
//    cam.closeCamera();
//}


int DisplayWindow::open_window(int argc, char *argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");

    // Shows the window and returns when it is closed
    return app->make_window_and_run<DisplayWindow>(argc, argv);
}


