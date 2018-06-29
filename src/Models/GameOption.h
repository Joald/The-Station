#ifndef THE_STATION_GAMEOPTION_H
#define THE_STATION_GAMEOPTION_H

#include <string>

enum class OptionState {
    ON, OFF
};

class GameOption {
    std::string name;
    OptionState state;
public:
    GameOption(std::string name, OptionState state) : name(std::move(name)), state(state) {}

    void setState(OptionState state) {
        this->state = state;
    }
    OptionState getState() {
        return state;
    }
};


#endif //THE_STATION_GAMEOPTION_H
