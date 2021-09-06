#include <utility>

#ifndef THE_STATION_COLLISION_DETECTOR_H
#define THE_STATION_COLLISION_DETECTOR_H

#include <string>
#include <memory>

#include "CollisionGraph.h"
#include "CollisionShape.h"

namespace STEngine {

class CollisionDetector {
    using GraphPtr = std::shared_ptr<CollisionGraph>;
    GraphPtr graph;
public:
    explicit CollisionDetector(GraphPtr graph) : graph(std::move(graph)) {}
};

CollisionDetector& collisionDetector(const std::string& detectorName, std::shared_ptr<CollisionGraph> graph);

using DetectorMap = std::map<std::string, CollisionDetector>;

DetectorMap& collisionDetectors();

} // STEngine

#endif //THE_STATION_COLLISION_DETECTOR_H
