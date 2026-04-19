---
name: C++ 빌드 환경 (VS2022)
description: 저장소에서 cpp 파일을 컴파일/실행하는 방법과 MSVC 링커 PDB 버그 회피책
type: reference
originSessionId: d4b6f3cd-b073-47c8-9794-bf12eea01719
---
이 저장소에서 C++ 풀이를 빌드/실행할 때 사용하는 도구와 환경 정보.

## 컴파일러

- **Visual Studio 2022 Community** (MSVC `cl`)
- 경로: `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat`
- `g++`, `clang++`, MinGW 등은 PATH 에 없음. cl 만 가능.

## 빌드 스크립트

`boj/cpp/build.bat` — 범용 빌드 헬퍼. 사용법:

```
cmd //c ".\\boj\\cpp\\build.bat <문제번호> [--run]"
```

예: `cmd //c ".\\boj\\cpp\\build.bat 1000 --run"` → `boj/cpp/1000.cpp` 컴파일 후 실행.

산출물(`.exe`, `.obj`)은 `boj/cpp/` 안에 생성되고 `.gitignore` 가 무시함.

다른 사이트(codeforces, atcoder)에서도 build.bat 이 필요하면 복사해서 해당 폴더에 넣으면 됨. `%~dp0` 기준 동작이라 위치 무관.

## MSVC mspdbcore.dll 링커 버그 — 반드시 알아둘 것

기본 `cl` 호출 시 `LINK : fatal error LNK1171: mspdbcore.dll을 로드할 수 없습니다 (error 1455)` 가 자주 발생함. 이 환경 특유의 버그.

**회피책**: `cl` 명령 끝에 `/link /DEBUG:NONE` 을 붙임. PDB 생성을 강제로 끄면 해당 dll 로딩이 시도되지 않음. `cpp/build.bat` 에 이미 적용돼 있음.

직접 `cl` 을 호출할 일이 있으면 항상 `/link /DEBUG:NONE` 을 붙일 것.
