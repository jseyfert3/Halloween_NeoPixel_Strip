// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     16 // (A2)

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  150 // 30 LED/m, 5 m strip

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  randomLights(60000, 25, 4);
  purpleChaseOnOrange(5, 10, 5); // speed, length, numLoops
  alternatePurpleAndOrange(10); //num cycles
}

void alternatePurpleAndOrange(int loops) {
  while (loops > 0) {
    for(int i = 0; i <= LED_COUNT; i = i + 2) {
      strip.setPixelColor(i, 255, 0, 200);
    }
    for(int i = 1; i <= LED_COUNT; i = i + 2) {
      strip.setPixelColor(i, 200, 25, 0);
    }
    strip.show();

    delay(1000);

    for(int i = 1; i <= LED_COUNT; i = i + 2) {
      strip.setPixelColor(i, 255, 0, 200);
    }
    for(int i = 0; i <= LED_COUNT; i = i + 2) {
      strip.setPixelColor(i, 200, 25, 0);
    }
    strip.show();

    delay(1000);

    loops--;
  }
}

void purpleChaseOnOrange(int purpleSpeed, int purpleLength, int loops) {

  if(purpleLength >= strip.numPixels()) purpleLength = strip.numPixels() - 1;

  int      head          = purpleLength - 1;
  int      tail          = 0;
//  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;

  for(;;) { // Repeat forever (or until a 'break' or 'return')
    for(int i=0; i<strip.numPixels(); i++) {  // For each pixel in strip...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip.setPixelColor(i, 255, 0, 200); // Set purple section
      } else {
        strip.setPixelColor(i, 200, 25, 0); // set background to orange
      }
    }

    strip.show(); // Update strip with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > purpleSpeed) { // Time to update head/tail?
      if(++head >= strip.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= strip.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  }
}

void randomLights(unsigned long time, int rate, int numUpdates) {
  strip.clear();
  unsigned long exit = millis() + time;
  for(int i = 0; i < strip.numPixels(); i++) {  // fill strip with mix of orange and purple randomly
    if(random(0, 2000) % 2 == 0) {
      strip.setPixelColor(i, 255, 0, 200); //purple
    }
    else {
      strip.setPixelColor(i, 200, 25, 0); //orange
    }
  }
  strip.show();
  delay(rate);

  while(millis() < exit) {
    for(int i = 0; i < numUpdates; i++) {
      strip.setPixelColor(random(0, strip.numPixels()), 255, 0, 200);
      strip.setPixelColor(random(0, strip.numPixels()), 200, 25, 0);
    }
    strip.show();
    delay(rate);
  }
}

void multiChase() {  // NOT WORKING!
  int startColor = 0;
  int loops = 15;
  
  while(loops > 0) {
    for(int x=0; x<3; x++) {  //length of 3 pixels
      for(int i = 0; i <= LED_COUNT; i = i + 6) {
        strip.setPixelColor(i + x + startColor, 255, 0, 200);  //set pixels to purple
      }
      for(int i = 3; i <= LED_COUNT; i = i + 6) {
        strip.setPixelColor(i + x + startColor, 200, 25, 0); //set pixels to orange
      }
    }
    strip.show();
    startColor++;
    loops--;
  }
}