#include <Arduino.h>

const int BUTTON_PIN = 0;

int colorIndex = 0;
int brightness = 10;

int lastButtonState = HIGH;
int currentButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

unsigned long pressStartTime = 0;
const unsigned long longPressTime = 800;

//동작 수행 함수
void setColor(int index){
    if (index == 0)
        neopixelWrite(RGB_BUILTIN, brightness, 0, 0);
    else if (index == 1)
        neopixelWrite(RGB_BUILTIN, 0, brightness, 0);
    else if (index == 2)
        neopixelWrite(RGB_BUILTIN, 0, 0, brightness);
    else
        neopixelWrite(RGB_BUILTIN, 0, 0, 0);
}

void changeBrightness(){
    if (brightness == 10)
        brightness = 50;
    else if (brightness == 50)
        brightness = 120;
    else if (brightness == 120)
        brightness = 255;
    else
        brightness = 10;

    setColor(colorIndex);

    Serial.print("Brightness: ");
    Serial.println(brightness);
}

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    setColor(colorIndex);
}

void loop()
{
    int reading = digitalRead(BUTTON_PIN);

    //버튼 상태가 바뀌면 시간을 기록함.
    if(reading != lastButtonState){
        lastDebounceTime = millis();
    }

    // 버튼 입력 상태가 마지막으로 변한 후 50ms 이상 안정적으로 유지되면 실제 입력으로 인정
    if(millis() - lastDebounceTime > debounceDelay){
        if(reading != currentButtonState){
            currentButtonState = reading;

            //버튼을 누르고 있는 순간
            if(currentButtonState == LOW){
                pressStartTime = millis();
            }

            //버튼을 땐 순간
            else{
                unsigned long pressDuration = millis() - pressStartTime;

                if(pressDuration >= longPressTime) changeBrightness();
                else{
                    colorIndex++;

                    if (colorIndex > 3)
                        colorIndex = 0;

                    setColor(colorIndex);

                    Serial.print("Color Index: ");
                    Serial.println(colorIndex);
                }
            }
        }
    }

    lastButtonState = reading;
}