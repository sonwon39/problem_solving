---
name: 메모리 동기화 구조 (symlink 기반)
description: BOJ 학습 맥락을 여러 PC에서 공유하기 위한 메모리 저장소 구조와 symlink 세팅 방법
type: project
---

이 repo 의 `.claude/memory/` 가 **실제 메모리 저장소**이고, Claude Code 가 읽는 `~/.claude/projects/<encoded-path>/memory` 는 symlink로 여기를 가리킨다.

**Why:** 사용자가 여러 PC에서 같은 학습 맥락(메모리)을 이어가고 싶어함. repo 에 메모리를 commit/push 하면 git 으로 자연스럽게 동기화된다.

**How to apply:**
- 메모리 파일은 항상 `c:\Users\son97\baekjoon\.claude\memory\` 에 쓴다 (symlink 를 통해 Claude Code 가 읽음)
- 메모리 변경 후엔 `commit-push` 스킬로 push 하면 다른 PC에서 pull 가능
- **다른 PC 세팅 시**: clone 후 개발자 모드 ON 상태에서 아래 형태로 symlink 생성 (PC마다 username/clone 경로에 맞춰 `<encoded-path>` 를 바꿈 — `c:\...` 의 `:` 제거 + `\` → `-` 치환, 예: `C:\Users\alice\code\baekjoon` → `c--Users-alice-code-baekjoon`):
  ```bash
  MSYS=winsymlinks:nativestrict cmd.exe /c "mklink /D \"%USERPROFILE%\\.claude\\projects\\<encoded-path>\\memory\" \"<clone경로>\\.claude\\memory\""
  ```
- 메인 PC(son97) 에서는 이미 symlink 설정 완료됨 (2026-04-13)
