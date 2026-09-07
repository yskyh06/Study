#include <Arduino.h>

const int BUTTON_PIN = 0;

volatile bool buttonPressed = false;
volatile unsigned long lastInterruptTime = 0;

const unsigned long debounceTime = 200;

void IRAM_ATTR handleButton()
{
    unsigned long currentTime = millis();

    if (currentTime - lastInterruptTime > debounceTime)
    {
        buttonPressed = true;
        lastInterruptTime = currentTime;
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    attachInterrupt(
        digitalPinToInterrupt(BUTTON_PIN),
        handleButton,
        FALLING
    );
}

void loop()
{
    if (buttonPressed)
    {
        buttonPressed = false;

        Serial.println("Button interrupt!");
    }
}