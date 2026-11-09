
#include "nip/graph/Graph.hpp"

#include <queue>
#include <unordered_set>
#include <functional>
#include <limits>
#include <functional>
#include <algorithm>
#include <utility>

namespace nip {

// Add a network device
bool Graph::addNode(const NetworkNode& node) {
    auto result = nodes.emplace(node.id, node);

    if (!result.second) {
        return false;
    }

    adjacencyList.emplace(node.id, std::vector<NetworkLink>{});

    return true;
}

// Add a directed or bidirectional connection
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

// Check whether a device exists
bool Graph::hasNode(int id) const {
    return nodes.find(id) != nodes.end();
}

// Retrieve a network device
const NetworkNode* Graph::getNode(int id) const {
    auto it = nodes.find(id);

    if (it == nodes.end()) {
        return nullptr;
    }

    return &it->second;
}

// Retrieve outgoing connections
const std::vector<NetworkLink>* Graph::getNeighbors(int id) const {
    auto it = adjacencyList.find(id);

    if (it == adjacencyList.end()) {
        return nullptr;
    }

    return &it->second;
}

// Breadth-First Search
std::vector<int> Graph::breadthFirstSearch(int startId) const {
    std::vector<int> result;

    if (!hasNode(startId)) {
        return result;
    }

    std::queue<int> q;
    std::unordered_set<int> visited;

    q.push(startId);
    visited.insert(startId);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        result.push_back(current);

        const auto* neighbors = getNeighbors(current);

        for (const auto& link : *neighbors) {
            int nextNode = link.destinationId;

            if (visited.find(nextNode) == visited.end()) {
                visited.insert(nextNode);
                q.push(nextNode);
            }
        }
    }

    return result;
}

// Depth-First Search
std::vector<int> Graph::depthFirstSearch(int startId) const {
    std::vector<int> result;

    if (!hasNode(startId)) {
        return result;
    }

    std::unordered_set<int> visited;

    std::function<void(int)> dfs = [&](int current) {
        visited.insert(current);
        result.push_back(current);

        const auto* neighbors = getNeighbors(current);

        for (const auto& link : *neighbors) {
            int nextNode = link.destinationId;

            if (visited.find(nextNode) == visited.end()) {
                dfs(nextNode);
            }
        }
    };

    dfs(startId);

    return result;
}


std::unordered_map<int, double> Graph::dijkstra(int startId) const {

    std::unordered_map<int, double> distance;

    // Initialize all nodes with infinity
    for (const auto& node : nodes) {
        distance[node.first] = std::numeric_limits<double>::infinity();
    }

    // Check starting node
    if (!hasNode(startId)) {
        return distance;
    }

    // Min priority queue: {distance, nodeId}
    std::priority_queue<
        std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        std::greater<std::pair<double, int>>
    > pq;

    distance[startId] = 0.0;
    pq.push({0.0, startId});

    while (!pq.empty()) {

        double currentDistance = pq.top().first;
        int currentNode = pq.top().second;

        pq.pop();

        // Ignore outdated queue entries
        if (currentDistance > distance[currentNode]) {
            continue;
        }

        const auto* neighbors = getNeighbors(currentNode);

        for (const auto& link : *neighbors) {

            int nextNode = link.destinationId;

            double newDistance =
                currentDistance + link.latencyMs;

            // Relaxation
            if (newDistance < distance[nextNode]) {

                distance[nextNode] = newDistance;

                pq.push({newDistance, nextNode});
            }
        }
    }

    return distance;
}


ShortestPathResult Graph::shortestPath(int startId, int targetId) const {

    if (!hasNode(startId) || !hasNode(targetId)) {
        return {{}, std::numeric_limits<double>::infinity(), false};
    }

    std::unordered_map<int, double> distance;
    std::unordered_map<int, int> parent;

    for (const auto& node : nodes) {
        distance[node.first] = std::numeric_limits<double>::infinity();
    }

    using State = std::pair<double, int>;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pq;

    distance[startId] = 0.0;
    pq.push({0.0, startId});

    while (!pq.empty()) {

        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (currentDistance > distance[currentNode]) {
            continue;
        }

        if (currentNode == targetId) {
            break;
        }

        const auto* neighbors = getNeighbors(currentNode);

        for (const auto& link : *neighbors) {

            int nextNode = link.destinationId;

            double newDistance =
                currentDistance + link.latencyMs;

            if (newDistance < distance[nextNode]) {

                distance[nextNode] = newDistance;
                parent[nextNode] = currentNode;

                pq.push({newDistance, nextNode});
            }
        }
    }

    if (distance[targetId] == std::numeric_limits<double>::infinity()) {
        return {{}, distance[targetId], false};
    }

    std::vector<int> path;

    int current = targetId;

    while (current != startId) {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(startId);

    std::reverse(path.begin(), path.end());

    return {path, distance[targetId], true};
}


}
