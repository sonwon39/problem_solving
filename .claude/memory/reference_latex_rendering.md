---
name: LaTeX 수식 렌더링 정책
description: 대화창과 .md 파일에서의 LaTeX 렌더링 차이, 수식 작성 규칙
type: reference
---

## 어디서 렌더링되나

- **Claude Code 대화창 (VSCode extension)**: CommonMark + monospace. `$...$`, `$$...$$` **렌더링 안 됨** — 그냥 `$` 문자로 보인다.
- **`.md` 파일**:
  - **GitHub 웹**: `$...$`, `$$...$$` 네이티브 KaTeX 렌더링.
  - **VSCode 마크다운 프리뷰** (`Ctrl+Shift+V`): 네이티브 KaTeX 렌더링.

## 작성 규칙

**대화창 답변:**
- Unicode 수학 기호(Σ π δ Ω · ≠ ≡ ⋯ √ ∈ ∀ 등) + 코드블록 활용.
- LaTeX 문법 사용 금지. `\frac{}{}` 같은 건 그대로 문자로 보인다.
- 간단한 식은 백틱 인라인(`x[n]`), 긴 식은 ```` ``` ```` 블록.

**`.md` 파일 작성:**
- LaTeX 수식을 자유롭게 씀. 문서 서두에
  `> LaTeX 수식 포함. GitHub 또는 VSCode 마크다운 프리뷰에서 렌더링.`
  같은 안내 한 줄 넣어두면 사용자가 평문으로 열었을 때 혼란 없음.
- 인라인 `$...$`, 블록 `$$...$$`, `\begin{aligned}...\end{aligned}` 등 일반 LaTeX 문법 사용.

## Why

대화창 렌더링 제약은 harness 차원의 결정(CommonMark + monospace)이라 설정 변경 불가.
하지만 파일로 저장하는 문서는 GitHub/VSCode 에서 예쁘게 렌더링되므로, 수식이 많은 배경지식은 파일로 저장하는 게 훨씬 깔끔하다.
