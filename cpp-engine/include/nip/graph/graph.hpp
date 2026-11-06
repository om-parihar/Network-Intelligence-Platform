#ifndef NIP_GRAPH_HPP
#define NIP_GRAPH_HPP

#include <unordered_map>
#include <vector>

#include "NetworkNode.hpp"
#include "NetworkLink.hpp"

namespace nip {

class Graph {
private:
    std::unordered_map<int, NetworkNode> nodes;

    std::unordered_map<int, std::vector<NetworkLink>> adjacencyList;

public:
    bool addNode(const NetworkNode& node);

    bool addLink(const NetworkLink& link, bool bidirectional = false);

    bool hasNode(int id) const;

    const NetworkNode* getNode(int id) const;

    const std::vector<NetworkLink>* getNeighbors(int id) const;
};

}

#endif