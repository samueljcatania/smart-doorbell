//
// Created by Meg on 20/03/23.
//

#include "../include/WebApp.hpp"
#include <Wt/WLineEdit.h>

Wt::WContainerWidget* WebApp::greetingsContainer_ = nullptr;
WebApp* WebApp::instance_ = nullptr;
std::queue<int> WebApp::motionQueue;

// Code in WebApp runs forever until the web application is closed.
WebApp::WebApp(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
{
    setTitle("Smart Doorbell Web Interface");

    root()->addWidget(std::make_unique<Wt::WText>("Smart Doorbell is online. You will be notified here when motion is detected.\n\n "));

    // Add server message text widget
    root()->addWidget(std::make_unique<Wt::WBreak>());
    serverMessage_ = root()->addWidget(std::make_unique<Wt::WText>("Current Server Time: "));
    root()->addWidget(std::make_unique<Wt::WBreak>());


    // Add timer for updating server messages
    timer_ = root()->addChild(std::make_unique<Wt::WTimer>());
    timer_->setInterval(std::chrono::seconds(1));
    timer_->timeout().connect(this, &WebApp::updateServerMessage);
    // update motion detected status
    timer_->timeout().connect(this, &WebApp::updateMotionStatus);
    timer_->start();

    // Current Motion Detected Status
    root()->addWidget(std::make_unique<Wt::WBreak>());
    currMotionStatus_ = root()->addWidget(std::make_unique<Wt::WText>("Current Status: No Motion Detected at this moment."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WBreak>());

    // Greetings sample code to reverse engineer


    //root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    //nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    //Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());


    auto greet = [this]{
        // Get the current date and time
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);

        // Format the date and time as a string
        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

        //greetingsContainer_->addWidget(std::make_unique<Wt::WText>("Hello there, " + nameEdit_->text()));
        greetingsContainer_->addWidget(std::make_unique<Wt::WText>("Motion Detected at " + ss.str()));
        greetingsContainer_->addWidget(std::make_unique<Wt::WBreak>());
    };
    //button->clicked().connect(greet);
    timer_->timeout().connect([this, greet]{
        if (trackMotionChanges()){
            greet();
        }
    });


    greetingsContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    greetingsContainer_->addWidget(std::make_unique<Wt::WBreak>());

    // recording buttons
//    Wt::WPushButton *startRecordingButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Start Recording"));
//    Wt::WPushButton *stopRecordingButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Stop Recording"));


// file explorer





    instance_ = this;

    // test

}

void WebApp::sendMessage(const std::string& msg){
        greetingsContainer_->addWidget(std::make_unique<Wt::WText>(Wt::WString(msg)));
        greetingsContainer_->addWidget(std::make_unique<Wt::WBreak>());
        timer_->timeout().connect(this, &WebApp::updateMotionStatus);

}

// Call this function to start the Web Application.
int WebApp::startApplication(int argc, char **argv){

    try {
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::EntryPointType::Application, [](const Wt::WEnvironment& env) {
            return std::make_unique<WebApp>(env);
        }, "/" );

        server.start();

        server.waitForShutdown();
        server.stop();

        return 0;
    }

    catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }

}

// This function updates the date and time displayed in the Web Application.
void WebApp::updateServerMessage()
{
    // Get the current date and time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);

    // Format the date and time as a string
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // Update the server message with the current date and time
    serverMessage_->setText("Current Server Time: " + ss.str());
}

void WebApp::updateMotionDetected_test(){
    currMotionStatus_->setText("Current Status: Motion Detected");

}

void WebApp::updateMotionStatus(){
    if (!motionDetectedCurr){
        currMotionStatus_->setText("Current Status: No Motion Detected at this moment.");
    }
    else{
        currMotionStatus_->setText("Current Status: Motion Detected");
    }
}

void notifyWebAppMotionDetected(){
     WebApp::motionQueue.push(1);
}

bool WebApp::trackMotionChanges(){
    // prev = no motion detected, curr = motion detected
    if (!motionDetectedPrev && motionDetectedCurr){
        motionDetectedPrev = true;
        return true;
    }

    // prev = motion detected, curr = no motion detected
    if (motionDetectedPrev && !motionDetectedCurr){
        motionDetectedPrev = false;
        return false;
    }

    // prev = motion detected, curr = motion detected
    // prev = no motion detected, curr = no motion detected
    else{
        return false;
    }

}

WebApp *WebApp::getInstance() {
    return instance_;
}
