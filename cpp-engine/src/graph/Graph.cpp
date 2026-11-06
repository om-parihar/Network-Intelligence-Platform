
#include "nip/graph/Graph.hpp"

namespace nip {

bool Graph::addNode(const NetworkNode& node) {
    auto result = nodes.emplace(node.id, node);

    if (!result.second) {
        return false;
    }

    adjacencyList.emplace(node.id, std::vector<NetworkLink>{});

    return true;
}

bool Graph::addLink(const NetworkLink& link, bool bidirectional) {
    if (!hasNode(link.sourceId) || !hasNode(link.destinationId)) {
        return false;
    }

    adjacencyList[link.sourceId].push_back(link);

    if (bidirectional) {
        NetworkLink reverseLink = link;

        reverseLink.sourceId = link.destinationId;
        reverseLink.destinationId = link.sourceId;

        adjacencyList[link.destinationId].push_back(reverseLink);
    }

    return true;
}

bool Graph::hasNode(int id) const {
    return nodes.find(id) != nodes.end();
}

const NetworkNode* Graph::getNode(int id) const {
    auto it = nodes.find(id);

    if (it == nodes.end()) {
        return nullptr;
    }

    return &it->second;
}

const std::vector<NetworkLink>* Graph::getNeighbors(int id) const {
    auto it = adjacencyList.find(id);

    if (it == adjacencyList.end()) {
        return nullptr;
    }

    return &it->second;
}

}
