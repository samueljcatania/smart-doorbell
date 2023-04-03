
#include <iostream>
#include <pangomm/layout.h>

#include "../include/DisplayWindow.hpp"

DisplayWindow::DisplayWindow()
        : raw_camera_button("View Raw Camera"),
          thresh_camera_button("View Threshed Camera"),
          delta_camera_button("View Camera Delta"),
          camera_tab_label(
                  "Use these buttons below to open up the different views made available by the Doorbell's camera."),
          faces_tab_label("View the image capture by facial detection"),
          recordings_tab_label("View the recordings captured by the doorbell") {

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

    std::cout << "Hello World - " << data << " was pressed" << std::endl;

}


////
//// Created by Jonathan Lee on 2023-03-13.
////
//
//#include "../include/DisplayWindow.hpp"
//
//DisplayWindow::DisplayWindow() :
//        toggle_camera_button("Camera ON/OFF"),
//        start_recording_button("Record"),
//        stop_recording_button("Stop recording") {
//
//    // Set the title and border of the window
//    set_title("Menu Screen");
//    set_border_width(10);
//
//    // Create a header bar with a title and a close button
//    Gtk::HeaderBar *header = Gtk::manage(new Gtk::HeaderBar());
//    header->set_show_close_button(true);
//    header->set_title("Menu Screen");
//    set_titlebar(*header);
//
//    // Create a grid layout for the content
//    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid());
//    grid->set_row_spacing(10);
//    grid->set_column_spacing(10);
//    grid->set_margin_top(10);
//    grid->set_margin_bottom(10);
//    grid->set_margin_left(10);
//    grid->set_margin_right(10);
//    add(*grid);
//
//    // Create a stack for the tabs
//    Gtk::Stack *stack = Gtk::manage(new Gtk::Stack());
//    grid->attach(*stack, 0, 1, 1, 1);
//
//    // Create the tabs and add them to the stack
//    Gtk::Box *tab1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
//    stack->add(*tab1, "Tab 1");
//
//    Gtk::Box *tab2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
//    stack->add(*tab2, "Tab 2");
//
//    add(*stack);
//
//    // Add content to the first tab
//    Gtk::Label *label1 = Gtk::manage(new Gtk::Label("This is tab 1."));
//    tab1->add(*label1);
//    tab1->show();
//
//    // Add content to the second tab
//    Gtk::Label *label2 = Gtk::manage(new Gtk::Label("This is tab 2."));
//    tab2->add(*label2);
//    tab2->show();
//
//    // Create a label for the image
//    Gtk::Label *image_label = Gtk::manage(new Gtk::Label("Image:"));
//    grid->attach(*image_label, 0, 0, 1, 1);
//
////    // Create an image and add it to the grid
////    Gtk::Image *image = Gtk::manage(new Gtk::Image());
////    image->set_from_file("image.png");
////    grid->attach(*image, 1, 0, 1, 1);
//
//    // Create the buttons
//    Gtk::Button *button1 = Gtk::manage(new Gtk::Button("Button 1"));
//    grid->attach(*button1, 0, 2, 1, 1);
//
//    Gtk::Button *button2 = Gtk::manage(new Gtk::Button("Button 2"));
//    grid->attach(*button2, 1, 2, 1, 1);
//
//    Gtk::Button *button3 = Gtk::manage(new Gtk::Button("Button 3"));
//    grid->attach(*button3, 2, 2, 1, 1);
//
//    // Show all widgets
//    show_all_children();
//
////    // Set the title of the window
////    set_title("Control Panel");
////
////    // Sets the margin around the box
////    set_border_width(10);
////
////    // Put the box into the main window
////    add(window_box);
////
////    // Set an event handler for each button, so upon button press the on_button_clicked() function is called
////    toggle_camera_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
////            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "1"));
////    start_recording_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
////            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "2"));
////    stop_recording_button.signal_clicked().connect(sigc::bind<-1, Glib::ustring>(
////            sigc::mem_fun(*this, &DisplayWindow::on_button_clicked), "3"));
////
////    // Add the buttons to the window
////    window_box.pack_start(toggle_camera_button);
////    toggle_camera_button.show();
////
////    window_box.pack_start(start_recording_button);
////    start_recording_button.show();
////
////    window_box.pack_start(stop_recording_button);
////    stop_recording_button.show();
////
////    // Tell GTK to display the buttons in the window
////
////    // Tell GTK to display the window box
////    window_box.show();
//}
//
//DisplayWindow::~DisplayWindow() = default;
//

//}
//
