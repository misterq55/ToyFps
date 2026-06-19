# ToyFPS Code Convention

This document defines coding and module-architecture conventions for the ToyFPS project.

## 1) Unreal naming
- Classes: `U` (UObject), `A` (Actor), `F` (struct/value type), `I` (interface), `T` (template/container), `E` (enum).
- Member variables: use `PascalCase` and clear intent-focused names; avoid unexplained abbreviations.
- Local variables and function parameters: use `camelCase`.
- Functions: verb-first names for actions, noun/adjective names for queries/accessors.

## 2) Module boundaries
- `WeaponSystem` is runtime-only.
- Editor-only code must stay in `WeaponEditor` (or other editor-only modules/plugins).
- Runtime modules must not depend on editor modules.
- Allowed dependency direction: runtime <- editor.

## 3) Build and dependency rules
- Keep `PublicDependencyModuleNames` minimal and intentional.
- Prefer `PrivateDependencyModuleNames` unless symbols are required by dependents.
- Do not add `UnrealEd` to runtime targets or runtime module dependencies.
- Use `TargetAllowList` for editor-only plugins in project/plugin manifests.

## 4) C++ and Unreal style
- Prefer Unreal containers/types and patterns in gameplay code.
- Prefer `TFunction` or UE delegates for callbacks in UE-facing code.
- Include headers with explicit module/plugin-safe paths when crossing module boundaries.
- Initialize local variables as `const` whenever they are not reassigned after initialization.
- Add comments only for non-obvious intent or constraints.

## 5) Safety and packaging
- Any packaging fix should preserve runtime/editor separation.
- Validate `*.Build.cs`, `.uplugin`, and `ToyFPS.uproject` together when changing architecture.
- Avoid committing transient IDE/local files unless intentionally shared.

## 6) Commit messages
- Use concise, purpose-first messages.
- Prefer Conventional Commit style where possible (`fix:`, `refactor:`, `build:`, `chore:`).
- For packaging-impact changes, mention packaging intent explicitly.


