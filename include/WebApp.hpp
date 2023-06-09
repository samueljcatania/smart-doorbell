#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <Wt/WEnvironment.h>
#include <Wt/WTable.h>
#include <Wt/WAnchor.h>
#include <Wt/WFileResource.h>
#include <boost/filesystem.hpp>
#include <Wt/WTimer.h>
#include <Wt/WSignal.h>
#include <chrono>
#include <ctime>
#include <iomanip>

#ifndef GROUP_17_WEBSOCKET_HPP
#define GROUP_17_WEBSOCKET_HPP

/**
 * @brief WebApp is a self hosted web server that shows the status of the Smart Doorbell.
 *
 * The Smart Doorbell takes in command line arguments to bind to an IP address.
 * When running, use --docroot . --http-address 0.0.0.0 --http-port 8080
 * You can change the http address to your computer's IP address so that other devices on the network can
 * access the webpage.
 *
 * @author Meg Zhang
 *
 */
class WebApp : public Wt::WApplication
{
public:
    /**
     * @brief Constructor for WebApp.
     * @param env Wt::WEnvironment object take takes in required info to create the web application.
     */
    explicit WebApp(const Wt::WEnvironment& env);

    /**
     * Call startApplication to start running the web application.
     * @brief This static function initializes the WebApp object.
     *
     * @param argc number of command line arguments. Should be passed through main().
     * @param argv The content of the command line arguments. Should be passed through main().
     * @return 0 if server starts up successfully.
     */
    static int startApplication(int argc, char **argv);

    /**
     * getInstance() returns the singleton instance of WebApp, if it has been initialized.
     *
     * @return pointer to the current static instance of WebApp.
     */
    static WebApp* getInstance();

    /**
     * bool motionDetectedCurr is a control variable. Change this variable if motion has been detected,
     * and then the WebApp will automatically update the motion detected status.
     */
    bool motionDetectedCurr = false;


private:
    /**
     * motionDetectedPrev tracks the recent history of motion detection, so that a motion detected notification
     * isn't displayed every second motion is detected in the WebApp.
     */
    bool motionDetectedPrev = false;

    /**
     * fileTable stores the files found on the system.
     * It also includes weblinks so that you can remotely download the files.
     */
    Wt::WTable *fileTable_;

    /**
     * imageTable stores the images found on the system.
     * It displays them in a gallery.
     */
    Wt::WTable *imageTable_;

    /**
     * serverMessage keeps track of the current time and displays it on the WebApp.
     */
    Wt::WText *serverMessage_;

    /**
     * Timer is used to refresh the data shown on the page at regular intervals.
     */
    Wt::WTimer *timer_;

    /**
     * currMotionStatus is a variable storing text which is displayed on the WebApp
     * indicating whether or not motion is currently detected.
     */
    Wt::WText *currMotionStatus_;

    /**
     * The path that the WebApp accesses to look for recordings.
     *
     */
    boost::filesystem::path recordingsPath_{"../recordings"};

    /**
    * The path that the WebApp accesses to look for images.
    *
    */
    boost::filesystem::path imagesPath_{"../recordings/images"};

    /**
     * A set that stores the displayed images in the WebApp.
     */
    std::set<std::string> displayedImages;

    /**
     * Returns the instance of WebApp that is currently running.
     *
     */
    static WebApp *instance_;

    /**
     * GreetingsContainer stores the motion detected history.
     *
     */
    static Wt::WContainerWidget *greetingsContainer_;

    /**
     * This function automatically updates the current time displayed on the WebApp.
     *
     */
    void updateServerTimeMsg();

    /**
     * This function is called by WebApp to check if there have been any motion changes.
     *
     */
    void updateMotionStatus();

    /**
     * This function is called by WebApp in order to refresh the File Explorer
     * so that any file additions/deletions are reflected.
     *
     */
    void updateFileList();

    /**
     * trackMotionChanges tracks whether motion has been detected recently
     *
     * @return whether motion is currently detected in the camera.
     */
    bool trackMotionChanges();

    /**
     * This function adds new faces to the image gallery when images are captured.
     *
     */
    void updateImagesList();
};

#endif //GROUP_17_WEBSOCKET_HPP
