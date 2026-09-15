import serial
import time

#연결 포트 설정
PORT = "COM4"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout = 1)

time.sleep(2)

#ESP32에게 보낼 헤더, 명령어, 값, 체크섬을 작성
HEADER = 0xAA
COMMAND = 0x02
VALUE = 0
CHECKSUM = (COMMAND + VALUE) & 0xFF

#패킷이라는 바이트 단위의 배열을 보냄.
packet = bytes([
    HEADER,
    COMMAND,
    VALUE,
    CHECKSUM
])

print("TX:", packet.hex(" "))

#하지만 ESP32에선 한번에 들어가는게 아니라 헤더 -> 명령어 -> 값 이런식으로 바이트 단위로 하여 차례대로 들어옴
ser.write(packet)

time.sleep(0.2)


while ser.in_waiting > 0:
    line = ser.readline().decode(errors="ignore").strip()

    if line:
        print("RX", line)

ser.close()