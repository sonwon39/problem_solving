# 재귀 → 반복 변환 가이드

재귀 함수를 반복문(`for` / `while`)으로 바꾸는 것은 문제 유형에 따라 난이도가 크게 다르다.
이 문서는 분류, 핵심 통찰, 표준 패턴, 그리고 실제로 떠올리는 요령을 정리한다.

> LaTeX 수식이 포함됨. **GitHub** 또는 **VSCode 마크다운 프리뷰**(`Ctrl+Shift+V`) 에서 보면 렌더링.

## 세 가지 분류

| 난이도 | 형태 | 변환 방법 |
|---|---|---|
| 쉬움 | 꼬리 재귀 — $f(n) = f(n-1) \oplus (\text{something})$ | `while` 루프, 인자만 업데이트 |
| 중간 | 메모이제이션 가능한 DP — $f(i,j) = g(f(i-1,j), f(i,j-1))$ | 테이블 바텀업 채우기 |
| 어려움 | 분할정복 + 결과 결합 (FFT, merge sort, segment tree) | 표준 3중 for 골격 |

이 문서는 주로 **어려움** 범주를 다룬다.

## 핵심 통찰 — 바텀업으로 뒤집기

재귀는 **위에서 아래로 쪼개며 내려간다**. 반복은 **아래에서 위로 합치며 올라간다**.
같은 일을 정반대 방향으로 하는 것이다.

| 재귀 (top-down) | 반복 (bottom-up) |
|---|---|
| 크기 $N \to N/2 \to \cdots \to 1$ | 크기 $1 \to 2 \to \cdots \to N$ |
| "풀어줘" 를 요청 | "이미 풀린 것" 을 결합 |
| 콜 스택이 상태 기억 | 배열이 상태 |

메모이제이션 DP 의 재귀↔바텀업 관계와 **정확히 같은 구조**.

## 분할정복 표준 3중 for 골격

FFT, merge sort, segment tree build, NTT 모두 아래 뼈대에 들어간다:

```cpp
for (size = 1; size < N; size *= 2) {             // ① 현재 블록 크기
    for (offset = 0; offset < N; offset += 2*size) {  // ② 어느 블록 차례인가
        for (i = 0; i < size; i++) {              // ③ 블록 내 위치
            // a[offset + i] 와 a[offset + size + i] 를 결합
        }
    }
}
```

각 루프의 의미:

- **`size` (바깥)**: 재귀 트리의 "깊이" — 리프에서 몇 단계 올라왔나.
- **`offset` (중간)**: 그 깊이에서 몇 번째 블록을 처리 중인가.
- **`i` (안쪽)**: 블록 내에서 몇 번째 원소인가.

세 변수가 "어디서 무슨 일이 일어나는지" 를 **완전히** 지정한다.

## 예 1 — Merge sort (바텀업)

가장 단순한 형태. FFT 들어가기 전 연습용으로 최적.

```cpp
for (int size = 1; size < N; size *= 2) {
    for (int left = 0; left < N; left += 2*size) {
        int mid   = std::min(left + size,   N);
        int right = std::min(left + 2*size, N);
        merge(arr, left, mid, right);   // [left, mid) 와 [mid, right) 병합
    }
}
```

`i` 가 명시적으로 드러나지 않는 이유는 `merge()` 내부에 숨어 있기 때문.
FFT 는 결합 로직이 짧아서 `i` 루프가 명시된다.

## 예 2 — Iterative FFT

```cpp
for (int len = 2; len <= N; len <<= 1) {          // ① 블록 크기
    double ang = 2.0 * PI / len * (invert ? 1 : -1);
    cd wlen(std::cos(ang), std::sin(ang));
    for (int i = 0; i < N; i += len) {            // ② 블록 시작
        cd w(1, 0);
        for (int j = 0; j < len/2; j++) {         // ③ 블록 내 위치
            cd u = a[i + j];
            cd v = a[i + j + len/2] * w;
            a[i + j]         = u + v;
            a[i + j + len/2] = u - v;
            w *= wlen;
        }
    }
}
```

`size = len/2` 로 잡으면 위 일반 골격과 정확히 일치한다.
입력은 사전에 bit-reversal 순서로 섞여 있어야 함.

**왜 `wlen` 을 바깥에서 한 번만 계산하나?**
같은 `len` 레벨에서 $w_j = w_1^{\,j}$ 인 등비수열.
`std::exp()` 를 매 butterfly 마다 부르면 $O(N \log N)$ 번 호출되어 TLE 원인이 된다.
`w *= wlen` 누적이면 레벨당 `cos/sin` 호출 1번으로 줄어든다.

## 실제로 떠올리는 요령

### 1. 재귀 트리 한 번만 손으로 그리기

$N = 8$ 정도면 충분. $N = 16$ 까지 그릴 필요 없다.

### 2. "레벨별 결합 표" 작성

```
레벨 0 (size=1):  [a0][a1][a2][a3][a4][a5][a6][a7]   ← 리프 (bit-reversal 된 입력)
레벨 1 (size=2):  [a0±a1][a2±a3][a4±a5][a6±a7]
레벨 2 (size=4):  ... 8개 ...
레벨 3 (size=8):  ... 최종 8개 ...
```

### 3. 각 레벨에서 "어느 인덱스 ↔ 어느 인덱스가 결합되나" 관찰

레벨 $k$ 에서: 블록 크기 $= 2^k$. 블록 $[\text{offset},\ \text{offset} + 2^k)$ 안에서
$\text{offset} + i$ 와 $\text{offset} + 2^{k-1} + i$ 가 짝이다.

### 4. 3중 for 템플릿에 대입

관찰한 인덱스 식을 `offset + i`, `offset + size + i` 꼴로 맞추면 끝.

## 다른 카테고리의 재귀

- **순수 탐색 트리 (DFS/backtracking)**: 반복문으로 바꾸려면 **명시적 스택** 필요.
  D&C 처럼 깨끗한 골격은 없다. 대개 재귀로 두는 게 낫고, 스택 깊이 문제만 있으면 스택 시뮬레이션으로 대응.
- **게임 트리, minimax 등**: 본질이 탐색이라 반복 변환의 이득이 적음.
- **이항 계수 등 단순 D&C**: 닫힌 식이 있으면 반복조차 불필요 ($O(1)$).

## 연습 순서 추천

1. **Merge sort 바텀업** (30분) — 골격 체화.
2. **Segment tree iterative build + update** — 인덱스 계산 감각.
3. **Iterative FFT** — 위 두 개 있으면 자연스럽게 나온다.
4. **NTT** — FFT 와 골격 동일, 복소수 대신 모듈러 산술.

1, 2 를 한 번 짜보면 "size × offset × i" 3중 for 가 반사적으로 떠오른다.

## 관련 문서 / 문제

- [DFT / IDFT 항등식 유도](../math/dft.md) — FFT 의 수학적 배경.
- [BOJ 15576 큰 수 곱셈](../../boj/cpp/15576.cpp) — Iterative FFT 적용 사례.
