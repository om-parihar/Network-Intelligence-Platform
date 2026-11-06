
#include <iostream>
#include "nip/graph/NetworkNode.hpp"
#include "nip/graph/NetworkLink.hpp"

int main() {
    nip::NetworkNode router{
        1,
        "Router-1",
        nip::NodeType::ROUTER,
        "192.168.1.1"
    };

    nip::NetworkLink link{
        1,
        2,
        10.5,
        1000.0,
        5.0
    };

    std::cout << router.name << '\n';
    std::cout << router.ipAddress << '\n';
    std::cout << link.latencyMs << " ms\n";

    return 0;
}
