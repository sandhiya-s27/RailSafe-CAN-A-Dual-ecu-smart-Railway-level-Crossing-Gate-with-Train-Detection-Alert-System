🚆 RailSafe – Automatic Railway Level Crossing System Using CAN Protocol

📌 PROJECT OVERVIEW

RailSafe is an embedded-based automatic railway level crossing system designed to improve railway crossing safety by automating gate operations using train detection and CAN (Controller Area Network) communication.
The system consists of two LPC2129 ARM7 microcontrollers (ECUs) that communicate through the CAN protocol.
ECU1 detects train movement using IR sensors, maintains the train count, and transmits train information to ECU2. ECU2 receives the information and controls the railway gate using a servo motor, red LED, and buzzer.
The system uses CAN communication to provide reliable data exchange between the two controllers.


🎯 OBJECTIVES
Automate railway level crossing gate operations.
Detect train entry and exit using IR sensors.
Maintain the number of trains detected.
Establish communication between two microcontrollers using CAN protocol.
Control railway gate operation using a servo motor.
Provide visual and audio alerts using an LED and buzzer.
Improve railway crossing safety through embedded automation.


🏗️ SYSTEM ARCHITECTURE
The project is divided into two main control units:
ECU1 – Train Detection and Monitoring Unit
Microcontroller: LPC2129 (ARM7)
COMPONENTS
IR Sensor 1 – Train entry detection.
IR Sensor 2 – Train exit detection.
16×2 LCD – Displays train status, train count, and gate status.
CAN Controller – Transmits and receives information through CAN communication.

RESPONSIBILITIES
Detects train entry using IR1.
Detects train exit using IR2.
Maintains the train count.
Displays train information on the LCD.
Transmits train status through CAN (Message ID: 0x100) every 100 ms.
Receives gate status information through CAN.
ECU2 – Railway Gate Control Unit
Microcontroller: LPC2129 (ARM7)
COMPONENTS
CAN Controller – Receives train information.
Servo Motor – Opens and closes the railway gate.
Red LED – Provides a visual warning.
Buzzer – Provides an audio warning.

RESPONSIBILITIES
Receives train information from ECU1 through CAN.
Processes the received train status.
Uses a 3-second safety delay before gate operation.
Controls the servo motor to close or open the railway gate.
Activates the red LED and buzzer during the warning/gate-closed condition.
Communicates gate status back to ECU1.


⚙️ HARDWARE COMPONENTS
Component
Purpose
LPC2129 × 2
Main controllers
IR Sensors × 2
Train entry and exit detection
TJA1050 × 2
CAN transceivers
16×2 LCD
Displays train and gate status
Servo Motor
Railway gate control
Red LED
Visual warning
Buzzer
Audio warning
120Ω Resistors
CAN bus termination
Power Supply
Powers the system


🔄 WORKING PRINCIPLE
Step 1 – Train Detection
IR1 detects the approaching train and ECU1 updates the train count.
Step 2 – Train Exit Detection
IR2 detects the train leaving the crossing section, and ECU1 updates the train count accordingly.
Step 3 – CAN Communication
ECU1 transmits train status to ECU2 using CAN 2.0A communication at 1 Mbps.
Step 4 – Safety Timing
ECU2 receives the train information and applies the required 3-second safety timing before gate operation.
Step 5 – Gate Control
ECU2 operates the servo motor to control the railway gate. The red LED and buzzer provide warning indications.
Step 6 – Status Monitoring
ECU2 communicates gate status back to ECU1, and the LCD displays the train and gate information.


🔌 COMMUNICATION PROTOCOL
Parameter
Specification
Protocol
CAN
CAN Version
CAN 2.0A
Data Rate
1 Mbps
Controllers
LPC2129
Transceiver
TJA1050
Termination
120Ω
Train Status Message ID
0x100
Transmission Interval
100 ms


💻 SOFTWARE AND DEVELOPMENT TOOLS
Embedded C
Keil µVision IDE
LPC2129 ARM7 Microcontroller
CAN Protocol
Proteus (Circuit Simulation)
📚 CONCEPTS IMPLEMENTED
ARM7 Microcontroller Programming
GPIO Interfacing
IR Sensor Interfacing
LCD Interfacing
CAN Protocol Communication
CAN Message Transmission and Reception
Timer and Interrupt Programming
Servo Motor Control
Embedded System Integration

🚀 EXPECTED OUTCOME
The RailSafe system demonstrates automatic railway crossing control using two embedded controllers communicating over a CAN network.
It integrates train detection, real-time status monitoring, communication between ECUs, and automated gate operation to demonstrate a safety-oriented embedded system.

