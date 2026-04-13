---
name: 재사용 가능한 흐름은 skill 로 만든다 (slash command 아님)
description: 반복 작업을 자동화할 때 `.claude/commands/` 가 아닌 `.claude/skills/<name>/SKILL.md` 로 작성
type: feedback
---

재사용 가능한 작업 흐름은 **skill** (`.claude/skills/<name>/SKILL.md`, YAML frontmatter 포함) 로 만든다. slash command 파일 (`.claude/commands/*.md`) 로 만들지 말 것.

**Why:** 2026-04-13 commit-push 스킬 작업 중 사용자가 "스킬로 만들어 달라 한 거야" 라고 명시적으로 교정함. 기존 스킬들(hint/concept/roadmap/review/counterexample/postsolve) 도 모두 `.claude/skills/` 경로에 있어 일관성 유지 목적.

**How to apply:**
- "~~ 스킬 만들어줘", "커맨드로 만들어줘", "자동화해줘" 류 요청 → 무조건 `.claude/skills/<name>/SKILL.md` 생성
- frontmatter 에 `name`, `description` 필수. description 은 "언제 이 스킬을 쓰는지" 가 드러나야 함 (다른 스킬 파일들 참고)
- 본문은 `# /<name> — 한 줄 요약` 제목으로 시작하고, 기존 스킬 파일들과 구조 맞춤 (입력 파싱 / 실행 순서 / 금지 사항 / 엣지 케이스 등)
