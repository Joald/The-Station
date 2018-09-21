#include <map>

#include "CollisionDetector.h"



namespace {
DetectorMap initDetectors() {
    DetectorMap map;
    return map;
}

} // namespace

CollisionDetector& collisionDetector(
  const std::string& detectorName,
  const std::shared_ptr<CollisionGraph>& graph) {
    auto& detectors = collisionDetectors();
    auto it = detectors.find(detectorName);
    if (it == detectors.end()) {
        it = detectors.emplace(detectorName, graph).first;
    }
    return it->second;
}

DetectorMap& collisionDetectors() {
    static auto detectors = initDetectors();
    return detectors;
}
