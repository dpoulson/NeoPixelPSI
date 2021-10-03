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
#define STICKINESS 0
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

    NeoPixelPSI(int psi_pin) :
      leds(NUM_LEDS, psi_pin, NEO_GRB + NEO_KHZ800)
    {
      leds.begin();
      leds.setBrightness(brightness);
    }

    virtual void animate() {
      unsigned long currentMillis = millis();
      if (currentMillis >= fSwipeSpeed)
      {
        swipe_main(swipe_position);
        if (swipe_direction == 0) {
          if (swipe_position > 3) {
             swipe_direction = 1;
             fSwipeSpeed = currentMillis + random(sdelay, sdelay*4);
             //swipe_position--;
          } else {
             fSwipeSpeed = currentMillis + sspeed;
             swipe_position++;
          }
        } else {
          if (swipe_position <= 0) {
             swipe_direction = 0;
             fSwipeSpeed = currentMillis + random(sdelay, sdelay*4);
             //swipe_position++;
          } else {
             fSwipeSpeed = currentMillis + sspeed;
             swipe_position--;
          }
        }
      }
    }

    void set_brightness(int bright) {
      brightness = bright;
      leds.setBrightness(brightness);
      leds.show();
    }

    void set_color(int c, int r, int g, int b) {
      if (c == 1) 
        color_one = leds.Color(r,g,b);
      else
        color_two = leds.Color(r,g,b);
    }

    void set_speed(int s)  {
      sspeed = s;
    }

    void set_delay(int d) {
      sdelay = d;
    }

    void setSequence(Sequence seq = kNormal, uint8_t speedScale = 0, uint8_t numSeconds = 0)
    {
        do_pulse(10, 50, 255, 0, 0);
    }

  private:
    int fPSI = 0;
    int swipe_direction = 0;
    int swipe_position = 0;
    int sspeed = SWIPE_SPEED;
    int sdelay = SWIPE_DELAY;
    int brightness = BRIGHTNESS;
    uint32_t color_one = leds.Color(255,0,0);
    uint32_t color_two = leds.Color(0,0, 255);
    unsigned long fSwipeSpeed;
    unsigned long fSwipeMillis; 
    
    int LEDmap[5][5]  = {
       {99, 0, 1, 2, 99 },
       {3, 4, 5, 6, 7},
       {8, 9, 10, 11, 12},
       {13, 14, 15, 16, 17},
       {99, 18, 19, 20, 99},
    };
    

    void swipe_main(uint8_t pos)
    {
      uint32_t color;
      for(int row = 0; row <= 4 ; row++) {
        if(swipe_direction == 0)
            color = color_one;
        else
            color = color_two;
        int led = LEDmap[pos][row];
        if(led != 99)
          leds.setPixelColor(led, color);
      }
      leds.show();
    }

    void do_random(uint8_t cycles, uint8_t pulse_speed) 
    {
        int pixel, r, g, b;
        uint32_t color;
        for(int i=0;i<=cycles;i++) 
        {
            for (int j = 0; j< 5; j++) 
            {
                for (int k = 4; k >= 0; k--) 
                {
                    pixel = random(0,cycles);
                    if (pixel < cycles-i) 
                    {
                        // Pixel on
                        r = random(0,255);
                        g = random(0,255);
                        b = random(0,255);
                        color = leds.Color(r, g, b);
                    } else {
                        color = leds.Color(0,0,0);
                    }
                    int led = LEDmap[j][k];
                    leds.setPixelColor(LEDmap[j][k], color);
                }
            }
            leds.show();
            delay(pulse_speed);
        }
        delay(2000);
    }

    void do_pulse(uint8_t pulses, uint8_t pulse_speed, int r, int g, int b) 
    {
        Serial.println("Pulsing");
        uint32_t color;
        for(int i=0;i<=pulses;i++) 
        {
          Serial.print("Pulse: ");
          Serial.println(i);
          for(int x=0; x<20; x++) // Ten steps per pulse
          {
            if(x > 10) {
              Serial.print("r ");
              Serial.println(((r/10)*x));
              color = leds.Color((r/10)*x, (g/10)*x, (b/10)*x);
            } else {
              Serial.print("r ");
              Serial.println(r-((r/10)*x));
              color = leds.Color(r-((r/10)*x), g-((g/10)*x), b-((b/10)*x));
            }
            leds.fill(color);
            leds.show();
            delay(pulse_speed);
          }
        }
        leds.show();
    }
};

NeoPixelPSI fpsi(3);
NeoPixelPSI rpsi(4);

unsigned long last_effect = 0;

void setup() {
     Serial.begin(115200);
     rpsi.set_color(1, 0, 255, 0);
     rpsi.set_color(2, 128, 128, 128);
     rpsi.set_speed(50);
     rpsi.set_delay(750);
     rpsi.set_brightness(20);
}

void loop() {
  fpsi.animate();
  rpsi.animate();
  if(last_effect + 10000 < millis()) {
    Serial.print("Triggering effect: ");
    Serial.println(last_effect);
    fpsi.setSequence(1);
    last_effect = millis();
  }
}
