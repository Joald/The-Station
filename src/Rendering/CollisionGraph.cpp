#include "CollisionGraph.h"

CollisionGraph::IDType CollisionGraph::newID(std::string_view val) {
    auto it = stringToId.find(val);
    if (it != stringToId.end()) {
        return it->second;
    }
    auto rv = idToString.size();
    idToString.emplace_back(val);
    stringToId[val] = rv;
    return rv;
}

CollisionGraph::IDType CollisionGraph::edgeMax(const CollisionGraph::Edge& edge) {
    return std::max(stringToId[edge.first], stringToId[edge.second]);
}

void CollisionGraph::insertDirectedEdge(CollisionGraph::IDType src, CollisionGraph::IDType dest) {
    if (graph.size() <= src) {
        graph.resize(src + 1);
    }
    graph[src].emplace_back(dest);
}

CollisionGraph::CollisionGraph(std::vector<Edge> edges) {
    for (auto& [src, dest] : std::move(edges)) {
        auto srcID = newID(src);
        auto destID = newID(dest);
        insertDirectedEdge(srcID, destID);
        insertDirectedEdge(destID, srcID); // TODO: allow directed graphs
    }
}

bool CollisionGraph::canCollide(std::string_view id1, std::string_view id2) {
    auto& neighs = graph[stringToId[id1]];
    return std::find(neighs.begin(), neighs.end(), stringToId[id2]) != neighs.end();
}
