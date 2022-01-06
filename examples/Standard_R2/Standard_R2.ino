#include "NeoPixelPSI.h"

NeoPixelPSI fpsi(3); // Front PSI on pin 3
NeoPixelPSI rpsi(4); // Rear PSI on pin 4

void setup() {
     Serial.begin(115200);
     rpsi.set_color(1, 0, 255, 0);	// Set the rear PSI colours
     rpsi.set_color(2, 128, 128, 128);  // Without this it does the standard front colours
}

void loop() {
  fpsi.animate();
  rpsi.animate();
}

