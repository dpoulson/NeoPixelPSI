//#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#define USE_DEBUG
///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 21

#define SWIPE_SPEED 75 
#define SWIPE_DELAY 500 
#define BRIGHTNESS 28

#ifdef USE_DEBUG
 #define PSI_DEBUG
#endif

class NeoPixelPSI 
{
  public: 
    Adafruit_NeoPixel leds;
    
    enum EffectValue
    {
        kNormalVal = 0
    };

    enum Sequence
    {
        kNormal = 0,
        kSolid = 1,
        kHeart = 2,
        kMalf = 3,
    };

    enum PSIID
    {
        /** Front PSI ID */
        kFrontPSI = 1,
        /** Rear PSI ID */
        kRearPSI = 2,
    };


    NeoPixelPSI(const int psi, int psi_pin) :
      leds(NUM_LEDS, psi_pin, NEO_GRB + NEO_KHZ800),
      fPSI(psi)
    {
      Serial.println("Constructing");
      leds.begin();
      leds.setBrightness(BRIGHTNESS);
      //leds.fill(leds.Color(255,0,0),0, NUM_LEDS);
      //leds.show();
    }

    virtual void animate() {
      unsigned long currentMillis = millis();
      if (currentMillis >= fSwipeSpeed)
      {
        swipe_main(swipe_position);
        if (swipe_direction == 0) {
          if (swipe_position > 3) {
             swipe_direction = 1;
             fSwipeSpeed = currentMillis + random(500, 2000);
             //swipe_position--;
          } else {
             fSwipeSpeed = currentMillis + SWIPE_SPEED;
             swipe_position++;
          }
        } else {
          if (swipe_position <= 0) {
             swipe_direction = 0;
             fSwipeSpeed = currentMillis + random(500, 2000);
             //swipe_position++;
          } else {
             fSwipeSpeed = currentMillis + SWIPE_SPEED;
             swipe_position--;
          }
        }
      }
    }


  private:
    int fPSI = 0;
    int swipe_direction = 0;
    int swipe_position = 0;
    unsigned long fSwipeSpeed;
    unsigned long fSwipeMillis; 
    byte LEDmap[5][5]  = {
       {99, 0, 1, 2, 99 },
       {3, 4, 5, 6, 7},
       {8, 9, 10, 11, 12},
       {13, 14, 15, 16, 17},
       {99, 18, 19, 20, 99},
    };
    

    void swipe_main(uint8_t pos)
    {
      uint32_t colour;
      for(int row = 0; row <= 4 ; row++) {
        if(swipe_direction == 0)
          if (fPSI == 1) 
            colour = leds.Color(255,0,0);
          else
            colour = leds.Color(0,255,0);
        else
          if (fPSI == 1)
            colour = leds.Color(0,0,255);
          else
            colour = leds.Color(255,255,0);
        int led = LEDmap[pos][row];
        if(led != 99)
          leds.setPixelColor(led, colour);
      }
      leds.show();
    }
};

NeoPixelPSI fpsi(1, 3);
NeoPixelPSI rpsi(2, 4);

void setup() {
     Serial.begin(115200);
}

void loop() {
  fpsi.animate();
  rpsi.animate();
}
