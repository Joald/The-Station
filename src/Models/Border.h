#ifndef THE_STATION_BORDER_H
#define THE_STATION_BORDER_H


#include "../Rendering/Renderable.h"

extern const char BORDER_TEXTURE_NAME[];

template<const char* name, bool hasShader = false>
class Border : public Renderable<name, hasShader> {

};


#endif //THE_STATION_BORDER_H
