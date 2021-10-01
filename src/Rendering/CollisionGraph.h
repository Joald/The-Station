#ifndef THE_STATION_COLLISION_GRAPH_H
#define THE_STATION_COLLISION_GRAPH_H


#include <string>
#include <vector>
#include <map>
#include <algorithm>

class CollisionGraph {
public:
    using Edge = std::pair<std::string_view, std::string_view>;

    explicit CollisionGraph(const std::vector<Edge>& edges);

    bool canCollide(std::string_view id1, std::string_view id2);

private:
    using IDType = uint64_t;

    std::vector<std::string_view> idToString;
    std::map<std::string_view, IDType> stringToId;
    std::vector<std::vector<IDType>> graph;

    IDType newID(std::string_view val);

    IDType edgeMax(const Edge& edge);

    void insertDirectedEdge(IDType src, IDType dest);
};


#endif //THE_STATION_COLLISION_GRAPH_H
