#include <Arduino.h>
#include <Wire.h>

const uint8_t DEVICE_ADDRESS = 0x40;

// 1바이트 레지스터 쓰기
// uint8_t unsigned인 8비트(1바이트) 자료형
void writeRegister(uint8_t deviceAddress,
                   uint8_t regAddress,
                   uint8_t value)
{
    //디바이스 주소로 전송을 시작
    Wire.beginTransmission(deviceAddress);

    Wire.write(regAddress);   // Register 주소
    Wire.write(value);        // Register에 쓸 값

    //전송 종료 후 error에 리턴값 저장.
    uint8_t error = Wire.endTransmission();

    if (error == 0)
    {
        Serial.println("Write success");
    }
    else
    {
        Serial.print("Write error: ");
        Serial.println(error);
    }
}


// 1바이트 레지스터 읽기
uint8_t readRegister(uint8_t deviceAddress,
                     uint8_t regAddress)
{
    // 디바이스 주소와 통신 시작 후에 읽고 싶은 Register 주소 지정
    Wire.beginTransmission(deviceAddress);
    Wire.write(regAddress);

    // STOP 없이 이어서 Read 수행. 쓰기와 달리 한번에 끝나지 않고 어느 레지스터를 읽을 지 write 후 read하기 때문에 작성
    uint8_t error = Wire.endTransmission(false);

    if (error != 0)
    {
        Serial.print("Register select error: ");
        Serial.println(error);

        return 0;
    }

    // 1바이트 요청. received에는 실제로 몇 바이트를 받아왔는지 작성이 되는 것임. 우리가 1 바이트를 보냈으니 정상적으로 작동하는거면 recived = 1이 되어 있어야 하는 것임.
    uint8_t received =
        Wire.requestFrom(deviceAddress, (uint8_t)1);

    if (received == 1 && Wire.available())
    {
        //1바이트로 받은 값이 실제로 어떤 값인지 알고 싶으면 read 작성
        return Wire.read();
    }

    Serial.println("Read error");

    return 0;
}


// 연속된 High / Low Register를 읽어
// 하나의 16-bit 값으로 조립
int16_t readRegister16(uint8_t deviceAddress,
                       uint8_t highRegister)
{
    uint8_t high =
        readRegister(deviceAddress, highRegister);

    uint8_t low =
        readRegister(deviceAddress, highRegister + 1);

    int16_t value =
        (int16_t)(((uint16_t)high << 8) | low);

    return value;
}


void setup()
{
    Serial.begin(115200);

    Wire.begin();

    delay(1000);

    Serial.println("I2C Register Example");

    // 예시:
    // 0x01 Register에 0x05 저장
    writeRegister(
        DEVICE_ADDRESS,
        0x01,
        0x05
    );

    // 예시:
    // 0x00 Register에서 1 byte 읽기
    uint8_t deviceID =
        readRegister(
            DEVICE_ADDRESS,
            0x00
        );

    Serial.print("Device ID: 0x");
    Serial.println(deviceID, HEX);

    // 예시:
    // 0x10 = High byte
    // 0x11 = Low byte
    int16_t sensorValue =
        readRegister16(
            DEVICE_ADDRESS,
            0x10
        );

    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);
}


void loop()
{
}