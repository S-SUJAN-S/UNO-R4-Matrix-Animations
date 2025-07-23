/*
  UNO R4 Guide: Programmatic Rain Animation

  Purpose: Creates a continuous, non-repeating "falling rain" animation
  by programmatically calculating the position of each raindrop for every frame.
  This version uses a non-blocking timer for a smooth, continuous loop and
  ensures raindrops are not generated in adjacent columns for a clearer look.
*/

// Include the necessary library for LED matrix control.
#include "Arduino_LED_Matrix.h"

// Create an instance of the ArduinoLEDMatrix class.
ArduinoLEDMatrix matrix;

// --- Animation Parameters ---
const int FRAME_DELAY = 100; // Milliseconds between animation frames (lower is faster)

// --- Global Frame Buffer ---
// This array holds the current state of all 96 LEDs.
// We will modify this array directly to create the animation.
uint8_t frame[8][12];

// Variables for the non-blocking timer
unsigned long previousMillis = 0;

void setup() {
  // Initialize the LED matrix.
  matrix.begin();
  // Ensure the random number generator is seeded differently each time
  randomSeed(analogRead(A0));
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if enough time has passed to calculate and show the next frame
  if (currentMillis - previousMillis >= FRAME_DELAY) {
    // Save the time of this frame change
    previousMillis = currentMillis;

    // --- Animation Logic ---

    // 1. Shift all existing raindrops down by one row.
    // We loop from the bottom row up to avoid overwriting pixels prematurely.
    for (int r = 7; r > 0; r--) {
      for (int c = 0; c < 12; c++) {
        frame[r][c] = frame[r - 1][c];
      }
    }

    // 2. Clear the top row to make space for new raindrops.
    for (int c = 0; c < 12; c++) {
      frame[0][c] = 0;
    }

    // 3. Randomly generate new raindrops on the top row.
    for (int c = 0; c < 12; c++) {
      // Use a random check to decide if a new drop should appear.
      if (random(5) == 0) {
        // --- IMPROVEMENT: Check the surrounding 8 pixels (5 relevant ones) ---
        bool isSpaceClear = true;
        // Check left
        if (c > 0 && frame[0][c - 1] == 1) isSpaceClear = false;
        // Check right
        if (c < 11 && frame[0][c + 1] == 1) isSpaceClear = false;
        // Check 3 pixels below
        if (frame[1][c] == 1) isSpaceClear = false;
        if (c > 0 && frame[1][c - 1] == 1) isSpaceClear = false;
        if (c < 11 && frame[1][c + 1] == 1) isSpaceClear = false;

        if (isSpaceClear) {
          frame[0][c] = 1; // A new drop appears
        }
      }
    }

    // --- Render the Frame ---
    // Display the newly calculated frame on the LED matrix.
    matrix.renderBitmap(frame, 8, 12);
  }
}
