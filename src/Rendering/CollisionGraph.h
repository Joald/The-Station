#ifndef THE_STATION_COLLISION_GRAPH_H
#define THE_STATION_COLLISION_GRAPH_H


#include <string>
#include <vector>
#include <map>
#include <algorithm>

class CollisionGraph {
public:
    using Edge = std::pair<std::string, std::string>;
private:
    using IDType = uint64_t;

    std::vector<std::string> idToString;
    std::map<std::string, IDType> stringToId;
    std::vector<std::vector<IDType>> graph;

    IDType newID(const std::string& val) {
        auto it = stringToId.find(val);
        if (it != stringToId.end()) {
            return it->second;
        }
        auto rv = stringToId[val] = idToString.size();
        idToString.emplace_back(val);
        return rv;
    }

    IDType edgeMax(const Edge& edge) {
        return std::max(stringToId[edge.first], stringToId[edge.second]);
    }

    void insertDirectedEdge(IDType src, IDType dest) {
        if (graph.size() <= src) {
            graph.resize(src + 1);
        }
        graph[src].emplace_back(dest);
    }

public:
    explicit CollisionGraph(const std::vector<Edge>& edges) {
        for (auto&[src, dest] : edges) {
            auto srcID = newID(src);
            auto destID = newID(dest);
            insertDirectedEdge(srcID, destID);
            insertDirectedEdge(destID, srcID); // TODO: allow directed graphs
        }
    }
};


#endif //THE_STATION_COLLISION_GRAPH_H
