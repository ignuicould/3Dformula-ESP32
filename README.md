# 💻 ESP32 Retro 3D Wireframe Renderer

A proof-of-concept project demonstrating the fundamental principles of 3D computer graphics by porting a basic JavaScript Canvas renderer to flicker-free C++ code on an embedded system (Lilygo T-Display).

This project highlights how core mathematical transformations are universal, while the graphics I/O layer requires platform-specific optimization, such as double buffering.

## ✨ Key Features

* **Universal 3D Pipeline:** Implements Model, Projection, and Viewport transformations using pure C++ math.

* **Flicker-Free Rendering:** Uses the `TFT_eSprite` class for **Double Buffering** to ensure smooth, high-speed animation on the LCD.

* **Target Hardware:** Developed for the **Lilygo T-Display (ESP32)** with an ST7789 TFT screen.

* **Retro Aesthetics:** Achieves classic, 80s-style wireframe vector graphics performance on modern, affordable hardware.

## ⚙️ Hardware and Prerequisites

| Component | Requirement | Notes | 
 | ----- | ----- | ----- | 
| **Microcontroller** | Lilygo TTGO T-Display (ESP32) | Other ESP32 boards with a TFT display may work with minor pin adjustments. | 
| **Libraries** | `TFT_eSPI` | The core library for interacting with the screen and sprites. | 
| **Input Files** | Arduino Source Files, `cube.h`, `penger.h` | Logic + Models translated from the original Javascript | 

## 💾 Source Code Versions

The repository includes three distinct C++ implementations demonstrating the evolution of the embedded rendering pipeline:

* **`...Direct.old`**: The initial, unoptimized version. It draws directly to the LCD using `tft.drawLine()`, resulting in noticeable screen **flickering**.
* **`...DoubleBuffered.old`**: The final, optimized version. It uses `TFT_eSprite` to draw to an off-screen memory buffer (sprite) before "flipping" the completed frame to the LCD, achieving a **flicker-free** animation.
* **`...Debug.old`**: Contains extra code, visual guides, and verbose comments used during the development phase for debugging and verification of the mathematical transformations.

## 📐 The Universal Graphics Pipeline

The core challenge is translating a 3D point $(X, Y, Z)$ into a 2D screen pixel $(x, y)$. This process is identical in both JavaScript and C++.

## 🚀 The Embedded Optimization: Double Buffering

Drawing multiple lines directly to the LCD screen (`tft.drawLine()`) causes visual flicker. The solution is using an off-screen memory buffer, known as a **Sprite** (`TFT_eSprite`), which is the embedded equivalent of double buffering.

### Flicker Fix Comparison

This comparison shows the critical change: shifting the drawing target from the hardware object (`tft`) to the memory buffer (`spr`).

**Before: Direct-to-Screen (Clears the visible display hardware.)**
```cpp
void clear_screen() {
  tft.fillScreen(BACKGROUND_COLOR); // Direct hardware access
}
``` 
**After: Double-Buffered (Clears the invisible memory buffer.)**
```cpp
void clear_sprite() {
  spr.fillSprite(BACKGROUND_COLOR); // Draw to RAM
}
```

The process is completed with `spr.pushSprite(0, 0);` which "flips" the completed frame onto the screen in a single, rapid operation.

---

## 🌟 Inspiration

This entire project is a C++ port inspired by the excellent YouTube video: **"One Formula That Demystifies 3D Graphics"** by **Tsoding**.
[YouTube Video](https://www.youtube.com/watch?v=qjWkNZ0SXfo)
[GitHub Repo](https://github.com/tsoding/formula)

---
