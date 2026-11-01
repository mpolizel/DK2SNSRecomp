# Changelog

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
