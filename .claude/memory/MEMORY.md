<!-- Claude Code memory index. One-line entries pointing to memory files in this folder. -->

- [user profile](user_profile.md) — BOJ/CF/AtCoder 학습자, C++/Python, 여러 PC 환경(username 다름), Win11 + 개발자 모드
- [메모리 동기화 구조](project_memory_sync.md) — repo `.claude/memory/` 를 symlink 로 Claude Code 경로에 연결, git 으로 여러 PC 동기화
- [skill 로 만들기](feedback_skills_over_commands.md) — 재사용 흐름은 `.claude/skills/<name>/SKILL.md` 로, slash command 금지
- [Windows symlink = mklink](feedback_windows_symlink.md) — PowerShell New-Item 말고 `cmd /c mklink /D` 사용 (PS는 dev mode 켜도 버그)
- [Git Bash HEREDOC temp file 회피](feedback_git_bash_heredoc.md) — `export TMPDIR=/tmp && mkdir -p /tmp` 를 prefix 로
- [C++ 빌드 환경 (VS2022)](reference_cpp_build.md) — `boj/cpp/build.bat <num> --run`, MSVC `mspdbcore.dll` 버그는 `/link /DEBUG:NONE` 으로 회피
- [theory/ 폴더 구조](project_theory_folder.md) — 배경 지식은 `theory/math/`, 기법은 `theory/technique/`. 풀이 코드와 분리
- [LaTeX 렌더링 정책](reference_latex_rendering.md) — 대화창은 Unicode+코드블록만, `.md` 파일은 `$...$` LaTeX 자유롭게
- [BOJ 서비스 종료](project_boj_shutdown.md) — 2026-04-28 종료 예정, 이후 제출 불가. CF/AtCoder 로 무게중심 이동
