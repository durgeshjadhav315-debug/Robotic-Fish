# 🤖 Robotic Fish – Underwater Sea Monitoring System

## 1. Introduction

The Robotic Fish is a biomimetic robotics project designed to develop a fish-inspired underwater robotic platform for environmental observation and monitoring.

The project aims to combine robotic movement, embedded systems, environmental sensors, and underwater imaging technologies to support future aquatic monitoring applications.

The current development stage focuses on the basic mechanical model and initial movement control architecture.

## 2. Problem Statement

Traditional underwater monitoring and inspection can require expensive equipment and specialized resources.

This project explores a compact fish-inspired robotic platform that could support underwater observation and environmental data collection.

## 3. Project Objectives

- Develop a fish-inspired robotic structure.
- Implement servo-based tail movement.
- Use ESP32 for embedded control.
- Integrate environmental monitoring sensors.
- Explore underwater visual monitoring.
- Develop a platform for future autonomous underwater applications.

## 4. Working Principle

The proposed robotic fish uses an ESP32 microcontroller as its main control unit.

A servo motor is intended to operate the tail mechanism and generate fish-like movement.

Environmental sensors are planned to collect water-related measurements, including temperature, dissolved solids, turbidity, and depth.

An ESP32-CAM module is planned for underwater visual observation.

The collected information can eventually be processed and stored for environmental analysis.

## 5. System Architecture

### Main Controller
ESP32 DevKit

### Movement System
MG996R Servo Motor

### Environmental Monitoring
- DS18B20 – Temperature
- TDS Sensor – Dissolved solids estimation
- SEN0189 – Turbidity
- MS5837 – Pressure and depth

### Visual Monitoring
ESP32-CAM with OV2640 camera.

## 6. Development Phases

### Phase 1: Basic Model Development
- Basic robotic fish structure.
- Mechanical body design.
- Tail movement mechanism.
- Initial ESP32 control planning.

### Phase 2: Electronics Integration
- Servo motor integration.
- ESP32 programming.
- Power supply design.
- Electronic connection testing.

### Phase 3: Sensor Integration
- Temperature measurement.
- TDS measurement.
- Turbidity measurement.
- Depth measurement.

### Phase 4: Camera Integration
- ESP32-CAM configuration.
- Image capture.
- Waterproof camera enclosure.

### Phase 5: Testing and Validation
- Mechanical movement testing.
- Sensor calibration.
- Waterproofing validation.
- Underwater performance testing.

## 7. Expected Applications

- Underwater environmental observation.
- Aquatic ecosystem monitoring.
- Water quality assessment.
- Underwater inspection.
- Marine research support.

## 8. Future Scope

- Autonomous underwater navigation.
- Real-time environmental data logging.
- Advanced underwater image processing.
- Obstacle detection.
- Improved fish-like propulsion.
- Long-duration underwater operation.

## 9. Current Project Status

**Development Stage: Basic Model Development**

The project is currently focused on developing the basic robotic fish model and planning the embedded control architecture.

Sensor integration, camera implementation, waterproofing, and underwater testing are planned future activities.

## 10. Conclusion

The Robotic Fish project provides an opportunity to explore biomimetic robotics, embedded systems, servo-based actuation, and underwater environmental monitoring.

The planned development will progressively transform the basic robotic model into an integrated underwater monitoring platform.

---

**Project Domain:** Robotics | Embedded Systems | IoT | Underwater Monitoring

**Controller:** ESP32

**Programming Language:** Embedded C++
