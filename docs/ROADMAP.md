# Roadmap and Next Steps

## Current State
- Win32 UI (`src/ui.ixx`) captures a 360×960 portrait patch anchored to the cursor (~18% from the top), writes each capture as a BMP into `captures/` beside the executable, and displays it in a preview area.
- A global mouse hook triggers captures on left click even when the app is unfocused, while classification remains UI-only via the Classify button (no global F5 hook).
- The `PixelRecognizer` (`src/pixelai.ixx`) stores labeled patches, performs cosine-similarity matching, and saves/loads models to `pixelai_examples.bin` alongside the executable.
- Learning flow prompts for a label, trains in-memory, writes timestamped backups next to the model file, and attempts to persist the updated `pixelai_examples.bin` immediately.
- Startup loads `pixelai_examples.bin`, creating a placeholder file when none exists and surfacing load failures through the status bar and dialogs.

## Immediate Opportunities
1. **Hook Coverage**: add a global classification hotkey (or alternate gesture) so captures triggered outside the app window can be classified without focusing the UI.
2. **UX Feedback**: indicate when no capture is available, show confidence thresholds, and expose `min_confidence` as a setting, especially now that captures are saved automatically to `captures/`.
3. **Stability**: guard Win32 handles in `ui.ixx` (preview/status HWNDs, hooks) to reduce leak risk on failures.
4. **Testing Hooks**: add minimal unit coverage for `PixelRecognizer` (cosine similarity, persistence round-trip) using a cross-platform test target.
5. **Release Packaging**: script a release build that bundles the executable and default model for distribution.

## Next Steps Checklist
- [ ] Decide on module build strategy for non-MSVC toolchains or document MSVC-only support explicitly.
- [x] Implement startup load of `pixelai_examples.bin` with status messaging, placeholder creation when missing, and fallbacks for load failures.
- [ ] Extract preview drawing into a smaller helper to simplify `ui.ixx` and enable potential resizing modes.
- [ ] Add a configuration surface (ini file or registry) to persist confidence thresholds and capture radius.
- [ ] Document manual QA scenarios (multi-monitor capture, classification with no examples, repeated learning).
