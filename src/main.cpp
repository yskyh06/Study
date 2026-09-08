#include <Arduino.h>

const int BUTTON_PIN = 0;

struct Color
{
    int r;
    int g;
    int b;
};

Color colors[] =
{
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {0, 0, 0}
};

int brightnessLevels[] =
{
    10,
    50,
    120,
    255
};

int colorIndex = 0;
int brightnessIndex = 0;


// LED 출력
void applyLED()
{
    int brightness = brightnessLevels[brightnessIndex];
    Color currentColor = colors[colorIndex];

    int r = currentColor.r * brightness / 255;
    int g = currentColor.g * brightness / 255;
    int b = currentColor.b * brightness / 255;

    neopixelWrite(RGB_BUILTIN, r, g, b);
}


// 짧게 누름
void shortHandleButton()
{
    colorIndex++;

    if (colorIndex >= 4)
        colorIndex = 0;

    applyLED();
}


// 길게 누름
void longHandleButton()
{
    brightnessIndex++;

    if (brightnessIndex >= 4)
        brightnessIndex = 0;

    applyLED();
}


int lastButtonState = HIGH;
int currentButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

unsigned long pressStartTime = 0;
const unsigned long pressTime = 800;


void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    applyLED();
}


void loop()
{
    int reading = digitalRead(BUTTON_PIN);

    // raw 입력이 바뀌면 debounce 시간 초기화
    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    // 50ms 이상 안정적으로 유지된 입력만 인정
    if (millis() - lastDebounceTime > debounceDelay)
    {
        if (reading != currentButtonState)
        {
            currentButtonState = reading;

            // 버튼 누름
            if (currentButtonState == LOW)
            {
                pressStartTime = millis();
            }

            // 버튼 뗌
            else
            {
                unsigned long pressDuration =
                    millis() - pressStartTime;

                if (pressDuration < pressTime)
                {
                    shortHandleButton();
                }
                else
                {
                    longHandleButton();
                }
            }
        }
    }

    lastButtonState = reading;
}