# Contributor Quickstart: Runtime Flow

This guide summarizes how the app runs so you can trace code paths quickly when making changes.

## Startup sequence
- **Settings**: `pixelai.ini` is read from the executable directory if present. The app runs with built-in defaults when the file is missing or malformed.
- **History**: Capture history starts empty on launch. New captures are added in-memory as you record them.
- **Model**: The recognizer loads `pixelai_examples.bin` beside the executable when it exists. Missing models simply disable classification until you learn and save examples.

## Capture pipeline
- **Global mouse hook**: A low-level mouse hook watches for `WM_LBUTTONUP` outside the app window and posts a capture message so you can record without focusing the app.
- **Patch acquisition**: `CapturePatchAroundCursor()` produces a fixed 360×960 BGRA portrait frame anchored near the cursor (~18% from the top) and clamps at screen edges so the frame stays full-sized.
- **History entry**: Successful captures are appended to in-memory history, selected immediately, and written as BMPs to `captures/` beside the executable (unique names per capture). The preview invalidates to show the latest patch, and the status bar reflects success or failure.

## Classification flow
- **UI-driven**: Classification runs from the Classify button in the app (no global F5 hook). The handler reuses the `DoClassify()` flow.
- **Scoring**: Classification runs cosine similarity over the normalized RGB feature vectors stored in memory, returning the best label when the score meets the configured confidence threshold (`PixelRecognizer::min_confidence`, default 0.85).

## Model training, saving, and backups
- **Learning**: The "Learn Label" button prompts for a label, adds the current capture as an example, and saves `pixelai_examples.bin` in the executable directory.
- **Backups**: Successful saves write timestamped backups beside the model file according to `BackupRetention` in `pixelai.ini` (default 5, only when the file exists and the value is positive).
- **Persistence**: After optional backup, the updated examples are written to `pixelai_examples.bin`. Failures surface in the status bar; classification relies on the file being readable at next startup.

## Adjusting settings (`pixelai.ini`)
- Location: Same directory as the executable; optional file (omit to keep defaults).
- Keys: Under `[Saving]`, `BackupRetention` controls how many timestamped backups to keep (0 disables cleanup). Add more keys here as new features require them.

## Quick pointers to source
- **UI and hooks**: `VisualRecognition/src/ui.ixx` (app wiring), `VisualRecognition/src/ui.hooks.ixx` (mouse hook), `VisualRecognition/src/ui.capture.ixx` (capture/classify flows), `VisualRecognition/src/ui.filesystem.ixx` (capture storage, model persistence, settings helpers).
- **Recognizer**: `VisualRecognition/src/pixelai.ixx` (feature extraction, cosine similarity, load/save format).

## Macro hotkeys
- **Global keyboard hooks** drive the macro engine even when the app is unfocused: **F7** Record, **F8** Clear, **F9** Play/Stop, **F6** Exit. These mirror the buttons in the macro bar.

## Capture history lifecycle
- **Storage**: Each capture is saved as a BMP under `captures/` beside the executable and linked to its history entry.
- **Clear**: "Clear preview" wipes the on-screen image, clears history, and deletes any capture files from the session.
- **Delete**: "Delete Capture" removes the selected entry and deletes its BMP if present, updating selection/status accordingly.
