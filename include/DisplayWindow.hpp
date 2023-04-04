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

    /**
     * Constructor for Display Window
     * @param show_raw_camera_param atomic boolean that determines whether raw camera footage is shown.
     */
    DisplayWindow(std::atomic<bool> *show_raw_camera_param);

    /**
     * Destructor for displayWindow.
     */
    ~DisplayWindow() override;

    /**
     * atomic boolean to determine whether the raw footage from the camera is being shown.
     */
    std::atomic<bool> *show_raw_camera;


protected:
    /**
     * main_box is the main window box for the notebook on the GUI.
     */
    Gtk::Box main_box;

    /**
     * Grid for showing and organizing components
     */
    Gtk::Grid camera_grid;

    /**
     * notebook - the tabs on the GUI.
     */
    Gtk::Notebook notebook;

    /**
     * Labels for the GUI
     */
    Gtk::Label camera_tab_label, raw_camera_label;

    /**
     * Buttons for toggling camera footage.
     */
    Gtk::Button raw_camera_button;

    /**
     * @brief Signal handler for switching pages
     *
     * This signal handler is utilized when changing pages on the GUI.
     *
     * @param page tabs on the window
     * @param page_num current page number of the tab.
     */
    void on_notebook_switch_page(Gtk::Widget *page, guint page_num);

    /**
     * @brief Signal handler for button clicks
     *
     * This signal handler is utilized when buttons on the GUI are pressed
     *
     * @param data data sent when the button is clicked
     */
    void on_button_clicked(const Glib::ustring &data);
};

#endif // GROUP_17_DISPLAYWINDOW_HPP
