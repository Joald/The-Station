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

    CollisionGraph& getGraph() { return *graph; }
};

void registerCollisionDetector(std::shared_ptr<CollisionDetector> detector);

CollisionDetector& collisionDetector();

} // STEngine

#endif //THE_STATION_COLLISION_DETECTOR_H
