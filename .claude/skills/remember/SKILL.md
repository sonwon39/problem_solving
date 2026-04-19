---
name: remember
description: 대화에서 나온 변경사항/피드백/사용자 정보/외부 참조를 `.claude/memory/` 에 저장하거나 업데이트합니다. 사용자가 "기억해", "메모리화해", "이거 저장해둬" 라고 하거나, 중요한 결정/피드백/환경 변경이 있은 뒤에 사용하세요.
---

# /remember — 메모리 저장 스킬

대화 중 나온 정보 중 **다음 세션에서도 필요한 것들** 을 `.claude/memory/` 에 파일 단위로 저장하고 `MEMORY.md` 인덱스를 갱신합니다.

## 저장 위치

- 메모리 파일: `.claude/memory/<type>_<topic>.md`
- 인덱스: `.claude/memory/MEMORY.md` (한 줄짜리 링크만)

repo 안에 있고, 이미 symlink 로 Claude Code 전역 메모리 경로에 연결돼 있음 (see [project_memory_sync.md](.claude/memory/project_memory_sync.md)). 그래서 파일 하나만 추가해도 git push 로 다른 PC에 동기화 됨.

## 분류 (4 가지 type)

| type | 언제 쓰나 | 파일명 예시 |
|------|----------|------------|
| `user` | 사용자 배경, 환경, 학습 스타일 | `user_profile.md` |
| `feedback` | "이렇게 하지 마", "이 방식이 맞아" 같은 행동 교정/확정 | `feedback_<topic>.md` |
| `project` | 이 repo 안 작업의 맥락/결정/일정 | `project_<topic>.md` |
| `reference` | 외부 시스템 위치, 환경 세팅 정보 | `reference_<topic>.md` |

판단 모호하면 사용자에게 물어봄.

## 실행 순서

1. **후보 수집** — 대화에서 다음을 찾는다:
   - 사용자가 명시적으로 "기억해" 라고 한 것
   - 환경/설정/경로 변경 (repo rename, 새 도구 설치, credential 변경 등)
   - 사용자가 교정해준 접근 방식 또는 "그게 맞아" 로 확정한 판단
   - 외부 시스템 위치 (dashboard URL, tracker 프로젝트 등)
   - 프로젝트 일정, 마감, 중단/변경 결정

2. **기존 메모리와 중복 체크** — `.claude/memory/MEMORY.md` 를 먼저 읽고, 비슷한 주제 파일이 있으면 **새로 만들지 말고 업데이트**. 목록:
   - Read `MEMORY.md` → 관련 엔트리 있나 확인
   - 있으면 해당 파일 Read 후 Edit
   - 없으면 새 파일 Write + MEMORY.md 에 한 줄 추가

3. **저장하면 안 되는 것 거르기**:
   - 코드에서 바로 읽을 수 있는 구조/패턴/파일 경로
   - git log 로 알 수 있는 변경 이력
   - 이 대화 안에서만 쓰는 임시 상태
   - 버그 수정 레시피 (코드에 남아있고 commit 메시지에 있음)
   - CLAUDE.md 에 이미 있는 내용
   - 사용자를 부정적으로 평가할 만한 것 ("이 개념 몰랐음" 등)

4. **파일 작성** — frontmatter 필수:
   ```markdown
   ---
   name: <짧은 이름>
   description: <한 줄 요약, 미래의 내가 관련성 판단하기 쉽게 구체적으로>
   type: user | feedback | project | reference
   ---

   <본문>
   ```

   `feedback` / `project` 는 본문에 `**Why:**` 와 `**How to apply:**` 줄 포함.

5. **MEMORY.md 업데이트** — 한 줄:
   ```
   - [표제](파일명.md) — 한 줄 훅
   ```
   총 200 줄 넘지 않게 간결하게.

6. **요약 출력** — 사용자에게 저장/업데이트한 항목 리스트 보여줌 (어떤 파일에, 어떤 내용을).

## 예시

**입력**: "지금 이 대화에서 중요한 거 기억해둬"

**후보**:
- GitHub repo `baekjoon` → `problem_solving` 으로 rename (2026-04-19)
- remote URL 에서 PAT 제거, credential helper = manager 로 변경

**저장**:
- 업데이트: `user_profile.md` (repo 이름 변경 반영)
- 신규: `reference_git_auth.md` (credential helper 세팅)
- MEMORY.md 에 `reference_git_auth.md` 한 줄 추가

**출력**:
```
저장 완료:
- user_profile.md 업데이트 — GitHub repo 이름 반영
- reference_git_auth.md 신규 — credential helper = manager, PAT URL 금지
- MEMORY.md 인덱스 1줄 추가
```

## 금지 사항

- 사용자 동의 없이 민감정보(토큰/비밀번호/이메일 외부 공개) 저장 금지
- "이 사용자는 X 를 모른다" 같은 부정적 평가 저장 금지
- 코드/경로 덤프 저장 금지 (파일 읽으면 되는 내용)
- 한 파일 안에 관련 없는 주제 섞기 금지
- MEMORY.md 에 본문을 바로 쓰기 금지 (인덱스 한 줄만)

## 응답 스타일

- 저장 전 후보를 먼저 **한 줄씩 나열** 해서 사용자 확인 가능하게
- 사용자가 "ㅇㅇ 저장해" 하면 그대로 실행
- 완료 후에는 파일명 + 한 줄 요약으로 간결하게
- 한국어로 답변
