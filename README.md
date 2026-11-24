 🚆 RailSafe – Railway Level Crossing Safety System Using CAN Protocol

📌 Project Overview
RailSafe is an embedded systems project designed to automate railway level crossing gate operations using CAN communication. It uses two LPC2129 ARM7 microcontrollers (ECU1 and ECU2) to detect train movement, exchange status information, and control the railway gate automatically.

⚙️ Hardware Components
- LPC2129 ARM7 Microcontrollers (2)
- IR Sensors (2)
- 16×2 LCD
- TJA1050 CAN Transceivers
- Servo Motor (SG90)
- Red LED and Buzzer
- 120Ω Termination Resistors

 🔄 Working Principle
 
 ECU1 – Train Detection**
- Detects train entry and exit using IR sensors.
- Maintains train count.
- Displays train count and train/gate status on LCD.
- Transmits train status to ECU2 through CAN.

ECU2 – Gate Control**
- Receives train status from ECU1.
- Controls the railway gate using a servo motor.
- Activates the red LED and buzzer for warning indications.
- Sends gate status back to ECU1.

📡 Communication Protocol
- Protocol: CAN 2.0A
- Frame Type: Standard Frame (11-bit)
- Bit Rate: 1 Mbps
- CAN Transceiver: TJA1050
- CAN Message ID: `0x100` (TRAIN_STATUS)

💻 Software and Tools
- Embedded C
- Keil µVision IDE
- Flash Magic
- LPC2129 ARM7
- CAN Protocol

 ⭐ Key Features
- Automatic railway gate operation.
- Real-time train detection and counting.
- CAN-based communication between two ECUs.
- LCD status monitoring.
- Visual and audio warning indications.
- Communication timeout handling.
