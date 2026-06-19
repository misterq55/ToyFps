# Copilot Instructions for ToyFPS

Use this file as a thin, stable policy layer.

## References
- Primary coding/style rules: `docs/code-convention.md`

## Must-follow rules
- Treat `docs/code-convention.md` as the single source of truth for coding conventions.
- Keep runtime modules free of editor-only dependencies (`UnrealEd`, `Slate`, `PropertyEditor`, `AssetTools`) unless the target is explicitly editor-only.
- Preserve one-way dependency direction: runtime <- editor.
- Do not modify generated or intermediate outputs (`Binaries/`, `Intermediate/`, `DerivedDataCache/`, `Saved/`) unless explicitly requested.

## Change hygiene
- Keep edits minimal and focused on the requested goal.
- Preserve existing user changes; do not revert unrelated work.
- When touching module structure, explain dependency changes and verify packaging safety in `*.Build.cs`, `*.uplugin`, and `ToyFPS.uproject`.


