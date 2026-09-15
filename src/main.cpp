#include <Arduino.h>

//데이터가 바이트 단위로 들어오는 형식을 enum으로 지정
enum ParseState{
    WAIT_HEADER,
    READ_COMMAND,
    READ_VALUE,
    READ_CHECKSUM
};

ParseState parseState = WAIT_HEADER;

uint8_t command = 0;
uint8_t value = 0;

//command의 값에 따라서 결정
void processPacket(){
    if(command == 0x01){
        neopixelWrite(RGB_BUILTIN, value, 0, 0);

        Serial.print("Brightness: ");
        Serial.println(value);
    }

    else if (command == 0x02){
        neopixelWrite(RGB_BUILTIN, 0, 0, 0);

        Serial.println("LED OFF");
    }

    else
    {
        Serial.println("Unknown command");
    }   
}

void setup(){
    Serial.begin(115200);
    Serial.println("UART Packet Parser Start");
}

void loop(){
    while(Serial.available() > 0){
        //파이썬에서 순서대로 보내준 데이터를 바이트 단위로 하나씩 꺼내서 씀
        uint8_t data = Serial.read();

        //그래서 별도의 구분 작업 없이 switch로 나눠서 실행
        switch(parseState){
            //1단계 헤더 파일을 기다림
            //헤다가 중요한 이유 : 계속 보드에는 쓰레기 값이 들어오는데, 그 중에서 우리가 보낸 값을 찾으려면 그 시작 점을 찾아야 하기 때문
            //시작 점 이후로 몇개의 데이터는 우리가 보낸 데이터이기 떄문임. (이를 동기화라고 함)
            case WAIT_HEADER:
                //데이터가 0xAA라면 그 다음 단계로 진행. 알아서 data에는 커맨드가 들어감
                if(data == 0xAA){
                    parseState = READ_COMMAND;
                }

                break;
            
                //2단계 명령어 바이트를 기다림
            case READ_COMMAND:
                command = data;
                parseState = READ_VALUE;
                break;

            //3단계
            case READ_VALUE:
                value = data;
                parseState = READ_CHECKSUM;
                break;

            //4단계 체크섬 생성 및 확인
            case READ_CHECKSUM:
            {   
                //체크섬은 정상 패킷인지 아닌지 확인하기 위해 쓰임
                uint8_t receivedChecksum = data;
                uint8_t calculatedChecksum = command + value;

                if (receivedChecksum == calculatedChecksum){
                    Serial.println("Valid packet");

                    processPacket();
                }

                else{
                    Serial.println("Checksum error");
                }

                parseState = WAIT_HEADER;

                break;
            }
        }
    }
}