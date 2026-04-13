---
name: commit-push
description: 현재 작업 중인 변경사항을 commit 하고 origin 으로 push 합니다. 사용자가 "커밋하고 푸시해", "commit push 해줘", "올려줘" 등으로 작업 마무리를 요청할 때 사용하세요.
---

# /commit-push — 커밋 & 푸시 스킬

작업이 끝난 변경사항을 안전하게 origin 으로 올립니다. 백준 풀이 파일(cpp/, python/), CLAUDE.md 수정, 스킬 추가 등 이 repo에서 반복적으로 쓰입니다.

## 실행 순서

1. **상태 확인** — 다음 명령을 병렬로 실행:
   - `git status` (untracked/modified 파악, `-uall` 금지)
   - `git diff` (unstaged)
   - `git diff --cached` (staged)
   - `git log -5 --oneline` (기존 커밋 메시지 스타일 파악)

2. **변경사항 분석** — 무엇이, 왜 바뀌었는지 정리:
   - 새 문제 풀이? (예: "Solve BOJ 1149 DP")
   - 기존 풀이 수정/리팩터? (예: "Refactor 2580 with backtracking")
   - 스킬/설정 변경? (예: "Add commit-push skill")
   - 문서 수정?

3. **민감정보 체크** — 커밋 전 확인:
   - `.env`, `credentials.json`, API 키, 토큰 포함 여부
   - 발견 시 **즉시 중단**하고 사용자에게 경고
   - `.claude/settings.json` 에 민감 정보가 들어갔는지도 확인

4. **커밋 메시지 작성**:
   - 1줄 제목 (50자 내외) + 필요 시 본문 1~2줄
   - **"왜"** 중심 (무엇을 바꿨는지는 diff 에 있음)
   - 기존 repo 스타일 따름 (한/영 혼용 OK, 백준 풀이는 보통 `Solve BOJ <번호> <제목>` 형태)
   - 예시:
     - `Solve BOJ 1149 — RGB거리` (풀이 추가)
     - `Fix BOJ 2580 backtracking order` (버그 수정)
     - `Add commit-push skill` (인프라)

5. **스테이징** — 관련 파일만 명시적으로:
   ```bash
   git add cpp/1149.cpp python/1149.py
   ```
   **`git add -A` / `git add .` 금지** (민감정보 섞임 방지)

6. **커밋** — HEREDOC 으로 메시지 전달:
   ```bash
   git commit -m "$(cat <<'EOF'
   <커밋 메시지>

   Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>
   EOF
   )"
   ```
   Windows Git Bash 에서 HEREDOC 이 temp file 오류를 낼 때는 `export TMPDIR=/tmp && mkdir -p /tmp` 를 앞에 붙임.

7. **푸시** — `git push` 실행 (현재 브랜치 → origin)

8. **결과 요약** — 한 줄로: 커밋 해시 + 브랜치 이동(`4e19887..7861193 main -> main`)

## 금지 사항

- `git commit --amend` (pre-commit hook 실패해도 새 커밋으로 고치기)
- `git push --force` (특히 main)
- `--no-verify`, `--no-gpg-sign` (hook/서명 우회)
- 빈 커밋 만들기 (변경사항 없으면 "변경사항 없음" 알리고 종료)
- `git add -A`, `git add .`, `git add *`
- `git config` 수정

## 엣지 케이스

- **변경사항 없음**: 커밋하지 말고 "변경사항 없습니다" 만 알리고 종료
- **untracked 파일만 존재**: 추가할지 사용자에게 확인
- **여러 무관한 변경이 섞임**: 한 커밋에 묶지 말고 나눠서 커밋할지 물어봄
- **pre-commit hook 실패**: 오류 원인 파악 후 고쳐서 **새 커밋** 생성 (amend 금지)
- **push 거부** (`rejected`, non-fast-forward): force push 하지 말고 사용자에게 상황 알림 (`git pull --rebase` 필요한지 확인)

## 응답 스타일

- 중간 진행상황은 짧게 (한 줄씩)
- 최종 요약은 "완료. `<해시>` pushed" 정도로 간결하게
- 한국어로 답변
