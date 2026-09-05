#include <Arduino.h>

unsigned long previousTime = 0;
int colorIndex = 0;

void setup()
{
}

void loop()
{
    unsigned long currentTime = millis();

    if(currentTime - previousTime >= 1000){
        previousTime = currentTime;

        if (colorIndex == 0)
            neopixelWrite(RGB_BUILTIN, 255, 0, 0);
        else if (colorIndex == 1)
            neopixelWrite(RGB_BUILTIN, 0, 255, 0);
        else if (colorIndex == 2)
            neopixelWrite(RGB_BUILTIN, 0, 0, 255);
        else
            neopixelWrite(RGB_BUILTIN, 0, 0, 0);

        colorIndex++;

        if (colorIndex > 3)
            colorIndex = 0;
    }
}