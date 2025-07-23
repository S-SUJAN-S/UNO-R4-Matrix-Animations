/*
  UNO R4 Guide: Static Heart Display

  Purpose: Displays a single, static, well-proportioned heart icon on the
  12x8 LED matrix. This design is centered and contained within the matrix.
*/

// Include the necessary library for LED matrix control.
#include "Arduino_LED_Matrix.h"

// Create an instance of the ArduinoLEDMatrix class.
ArduinoLEDMatrix matrix;

// --- Centered and Contained Heart Bitmap ---
// This 8x8 pixel heart is designed for the best possible symmetry and
// centering on the 12x8 matrix, ensuring it does not touch the edges.
uint8_t heart_bitmap[8][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  // Initialize the LED matrix.
  matrix.begin();

  // Display the heart bitmap on the matrix. This function is designed
  // for the intuitive 2D byte array format.
  matrix.renderBitmap(heart_bitmap, 8, 12);
}

void loop() {
  // The loop is empty because the Arduino_LED_Matrix library automatically
  // handles refreshing the display in the background using a hardware timer.
}