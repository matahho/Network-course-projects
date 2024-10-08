# Computer Network Course Assignments

This repository contains two main projects developed as part of the Computer Network course assignments. Both projects leverage Qt for interface and functionality, and Boost for networking in one of the cases. Each project demonstrates fundamental aspects of network programming and simulation, focusing on real-world applications like voice calls and routing protocols.

## Projects Overview

### 1. **Socket Programming: Distributed Live Voice Call System**

This project demonstrates how to build a distributed live voice call system using socket programming techniques. We utilize Qt for handling audio input/output and Boost for network communications. The system enables real-time audio streaming between clients and servers.

#### Key Components:
- **Audio Source & Sink**: Captures and plays audio using `AudioSource` and `AudioSink` classes.
  - Audio levels are processed using loops to determine maximum audio input levels.
  
- **Connection Management**: 
  - A server class handles client connections using TCP. 
  - WebRTC protocol is used for efficient real-time communication, leveraging TURN and STUN servers.
  - Secure RTP (SRTP) is used to ensure encrypted communication.

#### WebRTC Protocol:
- **TURN/STUN Servers**: Used for traversing NATs and firewalls, ensuring device connectivity.
- **ICE (Interactive Connectivity Establishment)**: Handles network path optimization for direct connections.
- **SDP (Session Description Protocol)**: Manages multimedia session setup, helping with codec compatibility and transport layer protocols.

##### Advantages of WebRTC:
- Simplicity, compatibility, and security through SRTP.

##### Disadvantages of WebRTC:
- Scalability, codec limitations (VP8), and reliance on network quality.

![STUN server](https://github.com/matahho/CN_CA_1/assets/148063514/ef016451-2951-4a8e-bb35-d8dad28af2f4)
![SIGNALING server](https://github.com/matahho/CN_CA_1/assets/148063514/35828bfa-79f9-4b35-8bb8-c3eed319f4dd)

#### Resources:
- [YouTube: WebRTC Explanation](https://www.youtube.com/watch?v=WmR9IMUD_CY)

---

### 2. **Network Simulator for Measuring Routing Protocols**

This project focuses on simulating a network environment to measure the performance of different routing protocols. The simulator includes router, packet, cluster, and event control modules.

#### Key Components:
- **Router Class**: 
  - Each router is identified by a unique ID, and testing is handled using threads for each router to simulate parallelism.
  - `QThread` is used to assign each router its own thread.
  
- **Cluster & Packet Control**: These modules handle packet transfers and manage clusters of routers for optimized routing simulation.

---

## Authors

- Mehdi Haji Seyed Hossein
- Kasra Noorbakhsh
