#include <Arduino.h>
#include <cstring>
#include <cstdlib>

char buffer[64];
int bufferIndex = 0;

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
            buffer[bufferIndex] = '\0';
            
            //만약 명령어(buffer)가 brigthness 50이라면
            //strtok 함수는 buffer에서 " "가 첫번째로 나온 인덱스의 값을 "\0"으로 바꿈. 이후에 "b"인덱스를 가르키게 됨. 즉 그 문자가 들어있는 인덱스의 주소를 반환 그래서 포인터 변수로 받는거임
            //만약에 brightness 50이라는 명령어가 필요하다면 이 명령어를 복사하고 진행해야 함.
            char* command = strtok(buffer, " ");
            //왜 buffer가 아니라 NULL을 넣었냐고 하면, strtok는 내부적으로 본인이 어디까지 읽었는지 알고 있음. 그래서 첫번째 호출에서 "brightness "까지 처리했으므로 그 다음 인덱스인 50부터 시작함.
            //입력 변수가 여러개라면 첫번째만 (변수, " ")라고 하고, 그 이후로는 (NULL, " ")만 써줘도 계속 인식 할 수 있음.
            //토큰이 없다면 nullptr 반환
            char* argument = strtok(NULL, " ");
            //그래서 이 조건문을 써줘야 함. 입력 변수가 없다면 command 값이 없으므로 이 조건을 만족시키지 못함. 그래서 nullptr로 검사함.
            if (command != nullptr)
            {
                Serial.print("Command: ");
                Serial.println(command);
            }

            if (argument != nullptr)
            {
                //strcmp는 두 문자열이 같은지 판별, 만약에 같으면 0을 반환.
                //command가 포인터형이므로 한번에 비교하기에는 이 명령어가 편리함.
                if (strcmp(command, "brightness") == 0 && argument != nullptr)
                {
                    int value = atoi(argument);

                    Serial.print("Brightness value: ");
                    Serial.println(value);
                }
            }

            bufferIndex = 0;
        }
        else
        {
            //왜 크기가 64인데 bufferIndex는 63까지만 가능? : 마지막에는 널포인터 넣어야 해서
            if (bufferIndex < sizeof(buffer) - 1)
            {
                buffer[bufferIndex++] = c;
            }
        }
    }
}