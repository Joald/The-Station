#ifndef THE_STATION_MENUACTION_H
#define THE_STATION_MENUACTION_H


#include <string>
#include "Menu.h"
#include "GameOption.h"

class MenuAction {
    std::string actionText;
protected:
    explicit MenuAction(std::string name) : actionText(std::move(name)) {}
public:
    virtual void doAction() = 0;
};

class ChangeMenu : public MenuAction {
    Menu** currentMenu;
    Menu* targetMenu;
public:
    ChangeMenu(const std::string& name, Menu** currentMenu, Menu* targetMenu) :
        MenuAction(name), currentMenu(currentMenu), targetMenu(targetMenu) {}

    void doAction() override {
        *currentMenu = targetMenu;
    }
};

class SetOption : public MenuAction {
    GameOption* option;
    OptionState state;
public:
    SetOption(const std::string& name, GameOption* option, OptionState state) :
        MenuAction(name), option(option), state(state) {}
    void doAction() override {
        option->setState(state);
    }
};

#endif //THE_STATION_MENUACTION_H
