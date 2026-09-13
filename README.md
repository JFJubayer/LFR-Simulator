# LFR Simulator Studio Pro

A professional-grade **Line Follower Robot (LFR) CAD, Wiring Matrix, Multi-File Arduino IDE, and 2D Physics Simulator**.

![LFR Studio Banner](https://img.shields.io/badge/Platform-Arduino%20%7C%20ESP32%20%7C%20STM32-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Deployment](https://img.shields.io/badge/Deploy-Vercel-black)

## Features

### 1. 🚀 Simulation Arena & Real-Time Physics
- 2D differential-drive kinematics simulating wheel separation, wheel diameter, caster physics, and sensor offset.
- Real-time optical sensor LED status (active green on track line, red on background).
- Trajectory breadcrumb trail and lap tracking.
- Live telemetry HUD: error metric ($e = \text{linePos} - 45$), $\Delta\text{Speed}$, motor PWM, and live Serial Monitor.

### 2. 🛠️ CAD & Hardware Customization
- **Microcontrollers:** Arduino Nano, Arduino Uno R3, Arduino Mega 2560, ESP32 DevKit, STM32 BluePill, Raspberry Pi Pico.
- **Sensors:** Digital vs Analog mode, 2 to 16 sensors, configurable pitch/spacing, forward distance from axle.
- **Motor Drivers:** L298N, TB6612FNG, DRV8833, L293D, Cytron Maker Drive (with internal voltage drop modeling).
- **Power & Batteries:** 1S, 2S, 3S LiPo, 4x AA, 9V, or custom voltage.
- **Chassis Shapes:** Aerodynamic Tapered Wedge, Rectangular, Oval, Circular.

### 3. 🔌 Interactive Wiring & Pin Connector Matrix
- Map motor driver direction/PWM pins and sensor channels to any microcontroller pin.
- Automatic PWM compatibility validation for motor speed enable pins (`enA`, `enB`).
- 1-click preset: "Load Your 5-File Project Pinout".

### 4. 💻 Multi-File Arduino IDE & In-Browser Compiler
- Multi-tab sketch editor preloaded with 5 `.ino` files:
  - `c_line_follower.ino`
  - `initialization.ino`
  - `sensor.ino`
  - `main.ino`
  - `motor_driver.ino`
- In-browser Arduino execution engine supporting `setup()`, `loop()`, `pinMode()`, `digitalRead()`, `digitalWrite()`, `analogRead()`, `analogWrite()`, `delay()`, `millis()`, `constrain()`, `abs()`, and `Serial`.
- Instant live compilation and flashing to the virtual robot.

### 5. 🗺️ Track & Map Studio
- **Presets:** Grand Prix Circuit, Figure-8 / S-Curves, 90° Corner Challenge, Slalom & Hairpins, Cross Intersection.
- **Freehand Draw Mode:** Draw custom competition tracks directly on the canvas.
- Configurable track line width and color contrast (White on Black or Black on White).

## Quick Start
Open `index.html` in any modern web browser or visit the live deployment.
