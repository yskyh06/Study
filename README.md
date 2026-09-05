## Day 2 - RGB LED & Button Control

### What I Learned

- ESP32-S3 onboard RGB LED 제어
- `neopixelWrite()`를 이용한 색상 변경
- RGB 값 조절을 통한 밝기 제어
- `digitalRead()`를 이용한 버튼 입력
- `INPUT_PULLUP` 동작 방식
- BOOT 버튼(GPIO 0) 입력 처리
- Software debouncing
- 버튼 짧게 누르기 / 길게 누르기 구분
- `millis()`를 이용한 시간 측정
- LED 제어 코드를 함수로 분리

---

### RGB LED Control

ESP32-S3-DevKitC-1의 onboard RGB LED는 `neopixelWrite()`를 이용해 제어했다.

```cpp
neopixelWrite(RGB_BUILTIN, red, green, blue);