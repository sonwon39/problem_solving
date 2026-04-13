---
name: Git Bash on Windows HEREDOC temp file 오류 회피
description: Windows Git Bash 에서 HEREDOC 이 temp file 오류로 실패할 때 TMPDIR 을 /tmp 로 설정
type: feedback
---

Windows Git Bash 에서 `git commit -m "$(cat <<'EOF' ... EOF)"` 같은 HEREDOC 이 `cannot create temp file for here-document: No such file or directory` 로 실패하면 **`export TMPDIR=/tmp && mkdir -p /tmp` 를 앞에 붙여서** 재실행한다.

**Why:** 2026-04-13 첫 commit 시 기본 TMPDIR 경로가 존재하지 않아 HEREDOC 파싱 자체가 실패, 빈 커밋 메시지로 이어져 커밋 abort. `/tmp` 를 명시하면 해결됨. Git Bash 환경 자체의 문제라 이 머신에서 반복 발생할 가능성 높음.

**How to apply:**
- 이 프로젝트에서 커밋 메시지를 HEREDOC 으로 전달할 때는 기본적으로 prefix 를 붙여서 실행:
  ```bash
  export TMPDIR=/tmp && mkdir -p /tmp && git commit -m "$(cat <<'EOF'
  ...
  EOF
  )"
  ```
- commit-push 스킬 문서에 이미 이 회피법 적어둠 (`.claude/skills/commit-push/SKILL.md`)
