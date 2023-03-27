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

#ifndef GROUP_17_WEBSOCKET_HPP
#define GROUP_17_WEBSOCKET_HPP


class WebApp : public Wt::WApplication
{
public:
    explicit WebApp(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText *greeting_;
};

#endif //GROUP_17_WEBSOCKET_HPP
