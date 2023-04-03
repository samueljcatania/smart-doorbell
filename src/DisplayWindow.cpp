//
// Created by Jonathan Lee on 2023-03-13.
//

#include "../include/DisplayWindow.hpp"

DisplayWindow::DisplayWindow() :
        toggle_camera_button("Camera ON/OFF"),
        start_recording_button("Record"),
        stop_recording_button("Stop recording") {

    // Set the title of the window
    set_title("Control Panel");

    // Sets the margin around the box
    set_border_width(10);

    // Put the box into the main window
    add(window_box);

    // Set an event handler for each button, so upon button press the on_button_clicked() function is called
    toggle_camera_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "1"));
    start_recording_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "2"));
    stop_recording_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "3"));

    // Add the buttons to the window
    window_box.pack_start(toggle_camera_button);
    toggle_camera_button.show();

    window_box.pack_start(start_recording_button);
    start_recording_button.show();

    window_box.pack_start(stop_recording_button);
    stop_recording_button.show();

    // Tell GTK to display the buttons in the window

    // Tell GTK to display the window box
    window_box.show();
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


