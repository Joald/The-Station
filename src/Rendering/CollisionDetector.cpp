#include "CollisionDetector.h"

#include <utility>

namespace STEngine {

namespace {

struct DetectorHolder {
    std::shared_ptr<CollisionDetector> detectorPtr;
};

auto& holder() {
    static DetectorHolder holder;
    return holder;
}

} // namespace

CollisionDetector& collisionDetector() {
    return *holder().detectorPtr;
}

void registerCollisionDetector(std::shared_ptr<CollisionDetector> detector) {
    holder().detectorPtr = std::move(detector);
}

}  // namespace STEngine