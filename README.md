# OS-Diorama: CPU Scheduling Algorithm Demonstration

![OS-Diorama Demo](https://github.com/user-attachments/assets/589fed8e-440f-481b-b218-1899ee5e01aa)

## Overview

OS-Diorama is an interactive physical demonstration system that visualizes CPU scheduling algorithms used in operating systems. The project combines Arduino hardware with a web-based interface to provide a tangible and visual representation of how different CPU scheduling algorithms work.

## Features

- **Visual Demonstration**: Uses 5 LEDs and a servo motor to physically represent process execution
- **Multiple Algorithms**: Supports three common CPU scheduling algorithms:
  - Shortest Job First (SJF) Non-Preemptive
  - Shortest Job First (SJF) Preemptive
  - Round Robin (with configurable time quantum)
- **Interactive Web Interface**: User-friendly interface for configuring processes and scheduling parameters
- **Real-time Visualization**: Timeline view showing process execution order and timing

## Hardware Requirements

- Arduino board (e.g., Arduino Uno)
- 5 LEDs (different colors recommended)
- 1 Servo motor
- Resistors for LEDs (220Ω recommended)
- Jumper wires
- Breadboard

## Hardware Setup

1. Connect the 5 LEDs to Arduino pins 2, 3, 4, 5, and 6 (with appropriate resistors)
2. Connect the servo motor to Arduino pin 9
3. Power the Arduino via USB (which will also provide the serial connection)

## Pin Configuration

| Component | Arduino Pin |
|-----------|------------|
| LED 1     | Pin 2      |
| LED 2     | Pin 3      |
| LED 3     | Pin 4      |
| LED 4     | Pin 5      |
| LED 5     | Pin 6      |
| Servo     | Pin 9      |

## Software Components

### Arduino Code (`arduino code/main.ino`)

The Arduino code handles:
- Receiving scheduling data from the web interface via Serial
- Parsing process execution timelines
- Controlling LEDs to represent active processes
- Moving the servo to indicate which process is currently running

### Web Interface (`arduino_frontend/main.html`)

The web interface allows users to:
- Select different CPU scheduling algorithms
- Configure processes with arrival and burst times
- Visualize the scheduling timeline
- Connect to the Arduino via WebSerial API
- Send scheduling data to the Arduino for physical demonstration

## Usage Instructions

1. **Upload Arduino Code**:
   - Open the `arduino code/main.ino` file in the Arduino IDE
   - Connect your Arduino board
   - Upload the code to the board

2. **Open Web Interface**:
   - Open the `arduino_frontend/main.html` file in a WebSerial-compatible browser (Chrome or Edge)

3. **Configure and Run Demonstration**:
   - Select a scheduling algorithm
   - Configure processes (up to 5) with arrival and burst times
   - Click "Start Demonstration" to see the timeline visualization
   - Click "Connect to Arduino" to establish a connection with the Arduino board
   - Click "Send to Arduino" to start the physical demonstration

4. **Observe the Demonstration**:
   - LEDs will light up to represent which process is currently running
   - The servo motor will move to different positions to indicate the active process
   - The web interface console will display real-time status updates

## Supported Algorithms

### Shortest Job First (SJF) Non-Preemptive
Processes are executed in order of burst time. Once a process starts, it runs to completion.

### Shortest Job First (SJF) Preemptive
If a new process arrives with a shorter burst time than the remaining time of the current process, the current process is preempted.

### Round Robin
Each process gets a small unit of CPU time (time quantum). After this time has elapsed, the process is preempted and added to the end of the ready queue.

## Communication Protocol

The web interface sends scheduling data to the Arduino using the following format:

- **SJF Non-Preemptive**: `SJF:0|P1,100,200;P2,300,400;...`
- **SJF Preemptive**: `SJF:1|P1,100,200;P2,300,400;...`
- **Round Robin**: `RR:timeQuantum|P1,100,200;P2,300,400;...`

Where:
- `P1,100,200` represents Process ID 1, starting at 100ms, ending at 200ms

## Technical Requirements

- Modern web browser with WebSerial API support (Chrome or Edge)
- Arduino IDE for uploading code to the Arduino board
- Arduino with USB connection

## Educational Purpose

OS-Diorama is designed as an educational tool to help visualize and understand CPU scheduling algorithms, which are typically abstract concepts in operating systems theory. By providing a physical representation, it makes these concepts more tangible and easier to comprehend.

## Future Enhancements

- Support for additional scheduling algorithms (e.g., Priority Scheduling, FCFS)
- Enhanced visualizations with wait time and turnaround time calculations
- Mobile-friendly interface
- 3D-printable housing for the hardware components

---

*Created: April 22, 2025*
