#ifndef THE_STATION_COLLISION_GRAPH_H
#define THE_STATION_COLLISION_GRAPH_H


#include <string>
#include <vector>
#include <map>

class CollisionGraph {
    using IDType = uint64_t;

    std::vector<std::string> idToString;
    std::map<std::string, IDType> stringToId;
    std::vector<std::vector<int>> graph;

    IDType newID(const std::string& val) {
        auto it = stringToId.find(val);
        if (it != stringToId.end()) {
            return it->second;
        }
        idToString.emplace_back(val);
        stringToId[val] = idToString.size();
        return idToString.size();
    }



public:
    using Edge = std::pair<std::string, std::string>;
    explicit CollisionGraph(const std::vector<Edge>& edges) {
        for (auto&[src, dest] : edges) {
            auto srcID = newID(src);
            auto destID = newID(dest);
            graph[srcID].emplace_back(destID);
            graph[destID].emplace_back(srcID);
        }
    }
};


#endif //THE_STATION_COLLISION_GRAPH_H
