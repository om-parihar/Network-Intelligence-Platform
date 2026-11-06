
# Network Intelligence Platform — Architecture

## 1. Architecture Style

NIP will initially follow a modular monolithic architecture.

Individual components will have clear responsibilities and interfaces.
Components may be separated into services when justified by scalability
or deployment requirements.

## 2. Main Components

### C++ Network Engine
- Graph representation of network topology.
- BFS, DFS and Dijkstra algorithms.
- Traffic statistics processing.
- Packet parsing and analysis.

### Python Backend
- FastAPI REST API.
- Business logic and orchestration.
- Telemetry ingestion.
- Database communication.
- Integration with C++ and ML components.

### Machine Learning Engine
- Feature engineering.
- Anomaly detection.
- Traffic prediction.
- Model evaluation.

### AI Copilot
- Retrieval-Augmented Generation.
- Network documentation retrieval.
- Incident analysis.
- Read-only tool calling.

### Frontend
- React dashboard.
- Network topology visualization.
- Device monitoring.
- Incident management.
- AI assistant interface.

### Database
- PostgreSQL.
- Device records.
- Interface information.
- Telemetry records.
- Incidents and anomalies.

## 3. Component Communication

- React communicates with FastAPI through HTTP APIs.
- Python initially integrates with the C++ core through pybind11.
- Python communicates with PostgreSQL through a database access layer.
- ML models are invoked through Python interfaces.
- The AI Copilot retrieves authorized network context through backend tools.

## 4. Data Flow

1. Network devices or simulators generate network information.
2. Collectors obtain telemetry and traffic information.
3. The C++ engine processes performance-critical network operations.
4. Python validates and orchestrates the collected information.
5. PostgreSQL stores device information and telemetry.
6. The ML engine analyzes network behaviour.
7. Detected anomalies are recorded as incidents.
8. The AI Copilot uses network context to explain incidents.
9. React displays network health and intelligence.

## 5. Engineering Principles

- Separation of concerns.
- Modular and testable components.
- Explicit interfaces between modules.
- Secure handling of network data.
- Human approval for network configuration changes.
- Measurable performance and model