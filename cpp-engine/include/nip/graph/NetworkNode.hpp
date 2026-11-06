
#ifndef NIP_NETWORK_NODE_HPP
#define NIP_NETWORK_NODE_HPP

#include <string>

namespace nip {

enum class NodeType {
    ROUTER,
    SWITCH,
    HOST
};

struct NetworkNode {
    int id;
    std::string name;
    NodeType type;
    std::string ipAddress;
};

}

#endif
