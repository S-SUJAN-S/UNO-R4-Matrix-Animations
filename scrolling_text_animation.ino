/*
  UNO R4 Guide: Scrolling Text

  Purpose: Demonstrates how to display a scrolling text message on the
  12x8 LED matrix using the ArduinoGraphics library integration.
*/

// --- CRITICAL INCLUDE ORDER ---
// To use the graphics APIs for the matrix, ArduinoGraphics.h MUST be included
// BEFORE Arduino_LED_Matrix.h. Failure to do so will result in compilation errors.
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

// Create an instance of the ArduinoLEDMatrix class.
ArduinoLEDMatrix matrix;

void setup() {
  // Initialize the LED matrix.
  matrix.begin();
}

void loop() {
  // This entire block prepares and executes one full scroll of the text.
  // It will repeat each time the loop() runs.

  // The drawing process must be wrapped between beginDraw() and endDraw().
  matrix.beginDraw();

  // Set the "color" for the text. For the monochrome matrix, 0xFFFFFFFF means ON.
  matrix.stroke(0xFFFFFFFF);

  // Set the scroll speed in milliseconds per pixel step. Lower is faster.
  matrix.textScrollSpeed(60);

  // Select the font for the text. Other options like Font_4x6 are available.
  // This is a required step for text to be visible.
  matrix.textFont(Font_5x7);

  // Set the initial properties for the text drawing operation.
  // Parameters are (x, y, color). The (0, 1) position provides good vertical alignment.
  matrix.beginText(0, 1, 0xFFFFFFFF);

  // Add the character string to the drawing buffer.
  matrix.println(" Welcome ");

  // Finalize the text operation and specify the scrolling direction.
  matrix.endText(SCROLL_LEFT);

  // Commit all drawing operations to the matrix. This starts the animation.
  matrix.endDraw();
}
