
#include <iostream>
#include <cassert>
#include <vector>
#include <limits>
#include <cmath>

#include "nip/graph/Graph.hpp"

int main() {

    nip::Graph graph;

    // =====================================
    // 1. ADD NETWORK NODES
    // =====================================

    assert(graph.addNode({
        1, "Router-1", nip::NodeType::ROUTER, "192.168.1.1"
    }));

    assert(graph.addNode({
        2, "Router-2", nip::NodeType::ROUTER, "192.168.1.2"
    }));

    assert(graph.addNode({
        3, "Router-3", nip::NodeType::ROUTER, "192.168.1.3"
    }));

    assert(graph.addNode({
        4, "Switch-1", nip::NodeType::SWITCH, "192.168.1.4"
    }));

    assert(graph.addNode({
        5, "Host-1", nip::NodeType::HOST, "192.168.1.5"
    }));

    // Duplicate node test
    assert(!graph.addNode({
        1, "Duplicate", nip::NodeType::ROUTER, "192.168.1.10"
    }));

    std::cout << "All node tests passed!\n";


    // =====================================
    // 2. ADD NETWORK LINKS
    // =====================================

    assert(graph.addLink({1, 2, 10, 1000, 5}, true));
    assert(graph.addLink({1, 3, 30, 1000, 5}, true));
    assert(graph.addLink({2, 3, 5, 1000, 5}, true));
    assert(graph.addLink({2, 4, 20, 1000, 5}, true));
    assert(graph.addLink({3, 4, 10, 1000, 5}, true));
    assert(graph.addLink({4, 5, 5, 1000, 5}, true));

    // Invalid link test
    assert(!graph.addLink({1, 10, 10, 1000, 5}, true));

    // Verify reverse connection
    const auto* neighbors = graph.getNeighbors(2);

    bool reverseConnectionFound = false;

    for (const auto& link : *neighbors) {
        if (link.destinationId == 1) {
            reverseConnectionFound = true;
        }
    }

    assert(reverseConnectionFound);

    std::cout << "All link tests passed!\n";


    // =====================================
    // 3. NODE RETRIEVAL TEST
    // =====================================

    const nip::NetworkNode* node = graph.getNode(1);

    assert(node != nullptr);
    assert(node->name == "Router-1");

    assert(graph.getNode(10) == nullptr);

    std::cout << "All node retrieval tests passed!\n";


    // =====================================
    // 4. BFS TEST
    // =====================================

    std::vector<int> bfs = graph.breadthFirstSearch(1);

    std::vector<int> expectedBFS = {1, 2, 3, 4, 5};

    assert(bfs == expectedBFS);

    assert(graph.breadthFirstSearch(10).empty());

    std::cout << "BFS: ";

    for (int id : bfs) {
        std::cout << id << " ";
    }

    std::cout << "\nAll BFS tests passed!\n";


    // =====================================
    // 5. DFS TEST
    // =====================================

    std::vector<int> dfs = graph.depthFirstSearch(1);

    std::vector<int> expectedDFS = {1, 2, 3, 4, 5};

    assert(dfs == expectedDFS);

    assert(graph.depthFirstSearch(10).empty());

    std::cout << "DFS: ";

    for (int id : dfs) {
        std::cout << id << " ";
    }

    std::cout << "\nAll DFS tests passed!\n";


    // =====================================
    // 6. DIJKSTRA TEST
    // =====================================

    auto distances = graph.dijkstra(1);

    assert(distances[1] == 0.0);
    assert(distances[2] == 10.0);
    assert(distances[3] == 15.0);
    assert(distances[4] == 25.0);
    assert(distances[5] == 30.0);

    std::cout << "Distance to Router 3: "
              << distances[3] << " ms\n";

    std::cout << "All Dijkstra tests passed!\n";


    // =====================================
    // 7. SHORTEST PATH TEST
    // =====================================

    auto result = graph.shortestPath(1, 3);

    assert(result.reachable);
    assert(result.totalLatencyMs == 15.0);

    std::vector<int> expectedPath = {1, 2, 3};

    assert(result.path == expectedPath);

    std::cout << "Shortest route: ";

    for (int id : result.path) {
        std::cout << id << " ";
    }

    std::cout << "\nTotal latency: "
              << result.totalLatencyMs << " ms\n";

    std::cout << "All shortest path tests passed!\n";


    // =====================================
    // 8. UNREACHABLE PATH TEST
    // =====================================

    nip::Graph isolatedGraph;

    isolatedGraph.addNode({
        1, "Router-A", nip::NodeType::ROUTER, "10.0.0.1"
    });

    isolatedGraph.addNode({
        2, "Router-B", nip::NodeType::ROUTER, "10.0.0.2"
    });

    auto unreachable = isolatedGraph.shortestPath(1, 2);

    assert(!unreachable.reachable);
    assert(unreachable.path.empty());

    std::cout << "All unreachable path tests passed!\n";


    // =====================================
    // FINAL RESULT
    // =====================================

    std::cout << "\n=================================\n";
    std::cout << "ALL GRAPH TESTS PASSED!\n";
    std::cout << "=================================\n";

    return 0;
}
