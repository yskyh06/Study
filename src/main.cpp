#include <Arduino.h>

String command = "";

void setup()
{
    Serial.begin(115200);
    Serial.println("Enter command:");
}

void loop()
{
    while (Serial.available() > 0)
    {
        char c = Serial.read();

        if (c == '\n')
        {
            command.trim();

            Serial.print("Received: ");
            Serial.println(command);

            if (command == "red")
                neopixelWrite(RGB_BUILTIN, 255, 0, 0);
            else if (command == "green")
                neopixelWrite(RGB_BUILTIN, 0, 255, 0);
            else if (command == "blue")
                neopixelWrite(RGB_BUILTIN, 0, 0, 255);
            else if (command == "off")
                neopixelWrite(RGB_BUILTIN, 0, 0, 0);

            command = "";
        }
        else
        {
            command += c;
        }
    }
}