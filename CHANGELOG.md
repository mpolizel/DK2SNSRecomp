# Changelog

## 0.1.6 — 2026-11-12

Current snesrecomp and recomp-ui, and RecompLauncher's recommendations. The
framework brings its access-exact sound timing (a per-clock S-DSP), sprite
priority, brightness-rounding, HDMA and mosaic fixes: over the same test run
2302 of 3000 frames now match snes9x exactly, where 0.1.5 matched 2215. A
setting that needs a restart (renderer, audio output) comes back to the same
moment instead of starting the game over; a game that reads the controller
by hand gets fresh buttons on every read; a save state loaded in another
scene is no longer drawn with the previous scene's registers. Save states
now keep the CPU's place, so one loaded during the logos, a menu or the map
resumes where it was made. Your in-game save and the save states from 0.1.5
keep loading, with the music playing on (the old sound state is converted).
With [RecompLauncher](https://recomplauncher.com) the game builds on the
launcher's setup screen, Play goes straight into the game, Big Picture opens
full screen, and the renderer and shader are on the game's page. Controllers
are no longer read while the window is in the background ([General]
BackgroundInput = 1 restores that); the log keeps the last runs. The update
check on start stays; when RecompLauncher starts the game it leaves updates
to the launcher.

## 0.1.5 — 2026-11-03

### Changed
- A fresh install starts with **no shader** (the plain picture), the lightest
  option. A full-screen CRT shader made the game drop frames on weaker laptops.
  Pick CRT Lottes or another preset under Settings → Shader; your choice is
  still saved and kept. An install that already has a shader keeps it.
- On laptops with two graphics cards (NVIDIA Optimus, AMD switchable
  graphics), the game now asks for the **dedicated graphics card** instead of
  the integrated one.

## 0.1.4 — 2026-11-03

### Fixed
- Preventive fix for a black screen after saving. Donkey Kong Country could
  stay on a black screen (sound still playing) after saving at Candy's. This
  game runs on the same engine and gets the same fix, so saving at
  Kong Kollege cannot freeze for that reason.

## 0.1.3 — 2026-11-02

### New
- A fresh install starts with the **CRT Lottes** shader. An install that
  already has a shader chosen keeps it.
- **Updates never cost you a save.** Before installing, the updater copies your
  in-game saves and save states to `save-backups\<date>_before_<version>\`.
  Save files are left out of the copy, and if they changed anyway the backup
  is put back. Saves and save states from earlier versions keep working.
- Every release is now checked before publishing: a save and a save state made
  in the previous version must survive the update and load in the new one.

## 0.1.2 — 2026-11-02

### New
- **Settings during play:** Ctrl+L (or Select+L3 on a controller) reopens the
  launcher. Shader, window scale, volume and controls apply when you press
  Resume, without restarting the game.
- **Audio interpolation:** press **I** to cycle Gaussian (the console's own,
  default), Cubic (crisper highs) and Sinc. It changes only what you hear;
  the game, its echo and save states are unaffected. The choice is kept.
- New upscaler shaders: **ScaleFX**, **NNEDI3 (neural)** and **NNEDI3
  (neural, high)**.

### Fixed
- A bright horizontal line across the Gangplank Galleon island map. Every
  HDMA raster effect started one line late; they now start on the line the
  game asks for.
- Choosing **None** as the shader during play no longer leaves a black
  screen.
- Multi-pass shaders that read the original game frame from a later pass
  (ScaleFX) no longer draw black.

## 0.1.1 — 2026-11-01

### New
- **Check for updates on start** (on the launcher's main screen, next to
  *Skip launcher on boot*; on by default). When a newer release is out the
  game offers to install it: it downloads the new setup pack, copies it over
  the install without deleting anything, keeps your ROM selection and reopens
  the setup window; press **Generate & rebuild**. In-game saves, save states
  and settings are kept; save states from an older version may not load in a
  newer one.
- A fresh install starts with the **CRT Geom (curved)** shader. Any renderer
  or shader you pick in the launcher is saved and kept.

### Fixed
- Renderer: sprites now use the sprite table that was current on each line,
  HDMA effects enabled during vblank start on the first line, and writes made
  at the start of vblank are no longer applied one frame late (screens could
  show the previous screen's layout for a frame on a mode change).
- The Rare logo no longer appears over the Nintendo screen at boot.

Updating from 0.1.0: unpack this release's zip over your install folder once
(0.1.0 has no updater), start `DonkeyKongCountry2SNESRecomp.exe` and press
**Generate & rebuild**. Later versions update themselves.

## 0.1.0 — 2026-10-30

First release: a setup pack that recompiles the game from your own ROM. Boots
through the copyright and title screen into the attract-mode demo. Scanline,
CRT and upscaler shader presets; console-free Windows build.
