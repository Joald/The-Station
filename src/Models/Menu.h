#ifndef THE_STATION_MENU_H
#define THE_STATION_MENU_H

#include <tuple>
#include <type_traits>
#include "GameOption.h"
#include "GameObject.h"
#include "MenuAction.h"

class MenuBase : public GameObject {};

template<class... Option>
class Menu : public MenuBase {
    std::tuple<Option...> options;

    template<class... OptionCandidate>
    inline static constexpr bool areOptions = (std::is_base_of_v<MenuAction, OptionCandidate> && ...);

    static_assert(areOptions<Option...>);

public:
    explicit Menu(Option... options) : options(options...) {}

};


#endif //THE_STATION_MENU_H
