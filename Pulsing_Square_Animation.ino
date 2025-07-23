/*
  UNO R4 Guide: Programmatic Pulsing Square Animation

  Purpose: Demonstrates how to create a dynamic "pulsing" animation by
  programmatically modifying a 2D bitmap frame buffer in real-time.
*/

// Include the necessary library for LED matrix control.
#include "Arduino_LED_Matrix.h"

// Create an instance of the ArduinoLEDMatrix class.
ArduinoLEDMatrix matrix;

// --- Global Frame Buffer ---
// Declare the 8x12 frame buffer as a global variable. This allows it to
// persist and be modified across multiple iterations of the loop() function.
uint8_t frame[8][12];

// --- Animation Parameters ---
int squareSize = 0;      // Current size of the square
bool growing = true;     // Direction of animation (growing or shrinking)
int animationSpeed = 75; // Delay in milliseconds between frames

void setup() {
  // Initialize the LED matrix.
  matrix.begin();
}

void loop() {
  // --- Animation Logic ---
  // Update the size of the square for the next frame.
  if (growing) {
    squareSize++;
    if (squareSize >= 4) { // Max size is a 4x4 inner square
      growing = false;
    }
  } else {
    squareSize--;
    if (squareSize <= 0) { // Min size is 0
      growing = true;
    }
  }

  // --- Drawing Logic ---
  // 1. Clear the entire frame buffer by setting all pixels to 0 (OFF).
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 12; c++) {
      frame[r][c] = 0;
    }
  }

  // 2. Draw the new square based on the current 'squareSize'.
  // The square is centered on the matrix.
  // The offsets calculate the boundaries for the current size.
  for (int r = 4 - squareSize; r <= 3 + squareSize; r++) {
    for (int c = 6 - squareSize; c <= 5 + squareSize; c++) {
      // Bounds check to ensure we don't write outside the array
      if (r >= 0 && r < 8 && c >= 0 && c < 12) {
        frame[r][c] = 1; // Set pixel to ON
      }
    }
  }

  // --- Render the Frame ---
  // Display the newly drawn frame on the LED matrix.
  matrix.renderBitmap(frame, 8, 12);

  // --- Animation Timing ---
  // Wait for a short period to control the speed of the animation.
  delay(animationSpeed);
}
