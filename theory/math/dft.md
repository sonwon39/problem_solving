# DFT / IDFT 항등식 유도

이산 푸리에 변환(DFT)과 역변환(IDFT)이 서로 역함수임을 보이는 유도.
FFT 기반 다항식·큰 수 곱셈 (예: [BOJ 15576](../../boj/cpp/15576.cpp)) 의 배경 지식.

> 이 문서는 LaTeX 수식을 포함한다. **GitHub** 또는 **VSCode 마크다운 프리뷰**(`Ctrl+Shift+V`) 에서 보면 렌더링된다.

## 정의

$$
X[k] \;=\; \sum_{m=0}^{N-1} x[m]\, e^{-i\,2\pi km/N}
\qquad
x[n] \;=\; \frac{1}{N} \sum_{k=0}^{N-1} X[k]\, e^{i\,2\pi kn/N}
$$

$\tfrac{1}{N}$ 계수는 관습에 따라 DFT 또는 IDFT 한 쪽에 붙인다. 여기서는 IDFT 쪽.

## 핵심 보조정리 — 단위근의 직교성

임의의 정수 $r$ 에 대해

$$
S(r) \;=\; \sum_{k=0}^{N-1} e^{i\,2\pi kr/N}
\;=\;
\begin{cases} N, & r \equiv 0 \pmod{N} \\ 0, & \text{그 외} \end{cases}
$$

**증명.**

- $r \equiv 0 \pmod{N}$ 이면 지수가 $0$ 이라 $1$ 이 $N$ 번 더해져 $N$.
- 아니면 $w = e^{i\,2\pi r/N} \ne 1$ 인 등비급수:

$$
\sum_{k=0}^{N-1} w^{k} \;=\; \frac{1 - w^{N}}{1 - w}.
$$

$w^{N} = e^{i\,2\pi r} = 1$ 이므로 분자 $= 0$. 따라서 합 $= 0$. $\blacksquare$

## DFT → IDFT 항등식

IDFT 에 DFT 정의를 대입.

$$
\begin{aligned}
x[n]
&= \frac{1}{N} \sum_{k=0}^{N-1} \!\Biggl[\, \sum_{m=0}^{N-1} x[m]\, e^{-i\,2\pi km/N} \Biggr] e^{i\,2\pi kn/N} \\[6pt]
&= \frac{1}{N} \sum_{m=0}^{N-1} x[m] \underbrace{\sum_{k=0}^{N-1} e^{i\,2\pi k(n-m)/N}}_{=\, N\,\delta_{n,m}} \\[6pt]
&= \frac{1}{N} \cdot N \cdot x[n] \;=\; x[n]. \qquad\square
\end{aligned}
$$

순서가 중요하다. **안쪽 합이 $k$, 바깥이 $m$** 이라야 직교성이 $\delta_{n,m}$ 을 뽑아준다.

## 자주 하는 실수

1. **합 순서 뒤집기.** $\sum_{m} e^{i\,2\pi k(n-m)/N}$ 로 쓰면 의미가 달라진다.
   고정된 $k$ 에 대한 $m$ 합은 공비 $e^{-i\,2\pi k/N}$ 의 등비급수라
   $k=0$ 에서만 $N$, 나머지 $0$ → $X[0]$ 하나만 남는 엉뚱한 결과가 나온다.

2. **$N$ 을 $1$ 로 착각.** 직교성이 주는 건 $1$ 이 아니라 $N\,\delta_{n,m}$.
   $\tfrac{1}{N}$ 계수와 약분되어 $x[n]$ 이 된다.

3. **"대부분 $0$ 이니 전체 $0$" 해석.** $m \ne n$ 인 항이 $0$ 일 뿐,
   $m = n$ 인 **한 항이 살아남아** $x[n]$ 을 뽑아낸다.
   디락 델타의 sifting 성질과 같은 구조.

## 직관

IDFT 를 "각 주파수 $k$ 에 대한 역기저의 합" 으로 보면,
$k$ 에 대한 합이 **위치 $n = m$ 에서만 $N$ 만큼 튀는 이산 델타** 를 만든다.
이 델타가 $\sum_m x[m]$ 중 $m = n$ 항을 골라내 원본을 복원한다.

## 응용으로 이어지는 관찰

- **다항식 곱셈.** $A(x)\cdot B(x)$ 의 계수는 점값 표현에서 성분별 곱.
  $\text{DFT}$ (특정 점에서의 평가) → 성분곱 → $\text{IDFT}$ 로 $O(N \log N)$ 곱셈 (FFT).
- **순환 합성곱.** $\sum_m x[m]\, y[(n-m)\bmod N]$ 은 DFT 도메인에서 단순 곱 $X[k]\,Y[k]$ 가 된다.
  위 유도의 $e^{i\,2\pi k(n-m)/N}$ 구조가 이걸 자연스럽게 설명.

## 관련 문제

- [BOJ 15576 — 큰 수 곱셈](../../boj/cpp/15576.cpp) — FFT 기반 $O(N \log N)$ 곱셈.
