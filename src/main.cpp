#include <Arduino.h>
#include <cstring>
#include <cstdlib>

const int BUFFER_SIZE = 64;

char buffer[BUFFER_SIZE];
int bufferIndex = 0;

int brightness = 50;

enum SystemState
{
    IDLE,
    LED_ON,
    LED_OFF,
    ERROR_STATE
};

SystemState state = IDLE;

void applyLED()
{
    if (state == LED_ON)
    {
        neopixelWrite(RGB_BUILTIN, brightness, 0, 0);
    }
    else
    {
        neopixelWrite(RGB_BUILTIN, 0, 0, 0);
    }
}

void printStatus()
{
    Serial.print("State: ");

    switch (state)
    {
        case IDLE:
            Serial.println("IDLE");
            break;

        case LED_ON:
            Serial.println("LED_ON");
            break;

        case LED_OFF:
            Serial.println("LED_OFF");
            break;

        case ERROR_STATE:
            Serial.println("ERROR");
            break;
    }

    Serial.print("Brightness: ");
    Serial.println(brightness);
}

void processCommand()
{
    char* command = strtok(buffer, " ");
    char* argument = strtok(NULL, " ");

    if (command == nullptr)
        return;

    if (strcmp(command, "on") == 0)
    {
        state = LED_ON;
        applyLED();

        Serial.println("LED ON");
    }

    else if (strcmp(command, "off") == 0)
    {
        state = LED_OFF;
        applyLED();

        Serial.println("LED OFF");
    }

    else if (strcmp(command, "status") == 0)
    {
        printStatus();
    }

    else if (strcmp(command, "brightness") == 0)
    {
        if (argument == nullptr)
        {
            Serial.println("ERROR: brightness value required");
            state = ERROR_STATE;
            return;
        }

        char* endPtr;
        
        //strtol은 수를 안전하게 받을 때 사용함
        //만약 입력값이 brightness 10이라고 하면 value에는 10이 저장되고, endptr에는 null문자(문자열의 마지막)이 저장됨
        //하지만 123dfd라는 이상한 값이 들어오면 endptr에는 a의 주소가 찍히게 됨
        long value = strtol(argument, &endPtr, 10);


        //그래서 endptr이 null인지 아닌지 판별하여 value값이 수인지 아닌지 판별함.
        if (*endPtr != '\0')
        {
            Serial.println("ERROR: invalid number");
            state = ERROR_STATE;
            return;
        }

        if (value < 0 || value > 255)
        {
            Serial.println("ERROR: brightness must be 0~255");
            state = ERROR_STATE;
            return;
        }

        brightness = value;

        if (state == LED_ON)
        {
            applyLED();
        }

        Serial.print("Brightness changed: ");
        Serial.println(brightness);
    }

    else
    {
        Serial.println("ERROR: unknown command");
        state = ERROR_STATE;
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Commands:");
    Serial.println("on");
    Serial.println("off");
    Serial.println("brightness <0~255>");
    Serial.println("status");
}

void loop()
{
    while (Serial.available() > 0)
    {
        char c = Serial.read();

        if (c == '\n')
        {
            buffer[bufferIndex] = '\0';

            processCommand();

            bufferIndex = 0;
        }
        else if (c != '\r')
        {
            if (bufferIndex < BUFFER_SIZE - 1)
            {
                buffer[bufferIndex++] = c;
            }
            else
            {
                Serial.println("ERROR: command too long");
                bufferIndex = 0;
                state = ERROR_STATE;
            }
        }
    }
}