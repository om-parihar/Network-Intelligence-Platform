
# Network Intelligence Platform — Interface Design

## 1. C++ and Python Integration

Initial integration method: pybind11.

The C++ engine will expose selected functions to Python
through a Python extension module named nip_core.

## 2. C++ Modules

### Graph Engine
- shortest_path(source, destination, graph)
- bfs(start_node, graph)
- dfs(start_node, graph)
- connected_components(graph)

### Traffic Engine
- calculate_bandwidth(bytes, duration)
- calculate_packet_rate(packet_count, duration)
- calculate_sliding_window_statistics(metrics)

### Packet Analyzer
- analyze_packet(packet_bytes)
- extract_ip_header(packet_bytes)
- extract_transport_header(packet_bytes)

## 3. Python Backend Responsibilities

- Validate incoming data.
- Invoke C++ functions.
- Manage telemetry ingestion.
- Store processed results.
- Expose REST APIs.
- Coordinate ML inference.

## 4. Data Exchange

C++ functions should return structured results
that Python can consume.

Packet metadata may contain:

- Source IP
- Destination IP
- Protocol
- Source port
- Destination port
- Packet size

Invalid or unsupported packet formats must
produce controlled errors.

## 5. Engineering Requirements

- Define input and output types explicitly.
- Validate function arguments.
- Handle invalid network data safely.
- Write unit tests for every exposed function.
- Benchmark C++ operations.
- Avoid unnecessary copying of large packet buffers.
- Keep C++ and Python interfaces independently testable.

## 6. Future Integration

Potential future improvements:

- gRPC for independently deployed services.
- Kafka for high-volume event streaming.
- Native packet capture using Npcap/libpcap.
- Real device telemetry through SNMP and other protocols.
