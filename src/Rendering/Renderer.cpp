#include "Renderer.h"

Renderer& renderer() {
    static Renderer render;
    return render;
}
