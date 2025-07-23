/*
  UNO R4 Guide: Reversing Bars Animation

  Purpose: Creates a continuous, reversing "ping-pong" animation.
  The interlaced bars move to one side, then reverse direction and
  move back to the other side.
*/

// Include the necessary library for LED matrix control.
#include "Arduino_LED_Matrix.h"

// Create an instance of the ArduinoLEDMatrix class.
ArduinoLEDMatrix matrix;

// --- Animation Parameters ---
const int FRAME_DELAY = 75; // Milliseconds between animation frames (lower is faster)
const int BAR_WIDTH = 12;    // The width of each horizontal bar in pixels
const int ANIMATION_RANGE = 12 + BAR_WIDTH; // The number of steps for a full traversal

// --- Global Frame Buffer ---
// This array holds the current state of all 96 LEDs.
uint8_t frame[8][12];

// Variables for the non-blocking timer
unsigned long previousMillis = 0;
int currentFrame = 0;
bool isMovingForward = true; // Variable to track animation direction

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

    // 2. Draw the bars for the current frame.
    
    // --- Left-to-Right Bars (Even Rows) ---
    // Calculate the starting position of the left-side bars
    int left_start_col = currentFrame - BAR_WIDTH;
    // Draw the bars
    for (int c = 0; c < BAR_WIDTH; c++) {
      int current_col = left_start_col + c;
      // Only draw if the pixel is within the screen bounds (0 to 11)
      if (current_col >= 0 && current_col < 12) {
        frame[0][current_col] = 1; // Row 1
        frame[2][current_col] = 1; // Row 3
        frame[4][current_col] = 1; // Row 5
        frame[6][current_col] = 1; // Row 7
      }
    }

    // --- Right-to-Left Bars (Odd Rows) ---
    // Calculate the starting position of the right-side bars
    int right_start_col = (ANIMATION_RANGE - 1) - currentFrame;
    // Draw the bars
    for (int c = 0; c < BAR_WIDTH; c++) {
      int current_col = right_start_col - c;
       // Only draw if the pixel is within the screen bounds (0 to 11)
      if (current_col >= 0 && current_col < 12) {
        frame[1][current_col] = 1; // Row 2
        frame[3][current_col] = 1; // Row 4
        frame[5][current_col] = 1; // Row 6
        frame[7][current_col] = 1; // Row 8
      }
    }

    // --- Render the Frame ---
    // Display the newly calculated frame on the LED matrix.
    matrix.renderBitmap(frame, 8, 12);

    // --- Update Frame Counter for Reversing Effect ---
    // Change direction at the ends of the animation sequence.
    // This logic allows the animation to move completely off-screen before reversing.
    if (currentFrame <= 0) {
      isMovingForward = true;
    } else if (currentFrame >= ANIMATION_RANGE) { // THE FIX IS HERE
      isMovingForward = false;
    }

    // Move to the next frame based on the current direction.
    if (isMovingForward) {
      currentFrame++;
    } else {
      currentFrame--;
    }
  }
}
