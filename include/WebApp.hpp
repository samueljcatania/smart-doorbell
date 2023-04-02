//
// Created by Meg on 20/03/23.
//

#include <iostream>

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <mutex>

#include <Wt/WTimer.h>
#include <Wt/WSignal.h>

#include <chrono>
#include <ctime>
#include <iomanip>

#include <queue>

#ifndef GROUP_17_WEBSOCKET_HPP
#define GROUP_17_WEBSOCKET_HPP


class WebApp : public Wt::WApplication
{
public:
    explicit WebApp(const Wt::WEnvironment& env);

    // run this function to start the web server using the parameters specified in WebAppConfig.txt.
    static int startApplication(int argc, char **argv);

    static WebApp* getInstance();

    bool motionDetectedCurr = false;
    bool motionDetectedPrev = false;

    static std::queue<int> motionQueue;


private:
    static WebApp *instance_;


    Wt::WLineEdit *nameEdit_;
    static Wt::WContainerWidget *greetingsContainer_;
    Wt::WText *greeting_;
    Wt::WText *serverMessage_;
    Wt::WTimer *timer_;
    int messageCounter_;

    Wt::WText *currMotionStatus_;

    void updateServerTimeMsg();

    void updateMotionStatus();

    bool trackMotionChanges();

};

#endif //GROUP_17_WEBSOCKET_HPP
