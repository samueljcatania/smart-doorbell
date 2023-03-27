//
// Created by Meg on 20/03/23.
//

#include "../include/WebApp.hpp"
#include <Wt/WLineEdit.h>

WebApp::WebApp(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]{
        greeting_->setText("Hello there, " + nameEdit_->text());
    };
    button->clicked().connect(greet);
}
