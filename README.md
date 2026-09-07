## Day 4 - Interrupt & ISR

### What I Learned

- Polling 방식과 Interrupt 방식의 차이
- `attachInterrupt()` 사용법
- `FALLING` 인터럽트
- ISR(Interrupt Service Routine)
- `volatile`의 의미
- `IRAM_ATTR`의 역할
- ISR에서 해야 할 일 / 피해야 할 일
- 인터럽트 환경에서의 debounce 개념

---

### Polling vs Interrupt

이전까지는 `loop()`에서 버튼 상태를 계속 읽는 polling 방식을 사용했다.

```cpp
int reading = digitalRead(BUTTON_PIN);