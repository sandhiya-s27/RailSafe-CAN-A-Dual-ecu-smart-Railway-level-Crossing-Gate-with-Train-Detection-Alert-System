RailSafe CAN: Dual-ECU Smart Railway Level Crossing Gate:

An automatic railway level crossing built on two LPC2129 (ARM7) ECUs connected by a CAN bus.
ECU1 detects the train and shows live status. ECU2 closes the gate, drives the warning lights and
sounds the buzzer. If CAN communication is lost, the crossing goes to a safe state: gate closed, red
light on, buzzer on.

Features:-
Two-sensor train detection (IR1 entry, IR2 exit) with a train counter, so the gate opens only after
every train has left
20 ms software debounce on both IR sensors
Servo gate that moves in small steps (no sudden swing)
3 second warning (flashing red light and buzzer) before the gate starts closing
2 second safety delay after the last train leaves before the gate reopens
16x2 LCD dashboard: train state, train count, gate state, ECU2 link status
CAN 2.0A link with 100 ms cyclic messages and an alive counter in every frame
Fail-safe on communication loss (500 ms timeout) and on an emergency frame
Transmit timeout in the CAN driver, so a missing node cannot freeze the main loop

System overview:-
Layer Unit Role
Detection ECU1 IR1, IR2, LCD dashboard, sends TRAIN_STATUS
Communication CAN bus Twisted pair, 120 ohm termination at both ends, TJA1050 transceivers
Action ECU2 Servo gate, red and green LEDs, buzzer, sends GATE_STATUS

CAN messages

ID Name Direction DLC Payload
0x100 TRAIN_STATUS
ECU1 to
ECU2

4
B0 state (0 clear, 1 approaching, 2 on crossing, 3
cleared), B1 train count, B2 distance (0), B3 alive
counter

0x200 GATE_STATUS

ECU2 to
ECU1

4
B0 gate (0 open, 1 closing, 2 closed, 3 opening), B1
signal, B2 buzzer, B3 alive counter

0x300 EMERGENCY to ECU2 1

B0 = 0xFF forces gate closed, red light and buzzer
on

Both frames are sent every 100 ms. ECU2 ignores a TRAIN_STATUS frame whose alive counter has not
changed.
Operation
1. Power-up: gate open, green light on, LCD shows CLEAR.
2. IR1 triggers: train count goes up, state becomes APPROACHING.
3. ECU2 flashes the red light and sounds the buzzer. After 3 seconds the servo lowers the gate.
4. Train on the crossing: gate closed, red light steady.
5. IR2 triggers: train count goes down. At count 0, after a 2 second wait, ECU1 sends CLEARED.
6. ECU2 lifts the gate, turns green on and the buzzer off.
7. Two trains: the gate stays closed until the count returns to 0.
Fail-safe behaviour

Condition Result
ECU2 gets no valid TRAIN_STATUS for 500 ms Gate closes, red light on, buzzer on
Emergency frame 0x300 with 0xFF Same safe state, stays latched until reset
ECU1 gets no GATE_STATUS for 500 ms LCD shows ECU2 LOST , ECU1 keeps sending
Train count above 0 Gate never opens

Pin map (as used in the code)
ECU1

Signal Pin
IR1 (entry) P1.16
IR2 (exit) P1.17
LCD D4 to D7 P0.16 to P0.19
LCD RS / E P0.5 / P0.6
CAN2 RD2 / TD2 P0.23 / P0.24

ECU2

Signal Pin
Servo (PWM2) P0.7
Red LED P1.16
Green LED P1.17
Buzzer (active low) P1.18
CAN2 RD2 / TD2 P0.23 / P0.24
CAN wiring: CAN-H to CAN-H, CAN-L to CAN-L, common ground. Power the servo from its own 5 V
supply and join it to the logic supply at ground only.

Hardware

Qty Component
2 LPC2129 ARM7 boards
2 TJA1050 CAN transceivers
2 IR obstacle sensor modules
1 16x2 LCD
1 SG90 / MG90S servo with gate arm
1 set Red and green LEDs
1 Buzzer

Qty Component
2 120 ohm resistors (bus termination)
1 Model track with toy train, 5 V supply with 3.3 V regulator
Optional: HC-SR04 ultrasonic sensor for approach distance (planned, not in the current firmware).
Repository structure
RailSafe-CAN/
├── README.md
├── block_diagram.png
├── ECU1/
│ ├── ecu1_main.c
│ ├── header.h CAN message struct, state and ID defines
│ ├── can_driver.h can2_init, can2_tx, can2_rx
│ ├── timer0_delay.h delay_milliseconds
│ ├── timerdelay.h Timer1 init and 1 ms ISR
│ ├── lcd_header4bit.h LCD driver (4-bit)
│ ├── titledisplay.h startup banner
│ ├── ir_check.h IR debounce and train counter
│ ├── safety.h 2 s safety wait
│ ├── ecu1_tx.h send TRAIN_STATUS
│ ├── ecu1_rx.h receive GATE_STATUS
│ ├── timeout.h communication timeout
│ ├── lcd_display.h live dashboard
│ └── Startup.s
└── ECU2/
├── ecu2_main.c
├── header.h
├── can_driver.h
├── timer_delay.h Timer0 init and 1 ms ISR
├── gpio.h LED and buzzer pins
├── pwm.h PWM2 for the servo
├── servo_control.h gate open and close
├── train_status.h decode TRAIN_STATUS and EMERGENCY
├── signal.h LEDs and buzzer logic
├── gatestatus.h send GATE_STATUS
└── Startup.s
The .h files other than header.h and can_driver.h contain function bodies. They are included by
ecu*_main.c after the global variables and must not be added to the project as separate source files.

Build and flash
1. Open Keil uVision4. Create one project per ECU ( ECU1/ and ECU2/ ) for the LPC2129.
2. Add Startup.s and the ecu*_main.c file to the project. Do not add the other headers as sources.
3. Rebuild (F7). Flash the .hex file with Flash Magic.
4. Connect the CAN bus and power both boards.

Testing

Test Expected result
Train passes IR1 and IR2 Count goes up at IR1 and down at IR2
Trigger APPROACHING 3 s warning, then gate reaches closed
Train passes IR2 Gate reopens after the 2 s safety delay
Two trains before IR2 Gate stays closed until the count is 0
Disconnect the CAN wire Gate closes, red and buzzer on within 0.5 s, LCD shows ECU2 LOST

Limitations
Prototype scale, toy train at short range. Real tracks need track circuits or axle counters.
IR sensors are affected by sunlight and dirt.
Single-track layout assumed.
The ultrasonic sensor is not implemented yet.

Future work
Second crossing ECU, station-to-crossing messages, GSM/IoT alerts to a control room, camera or
radar for vehicles on the crossing, solar backup, CAN FD.

Tools
Keil uVision4 (ARM7), Flash Magic, embedded C with register-level LPC21xx drivers.
References
Bosch, CAN Specification Version 2.0, 1991
ISO 11898-1, Road vehicles: Controller Area Network

NXP LPC2129 datasheet and user manual
NXP TJA1050 datasheet
