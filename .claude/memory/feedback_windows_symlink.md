---
name: Windows 에서 symlink 생성은 mklink 로
description: Windows 에서 디렉토리 symlink 만들 때 PowerShell New-Item 말고 cmd mklink 를 써야 함
type: feedback
---

Windows 에서 디렉토리 symlink 를 만들 때는 **`cmd.exe /c mklink /D`** 를 쓴다. PowerShell `New-Item -ItemType SymbolicLink` 는 쓰지 말 것.

**Why:** 2026-04-13 메모리 symlink 세팅 중 확인: 개발자 모드가 **이미 켜진 상태**에서도 PowerShell 쪽은 `NewItemSymbolicLinkElevationRequired` 오류를 냄 (PowerShell 의 알려진 버그 — dev mode 로 부여된 `SeCreateSymbolicLinkPrivilege` 를 제대로 인식 못함). 같은 환경에서 `mklink` 는 관리자 권한 없이 성공.

**How to apply:**
- Git Bash 에서 실행할 때:
  ```bash
  MSYS=winsymlinks:nativestrict cmd.exe /c "mklink /D \"<link경로>\" \"<target경로>\""
  ```
  `MSYS=winsymlinks:nativestrict` 는 Git Bash 가 경로 변환을 방해하지 않도록 막는 역할
- 경로의 백슬래시는 `\\` 로 이스케이프, 각 경로는 `\"...\"` 로 감쌀 것
- 실패하면 먼저 Windows 개발자 모드가 켜져 있는지 확인 (설정 → 시스템 → 개발자용)
