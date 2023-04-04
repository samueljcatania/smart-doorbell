#ifndef GROUP_17_DISPLAYWINDOW_HPP
#define GROUP_17_DISPLAYWINDOW_HPP

#include <gtkmm.h>
#include <atomic>

/**
 * @brief The Display Window class creates the GUI from which camera functionalities can be utilized
 *
 * DisplayWindow will create the GUI that allows the user to interact with the camera. The
 * various views can be selected to be displayed. Saved images and videos can also be accessed
 * via this GUI.
 *
 * @author Samuel Catania
 */

class DisplayWindow : public Gtk::Window {
public:
    DisplayWindow(std::atomic<bool> *show_raw_camera_param);
    /**
     * @brief Constructor for Display Window
     *
     */
    DisplayWindow();

    ~DisplayWindow() override;

    std::atomic<bool> *show_raw_camera;


protected:
    /**
     * Initialization of various child widgets used for displaying, labeling, and using buttons on GUI
     */
    Gtk::Box main_box, face_detection_box;
    Gtk::ScrolledWindow face_detection_scrolled_window;
    Gtk::Grid camera_grid, face_detection_grid, recordings_grid;
    Gtk::Notebook notebook;
    Gtk::Label camera_tab_label, raw_camera_label, thresh_camera_label, delta_camera_label, faces_tab_label, recordings_tab_label;

    Gtk::ButtonBox button_box;
    Gtk::Button raw_camera_button, thresh_camera_button, delta_camera_button;

    /**
     * @brief Signal handler for switching pages
     *
     * This signal handler is utilized when changing pages on the GUI.
     *
     * @param page
     * @param page_num
     */
    void on_notebook_switch_page(Gtk::Widget *page, guint page_num);

    /**
     * @brief Signal handler for button clicks
     *
     * This signal handler is utilized when buttons on the GUI are pressed
     *
     * @param data
     */
    void on_button_clicked(const Glib::ustring &data);
};

#endif // GROUP_17_DISPLAYWINDOW_HPP
