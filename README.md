# CAN Bus Communication Simulator

Automotive CAN (Controller Area Network) bus simulator demonstrating multi-ECU communication, message arbitration, and diagnostic trouble code (DTC) management.

## Project Overview

This project simulates a realistic automotive CAN bus network with multiple Electronic Control Units (ECUs) communicating in real-time. It demonstrates core automotive embedded systems concepts including message prioritization, fault detection, and inter-ECU communication.

## Key Features

- **Multi-ECU Architecture**: 4 independent ECUs (Engine, Brake, Body Control, Infotainment)
- **CAN 2.0B Protocol**: Standard 11-bit identifier implementation
- **Message Queue Management**: 100-frame circular buffer with overflow protection
- **Priority-Based Arbitration**: Lower CAN IDs have higher priority
- **Collision Detection**: Realistic arbitration when multiple ECUs transmit simultaneously
- **Diagnostic Trouble Codes (DTC)**: Real-time fault detection and logging
- **Real-Time Monitoring**: Infotainment ECU displays all bus traffic
- **Inter-ECU Reactions**: ECUs respond to messages from other nodes

## Architecture
```
┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐
│  Engine ECU │  │  Brake ECU  │  │  Body ECU   │  │Infotainment │
│   (0x100)   │  │   (0x120)   │  │   (0x300)   │  │    ECU      │
└──────┬──────┘  └──────┬──────┘  └──────┬──────┘  └──────┬──────┘
       │                │                │                │
       └────────────────┴────────────────┴────────────────┘
                      Virtual CAN Bus
                   (Queue-based message passing)
```

## CAN Message IDs

| ID    | Priority | ECU Source      | Data Description              |
|-------|----------|-----------------|-------------------------------|
| 0x100 | Critical | Engine Control  | Engine RPM (2 bytes)          |
| 0x120 | Critical | Brake System    | Brake Status (1 byte)         |
| 0x300 | Medium   | Body Control    | Door Status Bitmap (1 byte)   |
| 0x7DF | High     | Diagnostic      | OBD-II Request/Response       |

## Getting Started

### Prerequisites
- GCC Compiler (MinGW for Windows)
- Make utility

### Building
```bash
mingw32-make clean
mingw32-make
```

### Running
```bash
./can_simulator.exe
```

## Project Structure
```
CANBusSimulator/
├── include/
│   ├── can_frame.h       # CAN frame structure and operations
│   ├── can_bus.h         # Virtual bus interface
│   ├── ecu_node.h        # ECU node management
│   └── dtc_manager.h     # Diagnostic Trouble Codes
├── src/
│   ├── can_frame.c
│   ├── can_bus.c
│   ├── ecu_node.c
│   ├── dtc_manager.c
│   └── main.c            # Main simulation loop
├── Makefile
└── README.md
```

## Sample Output
```
================================================
     CAN BUS SIMULATOR v2.0
     Multi-ECU Communication System
================================================

Active ECUs:
  * Engine Control Unit (ID: 0x100)
  * Brake System (ID: 0x120)
  * Body Control Module (ID: 0x300)
  * Infotainment System (Monitor Only)

=== Cycle 1 ===
>> Transmission Phase:
[Engine-ECU] Sending: CAN Frame [ID:0x100 DLC:4] Data: 0B 4A 00 00
[Brake-ECU] Sending: CAN Frame [ID:0x120 DLC:1] Data: 01

>> Reception Phase:
[Infotainment-ECU] Monitoring: ID=0x100 Engine RPM: 2890
[Infotainment-ECU] Monitoring: ID=0x120 Brakes: PRESSED
```

## CAN Arbitration Feature

When multiple ECUs attempt to transmit simultaneously, the simulator implements proper CAN arbitration based on message priority:
```
>> ARBITRATION EVENT:
   [Engine-ECU] wants to send ID: 0x100
   [Brake-ECU] wants to send ID: 0x120
   --> [Engine-ECU] WINS (lower ID = higher priority)
   --> [Brake-ECU] backs off, will retry
```

**Real-World Behavior**: In a typical simulation run, the Brake ECU may transmit only 9 out of 12 attempted frames due to arbitration losses, demonstrating realistic CAN bus collision handling.

## Technical Highlights

### CAN Frame Structure
- 11-bit identifier (0x000 - 0x7FF)
- Data Length Code (0-8 bytes)
- Timestamp for message tracking
- Error and RTR flags

### Bus Operations
- Non-blocking transmit/receive
- Queue overflow protection
- Statistics tracking (collisions, errors, dropped frames)
- Bus status monitoring
- Priority-based arbitration

### Fault Detection
- Engine misfire detection (10% random occurrence)
- High RPM warnings (threshold: 5000 RPM)
- Brake pressure monitoring (3% random fault)
- DTC generation and storage

## Statistics and Reporting

The simulator provides comprehensive statistics at the end of each session:

- **Per-ECU Statistics**: Frames sent, frames received, status
- **Bus Statistics**: Total frames, collisions, errors, dropped frames, queue utilization
- **Diagnostic Codes**: Active DTCs with descriptions

## Learning Outcomes

This project demonstrates:
- **CAN Protocol Implementation**: Standard frame format, priority arbitration
- **Embedded Communication**: Multi-node message passing
- **Automotive Diagnostics**: DTC generation and management
- **Real-Time Systems**: Cyclic execution, timing constraints
- **Collision Handling**: Arbitration and retry mechanisms
- **Modular Design**: Separation of concerns, reusable components

## Technical Skills Demonstrated

- C programming for embedded systems
- Data structure design (circular buffers, queues)
- Bit manipulation and binary protocols
- State machine implementation
- Real-time system simulation
- Modular software architecture

## Web Dashboard

The simulator includes a real-time web dashboard for visualizing CAN bus traffic:

**Features:**
- Live bus statistics display
- ECU status monitoring with sent/received frame counts
- Message log viewer (latest 50 messages)
- Color-coded messages by ECU type
- Collision detection alerts
- Auto-refresh every 3 seconds

**Usage:**
1. Run the simulator: `./can_simulator.exe`
2. Open `dashboard.html` in your web browser
3. Select the generated `can_data.json` file when prompted

The dashboard provides an intuitive interface for analyzing CAN communication patterns and identifying potential issues.

## Future Enhancements

- [ ] Extended CAN (29-bit identifier) support
- [x] Web-based dashboard for real-time visualization --- done
- [ ] CAN bus load analysis and statistics
- [ ] Message filtering and masking
- [ ] Save/replay CAN traces to file
- [ ] Multiple CAN bus support
- [ ] Gateway ECU implementation
- [ ] Error frame injection and handling



**Note**: This is a simulation for demonstration purposes. Real CAN bus implementations require specialized hardware and strict timing requirements. This project focuses on protocol understanding and software architecture.
