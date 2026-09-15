#include <Arduino.h>

hw_timer_t* timer = nullptr;

volatile bool timerTriggered = false;

void IRAM_ATTR onTimer()
{
    timerTriggered = true;
}

void setup()
{
    Serial.begin(115200);

    timer = timerBegin(0, 80, true);

    timerAttachInterrupt(timer, &onTimer, true);

    timerAlarmWrite(timer, 1000000, true);

    timerAlarmEnable(timer);
}

void loop()
{
    if (timerTriggered)
    {
        timerTriggered = false;

        Serial.println("Timer interrupt!");
    }
}