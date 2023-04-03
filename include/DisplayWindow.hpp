#ifndef GROUP_17_DISPLAYWINDOW_HPP
#define GROUP_17_DISPLAYWINDOW_HPP

#include <gtkmm.h>

/**
 * @brief The Display Window class creates the GUI from which camera functionalities can be utilized
 *
 * DisplayWindow will create the GUI that allows the user to interact with the camera. The
 * various views can be selected to be displayed. Saved images or videos can also be accessed
 * via this GUI.
 *
 * @author Samuel Catania
 */

class DisplayWindow : public Gtk::Window {
public:
    DisplayWindow();

    ~DisplayWindow() override;

protected:
    //Child widgets:
    Gtk::Box main_box;
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
