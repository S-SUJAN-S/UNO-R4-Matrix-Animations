/*
  UNO R4 Guide: Merging Bars Animation

  Purpose: Creates a continuous animation where two vertical bars start
  at the edges, move to the center to merge, and then reverse
  back to the edges.
*/

// Include the necessary library for LED matrix control.
#include "Arduino_LED_Matrix.h"

// Create an instance of the ArduinoLEDMatrix class.
ArduinoLEDMatrix matrix;

// --- Animation Parameters ---
const int FRAME_DELAY = 75; // Milliseconds between animation frames (lower is faster)
const int ANIMATION_STEPS = 6; // Number of steps for bars to reach the center

// --- Global Frame Buffer ---
// This array holds the current state of all 96 LEDs.
uint8_t frame[8][12];

// Variables for the non-blocking timer
unsigned long previousMillis = 0;
int currentStep = 0;
bool isMovingInward = true; // Variable to track animation direction

void setup() {
  // Initialize the LED matrix.
  matrix.begin();
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if enough time has passed to calculate and show the next frame
  if (currentMillis - previousMillis >= FRAME_DELAY) {
    // Save the time of this frame change
    previousMillis = currentMillis;

    // --- Animation Logic ---

    // 1. Clear the entire frame buffer for the new frame.
    for (int r = 0; r < 8; r++) {
      for (int c = 0; c < 12; c++) {
        frame[r][c] = 0;
      }
    }

    // 2. Draw the two vertical bars for the current step.
    int leftBarPosition = currentStep;
    int rightBarPosition = 11 - currentStep;

    for (int r = 0; r < 8; r++) {
      // Draw the left bar
      if (leftBarPosition >= 0 && leftBarPosition < 12) {
        frame[r][leftBarPosition] = 1;
      }
      // Draw the right bar
      if (rightBarPosition >= 0 && rightBarPosition < 12) {
        frame[r][rightBarPosition] = 1;
      }
    }

    // --- Render the Frame ---
    // Display the newly calculated frame on the LED matrix.
    matrix.renderBitmap(frame, 8, 12);

    // --- Update Step Counter for Reversing Effect ---
    // Change direction when the bars meet in the middle or return to the edges.
    if (currentStep >= ANIMATION_STEPS) {
      isMovingInward = false;
    } else if (currentStep <= 0) {
      isMovingInward = true;
    }

    // Move to the next step based on the current direction.
    if (isMovingInward) {
      currentStep++;
    } else {
      currentStep--;
    }
  }
}
