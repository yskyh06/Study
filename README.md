## Day 5 - LED State Management with Arrays & Structs

### What I Learned

- RGB 색상을 `struct`로 관리
- 밝기 단계를 배열로 관리
- `colorIndex`, `brightnessIndex`를 이용한 상태 전환
- 짧게 누르기 / 길게 누르기 동작 분리
- LED 출력 로직을 함수로 분리
- Polling 방식과 Interrupt 방식의 사용 기준
- 불필요한 interrupt 사용을 피하는 이유

---

### Managing Colors with a Struct

기존에는 RGB 색상을 `if / else if` 안에서 직접 지정했지만,
이번에는 색상 데이터를 구조체로 묶어서 관리했다.

### Poling vs Interrput
Poling이 유리한 경우
1. 사용자가 버튼을 누르는 경우
2. 동작이 심하면 몇 초정도 느려도 되는 경우
3. 이 동작의 지연이 다음 함수에 영향을 안주는 경우

Interrupt가 유리한 경우
1. 버튼 입력을 놓치면 안되는 경우
2. 아주 빠른 센서 입력값을 잡아야 하는 경우
3. 저전력 모드에서 이벤트 발생시에 CPU를 깨워야 하는 경우


```cpp
struct Color
{
    int r;
    int g;
    int b;
};



