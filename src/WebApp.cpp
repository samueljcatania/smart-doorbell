//
// Created by Meg on 20/03/23.
//

#include "../include/WebApp.hpp"

Wt::WContainerWidget* WebApp::greetingsContainer_ = nullptr;
WebApp* WebApp::instance_ = nullptr;

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
    timer_->timeout().connect(this, &WebApp::updateServerTimeMsg);
    // update motion detected status
    timer_->timeout().connect(this, &WebApp::updateMotionStatus);
    // update files
    timer_->timeout().connect(this, &WebApp::updateFileList);
    //update images
    timer_->timeout().connect(this, &WebApp::updateImagesList);
    timer_->start();

    // Current Motion Detected Status
    root()->addWidget(std::make_unique<Wt::WBreak>());
    currMotionStatus_ = root()->addWidget(std::make_unique<Wt::WText>("Current Status: No Motion Detected at this moment."));
    root()->addWidget(std::make_unique<Wt::WBreak>());

    //file explorer module
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WText>("Stored Recordings: "));
    auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    container->setStyleClass("container");

    fileTable_ = container->addWidget(std::make_unique<Wt::WTable>());
    fileTable_->setWidth(Wt::WLength("100%"));
    updateFileList();

    // end file explorer module

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
    timer_->timeout().connect([this, greet]{
        if (trackMotionChanges()){
            greet();
        }
    });

    // activity history layout on webapp
    greetingsContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    greetingsContainer_->addWidget(std::make_unique<Wt::WBreak>());
    greetingsContainer_->addWidget(std::make_unique<Wt::WText>("Activity History:"));
    greetingsContainer_->addWidget(std::make_unique<Wt::WBreak>());

    // image gallery
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WText>("Image Gallery: "));
    auto container2 = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    container2->setStyleClass("container");
    imageTable_ = container2->addWidget(std::make_unique<Wt::WTable>());
    imageTable_->setWidth(Wt::WLength("100%"));
    updateImagesList();


    // recording buttons
//    Wt::WPushButton *startRecordingButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Start Recording"));
//    Wt::WPushButton *stopRecordingButton = root()->addWidget(std::make_unique<Wt::WPushButton>("Stop Recording"));

    instance_ = this;

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
void WebApp::updateServerTimeMsg()
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

// This function updates the webapp to display whether motion has been detected or not
void WebApp::updateMotionStatus(){
    if (!motionDetectedCurr){
        currMotionStatus_->setText("Current Status: No Motion Detected at this moment.");
    }
    else{
        currMotionStatus_->setText("Current Status: Motion Detected");
    }
}

// this function tracks motion changes for use of keeping a history of when motion was detected
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

    // prev = motion detected, curr = motion detected OR prev = no motion detected, curr = no motion detected
    else{
        return false;
    }

}

// function to retrieve Recordings folder files.
void WebApp::updateFileList() {
    int row = 1;

    if (!boost::filesystem::exists(recordingsPath_) || !boost::filesystem::is_directory(recordingsPath_)) {
        return;
    }

    // Clear the entire table if there are existing entries
    fileTable_->clear();

    for (const auto &entry : boost::filesystem::directory_iterator(recordingsPath_)) {
        if (boost::filesystem::is_regular_file(entry.path())) {
            auto fileName = entry.path().filename().string();
            auto filePath = (recordingsPath_ / fileName).string();
            auto fileResource = std::make_shared<Wt::WFileResource>("", filePath);
            fileResource->suggestFileName(fileName);

            fileTable_->elementAt(row, 0)->addWidget(std::make_unique<Wt::WAnchor>(Wt::WLink(fileResource), fileName));

            ++row;
        }
    }
}

// function to update images.
void WebApp::updateImagesList() {
    int row = imageTable_->rowCount();

    if (!boost::filesystem::exists(imagesPath_) || !boost::filesystem::is_directory(imagesPath_)) {
        return;
    }

    for (const auto &entry : boost::filesystem::directory_iterator(imagesPath_)) {
        if (boost::filesystem::is_regular_file(entry.path())) {
            auto fileName = entry.path().filename().string();
            auto filePath = (imagesPath_ / fileName).string();

            // Check if the image is already displayed
            if (displayedImages.find(fileName) == displayedImages.end()) {
                auto fileResource = std::make_shared<Wt::WFileResource>("", filePath);
                fileResource->suggestFileName(fileName);

                // Create a WImage widget with the file resource as a source and add it to the table
                auto imageWidget = std::make_unique<Wt::WImage>(Wt::WLink(fileResource));
                imageWidget->setAlternateText(fileName); // Set the alternate text to the file name

                // Set the image size (width and height)
                imageWidget->setWidth(Wt::WLength(150, Wt::LengthUnit::Pixel));
                imageWidget->setHeight(Wt::WLength(100, Wt::LengthUnit::Pixel));

                imageTable_->elementAt(row, 0)->addWidget(std::move(imageWidget));

                // Add the image to the displayed images set
                displayedImages.insert(fileName);

                ++row;
            }
        }
    }
}

// Return the instance of WebApp that is being run.
WebApp *WebApp::getInstance() {
    return instance_;
}
