## Day 3 - Non-Blocking LED Fade & Button Control

### What I Learned

- `millis()`를 이용한 non-blocking LED fade
- 일정 시간 간격으로 LED 밝기 변경
- 버튼 입력과 LED fade를 동시에 처리하는 구조
- `bool` 상태 변수를 이용한 기능 ON/OFF
- 짧게 누르기 / 길게 누르기 기능 확장
- `loop()`에서 여러 기능을 반복적으로 처리하는 방식
- 함수 분리를 통한 코드 구조화

---

### LED Fade

LED 밝기를 자동으로 증가시켰다가 감소시키는 fade 효과를 구현했다.

```cpp
int brightness = 0;
int direction = 1;