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
     * @brief Constructor for Display Window
     *
     */
    DisplayWindow(std::atomic<bool> *show_raw_camera_param, std::atomic<bool> *show_threshold_camera,
                  std::atomic<bool> *show_delta_camera, std::condition_variable *camera_stream_updated_param);

    ~DisplayWindow() override;

    std::atomic<bool> *show_raw_camera;
    std::atomic<bool> *show_threshold_camera;
    std::atomic<bool> *show_delta_camera;

    std::condition_variable *camera_stream_updated;


protected:
    /**
     * Initialization of various child widgets used for displaying, labeling, and using buttons on GUI
     */
    Gtk::Box main_box;
    Gtk::Grid camera_grid;
    Gtk::Notebook notebook;
    Gtk::Label camera_tab_label, raw_camera_label;
    Gtk::Button raw_camera_button;

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
