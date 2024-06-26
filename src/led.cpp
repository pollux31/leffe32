//Libraries
#include <FastLED.h>//https://github.com/FastLED/FastLED
#include "led.h"

//Constants
#define NUM_LEDS 60
#define BRIGHTNESS 50
#define LED_TYPE WS2812B
#define COLOR_ORDER BRG

//Parameters
const int stripPin 	= 12;

//Variables
volatile int ledLevel = 0;
int oldLedLevel = 0;
//bool gReverseDirection = false;

//Objects
CRGB leds[NUM_LEDS];

// handle to tasks
TaskHandle_t hTaskLed;

// define tasks 
void TaskLed(void *pvParameters);

void SetupLed() {
 	//Init led strips
 	FastLED.addLeds<LED_TYPE, stripPin, COLOR_ORDER>(leds, NUM_LEDS);
 	FastLED.setBrightness(BRIGHTNESS);

    // Create the default task
    xTaskCreatePinnedToCore(
        TaskLed,
        "Analog",
        4096,       //stack size
        NULL,       // Task parameter
        3,          // Task priority from 0 (lowest) to 3
        &hTaskLed, // Created task handle return value (TaskHandle_t xHandle or NULL)
        1           // Display need to run in Core 1 !!!
    );


}

void SetLedLevel(int level) {
    ledLevel = level;
}


/*--------------------------------------------------*/
/*                       Tasks                      */
/*--------------------------------------------------*/

//---------------------------------------------------------------
void TaskLed(void *pvParameters)
{
    CRGB color = CRGB::Red;

    while (1)
    {
        // check if value changed
        if (ledLevel != oldLedLevel) {
            // set the new value
            oldLedLevel = ledLevel;
            //Serial.printf(".");

            // Clear the strip
            memset(leds, 0, NUM_LEDS * sizeof(CRGB));
            for (int i = 0; i < ledLevel * NUM_LEDS / 2048; i++) {
                leds[i] = CRGB::Red;
            }

            FastLED.show(); 
        }




    /*
    //color.setRGB(random(255), random(255), random(255));
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
        leds[i + 3] = color;
        FastLED.show();

        // Wait 10ms
        vTaskDelay(10 / portTICK_PERIOD_MS);

        leds[i] = CRGB::Black;
        FastLED.show();

        // Wait 10ms
        vTaskDelay(10 / portTICK_PERIOD_MS);
 	}
    */
    } // End infinit loop
}

