# Motorized Tape Measure Driver

## Introduction
This project was part of my AP Physics 2 final, specifically the last energy transfer within a larger Rube Goldberg contraption. A domino would fall, triggering a sensor, which in turn activated the motors to drive a tape measure vertically. I originally aimed for a 25-foot extension to break my class record (and last year’s), but due to practical limitations, I managed around 8 feet (still broke this year's record).

I’m still fairly novice to CAD and mechanical design, so this build was a crash course in tolerances, iterating on prototypes, and troubleshooting unexpected mechanical issues. I used my **Bambu Lab P1S** to print most of the parts in both **PLA** and **TPU** filaments.

[https://github.com/user-attachments/assets/6b1b6aa8-f43f-4f7a-9d7e-347c0948d33c](https://github.com/user-attachments/assets/6b1b6aa8-f43f-4f7a-9d7e-347c0948d33c)

<img src="https://github.com/user-attachments/assets/c855e882-6582-406c-947e-b412dc4ccfbe" width="375" alt="Main Assembly Photo">
<img src="https://github.com/user-attachments/assets/13406976-9949-4ce1-a7e1-22ab9fe750ff" width="375" alt="Mechanism in Action">


---

## Design Overview

### Final Design
The final device is fairly compact, designed to fit within a 60 × 60 × 60 cm box, with these main features:

- **Two Motorized Wheels:**  
  Grip the tape measure firmly to move it upward (and could move it downward, though unused).

- **Baseplate:**  
  A 3D-printed plate that houses the tape measure and supports the modular inserts.

- **Modular Inserts:**  
  Hold the motors, bearings, and steel shaft. These inserts are easily swappable for quick reprints and testing.

- **TPU Treads on Wheels:**  
  Provide traction. One tread design includes small diamond-shaped grips, and another has short walls to cradle the tape measure’s concavity.

#### Key Components

- **Motors:** Two [uxcell GA12-N20 6V 150RPM DC Gear Motors](https://www.amazon.com/dp/B07N1FJN3N) (encoders unused).
  
  <img src="https://github.com/user-attachments/assets/c31b64e7-0573-4076-8b50-4fe0fd1e5648" width="256" alt="Motor Mount">

- **Baseplate:** 3D-printed in PLA, with embedded nuts for mounting.

  <img src="https://github.com/user-attachments/assets/5b9b80b6-13d9-4dfb-a26d-ef27f1c29965" width="256" alt="Baseplate">

- **Wheel Hub:**  
  3D-printed in PLA, with embedded nuts for mounting. Circular hole for motor gearbox shaft coupler

  <img src="https://github.com/user-attachments/assets/1a7fbbd4-d1b1-4ac3-91cc-5ef1450495a7" width="512" alt="Wheel Hub">

- **TPU Treads:**  
  Flexible, rubber-like grip that I could manufacture at home.

  <img src="https://github.com/user-attachments/assets/20709778-e9b0-4e56-9dbe-9e8eafb8af16" width="512" alt="TPU Tread 1">  
  <img src="https://github.com/user-attachments/assets/7065bbb6-f9f5-4af2-83d3-15b5eff3f96c" width="512" alt="TPU Tread 2">

- **Modular Inserts:**  
  3D-printed in PLA, with embedded nuts for mounting.

  <img src="https://github.com/user-attachments/assets/e17ba553-5fa6-4e00-a1a2-8313cf6dafd6" width="512" alt="Modular Insert 1">  
  <img src="https://github.com/user-attachments/assets/24875e90-e150-4755-9177-6722f3048fc7" width="512" alt="Modular Insert 2">

- **608 Bearings & Steel Shaft:**  
  Stabilize the motor shafts to prevent bending.
  
  <img src="https://github.com/user-attachments/assets/a6bfdca6-c959-4610-ab15-ab014c3494e3" width="512" alt="608 Bearing Mount">

- **Tape Measure:**  
  A sturdy, heavy-duty type that isn’t too glossy.

---

## Process and Iterations

### Initial Concept
Initially, I wanted one motorized wheel paired with a passive wheel on the other side. The tape measure would run through these wheels, and the single motor would drive it upward. My early sketches were simple, but I quickly realized I’d need stronger support and better stability.

### Prototyping
1. **Bent Shafts:**  
   Applying enough pressure to grip the tape measure caused the motors’ tiny shafts to bend.

2. **Low Torque:**  
   A single motor lacked the power to extend the tape more than a few feet.

3. **Alignment Issues:**  
   Even a slight misalignment caused the tape measure to slip or bind.

**Solution Approaches**  
- Added a **steel rod** and **608 bearings** for extra shaft support.  
- Shifted to **two motorized wheels** to increase grip and torque.  
- Created **modular inserts** so I could easily reprint smaller parts (instead of reprinting a massive, single-piece baseplate) whenever I needed to tweak tolerances.

### Tread Evolution
- **Early Tread Design:** Inspired by FRC-style swerve wheels with small, tapered cylinders for grip.
- **Later Tread Design:** Changed to tapered diamonds and added sidewalls to keep the tape measure’s curved shape from slipping off. This final approach stabilized the tape and allowed it to go higher before collapsing.

---

## Technical Details

### Materials and 3D Printing
- **PLA** for most structural parts (baseplate, motor mounts, modular inserts).
- **TPU** for wheel treads to achieve a rubbery grip.
- Printed on a **Bambu Lab P1S**.
- **Embedded Nuts:** I paused the 3D prints at specific layer heights to insert nuts. This technique was used for both the baseplate and modular inserts to allow secure bolt mounting.

### Electronics
- **Controller:** [Arduino Mega 2560](https://www.amazon.com/ARDUINO-MEGA-2560-REV3-A000067)
- **Motor Driver:** [HiLetgo L298N](https://www.amazon.com/dp/B07BK1QL5T)
- **Time-of-Flight Sensor (TOF):** [VL53L1X](https://www.amazon.com/dp/B07F3TV3G4) for detecting the falling domino (final trigger)
- **Power Supply:** [30V 10A Bench Power Supply](https://www.amazon.com/dp/B08DJ1FDXV). Initially planned for batteries, but the rules allowed an external plug.
- **Misc. Wiring:** Jumper wires, alligator clips, ferrules—no soldering required.

### How It Works (Software Flow)
1. **Initialization:** The VL53L1X sensor measures a baseline distance repeatedly, averaging values for an offset.  
2. **Domino Trigger:** When a domino falls in front of the sensor, the measured distance changes significantly. If this difference crosses a threshold, the Arduino powers both motors.  
3. **Motor Control:** Both wheels spin at full speed to grip the tape measure and extend it upward. There’s a built-in time limit in the code to stop the motors eventually, so they don’t run indefinitely.  
4. **Stall Situation:** In practice, once the tape measure reached around 8–9 feet, the wheels began to stall. Ironically, this stalling “locked” the tape in place at a height high enough to impress my classmates, so I left it that way for the final demonstration.

---

## Testing and Results

### Performance
- Managed an 8-foot extension (short of the 25-foot goal, but still exceeded most classmates’ designs).
- The stall at 8 feet wasn’t intentional at first, but it worked to my advantage, preventing tape collapse.

### Challenges Overcome
- **Shaft Bending:** Solved with 608 bearings and a steel rod support.
- **Misalignment:** Reduced by carefully spacing the wheels and creating precisely toleranced inserts.
- **Tape Collapsing:** Addressed by inclining the entire mechanism so the tape measure’s natural concavity helped support itself.

---

## Lessons Learned

1. **CAD Tolerances Are Critical:** Even a 0.1 mm error in Fusion 360 can cause major alignment problems in the final assembly.  
2. **Mechanical Support:** Tiny motors need bearings and thicker shafts to prevent bending under load.  
3. **TPU is Tricky But Rewarding:** Getting the right tread design took a few tries, but once dialed in, it provided the grip I needed.  
   **You don’t want to know how many times it clogged my 3d printer...**  
4. **Iterate Early and Often:** Modular inserts saved me from reprinting the entire baseplate each time something changed.

---


## Future Improvements

- **Angle the Motors:** Rather than manually tilting the entire mechanism, I’d design angled motor mounts so the tape measure remains stable upright.
- **Higher-Torque Motors:** Ideally, 12 V motors with more torque would prevent stalling and might reach that 25 ft mark.
- **Custom Tape Measure Housing:** Integrating the tape measure into the baseplate more tightly could reduce overall size and improve reliability.

---

## Conclusion
Building this motorized tape measure driver was a huge learning experience for me as an aspiring engineering student, novice to CAD and mechanical design. Although I fell short of my ambitious 25-foot extension goal, I managed to reach about 8 feet—enough to stand out in my AP Physics 2 class. The project gave me hands-on practice in CAD (Computer Aided Design), torque requirements, tread design, and the value of constant iteration.

---

## Parts Used
- [Time-of-Flight Sensor VL53L1X](https://www.amazon.com/dp/B07F3TV3G4)
- [Hex Coupler (Early Prototypes)](https://www.amazon.com/dp/B08M3FY9MM)
- [uxcell GA12-N20 6V 150RPM DC Gear Motor](https://www.amazon.com/dp/B07N1FJN3N)
- [DC Bench Power Supply, 30V 10A](https://www.amazon.com/dp/B08DJ1FDXV)
- [Coupling 3 mm to 8 mm Bore](https://www.amazon.com/dp/B08H24HD3G)
- [8 mm Steel Shaft, 60 mm Long](https://www.amazon.com/dp/B0CQTFQ9C9)
- [SHKI 608 2RS Ball Bearings](https://www.amazon.com/SHKI/dp/B09PKD8QZZ)
- [Arduino Mega 2560](https://www.amazon.com/ARDUINO-MEGA-2560-REV3-A000067)
- [HiLetgo L298N](https://www.amazon.com/dp/B07BK1QL5T)

---

## Source Code
[View the Arduino Code Here](https://github.com/ArshansGithub/Motorized-Tape-Measure-Driver/blob/main/main.ino)

---

## Plastic Graveyard

Behold the resting place for every melted misadventure, spaghetti-laden failure, and 
tragically under-extruded prototype. It’s a towering testament to how many times 
I whispered, “It’ll be fine,” right before it absolutely wasn’t. 
May these casualties of CAD forever remind us to measure twice—and pray once.

<img src="https://github.com/user-attachments/assets/84abcfca-3123-4f40-8fd6-284436447b48" width="512" alt="Don't be like me">  

