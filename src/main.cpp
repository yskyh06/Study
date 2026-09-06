#include <Arduino.h>

//버튼 상태 변수
const int BUTTON_PIN = 0;

int lastButtonState = HIGH;
int currentButtonState = HIGH;

//버튼이 짧은 시간 안에 연속적으로 인식되는 것을 방지
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

//길게 누른 것인지, 짧게 누른 것인지 판별하는 시간을 800ms로 잡음
unsigned long pressStartTime = 0;
const unsigned long longPressTime = 800;

//밝기 조절
int brightness = 0;
int direction = 1;

//이전 시간 기록.
unsigned long previousTime = 0;

//변화 사이사이의 딜레이
const unsigned long interval = 20;

//연속 동작 스위치
bool swtchBrightness = false;

//컬러 인덱스
int colorIndex = 0;

void ChangeColor(){
    
    if (colorIndex == 0)
        neopixelWrite(RGB_BUILTIN, brightness, 0, 0);
    else if (colorIndex == 1)
        neopixelWrite(RGB_BUILTIN, 0, brightness, 0);
    else if (colorIndex == 2)
        neopixelWrite(RGB_BUILTIN, 0, 0, brightness);
    else
        neopixelWrite(RGB_BUILTIN, 0, 0, 0);
}

void setBrightness(){
    if(!swtchBrightness) return;

    unsigned long currentTime = millis();

    if(currentTime - previousTime < interval) return;

    previousTime = currentTime;

    brightness += direction * 5;

    if(brightness >= 255){
        brightness = 255;
        direction = -1;
    }

    else if(brightness <= 0){
        brightness = 0;
        direction = 1;
    }
    
    ChangeColor();
}



void setup(){
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop(){

    setBrightness();

    int reading = digitalRead(BUTTON_PIN);

    if(reading != lastButtonState){
        lastDebounceTime = millis();
    }

    if(millis() - lastDebounceTime > debounceDelay){
        if(reading != currentButtonState){
            currentButtonState = reading;


            if(currentButtonState == LOW){
                pressStartTime = millis();
            }

            else{
                unsigned long pressDuration = millis() - pressStartTime;

                if(pressDuration >= longPressTime){
                    if(swtchBrightness) swtchBrightness = false;
                    else if(!swtchBrightness) swtchBrightness = true;
                }

                else{
                    colorIndex++;
                    if (colorIndex > 3) colorIndex = 0;
                    ChangeColor();
                }
            }
        }
    }

    lastButtonState = reading;
    
}
    