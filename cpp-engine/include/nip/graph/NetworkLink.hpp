
#ifndef NIP_NETWORK_LINK_HPP
#define NIP_NETWORK_LINK_HPP

namespace nip {

struct NetworkLink {
    int sourceId;
    int destinationId;

    double latencyMs;
    double bandwidthMbps;
    double cost;
};

}

#endif
