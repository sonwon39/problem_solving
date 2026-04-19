---
name: git 인증 세팅
description: 이 repo 의 GitHub remote URL 과 credential 저장 방식. PAT 를 URL 에 박지 않는다는 규칙 포함.
type: reference
---

- **Remote URL**: `https://github.com/sonwon39/problem_solving.git` (HTTPS)
  - 2026-04-19 에 `baekjoon` 에서 `problem_solving` 으로 rename 됨 (로컬 폴더 + GitHub repo 둘 다)
- **Credential helper**: `manager` (Windows Credential Manager). `git config --global credential.helper manager` 로 설정됨
  - 첫 push 때 브라우저 인증 한 번, 그 이후 자동
  - 토큰 꼬이면 `제어판 → 자격 증명 관리자 → Windows 자격 증명` 에서 `git:https://github.com` 항목 삭제 후 재시도
- **금지**: remote URL 안에 PAT 박아두는 방식 (`https://ghp_xxx@github.com/...`)
  - `git remote -v` / 로그 / 스크린샷으로 토큰 노출됨
  - 과거 이 방식으로 토큰이 노출된 적 있어 해당 토큰은 revoke 됨
- 다른 PC 에서 clone 할 때도 동일하게 credential helper 만 세팅하고, URL 에는 토큰 박지 말 것
