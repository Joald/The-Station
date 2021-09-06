#include <map>

#include "CollisionDetector.h"

namespace STEngine {

namespace {

struct DetectorHolder {
    std::shared_ptr<CollisionDetector> detectorPtr;
} holder;

} // namespace

CollisionDetector& collisionDetector() {
    return *holder.detectorPtr;
}

void registerCollisionDetector(std::shared_ptr<CollisionDetector> detector) {
    holder.detectorPtr = detector;
}

} // STEngine