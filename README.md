# Donkey Kong Country 2 Recomp

A native recompilation of **Donkey Kong Country 2** (USA), built on
[snesrecomp](https://github.com/RetroPortingToolKit/snesrecomp).

<a href="https://recomplauncher.com/game/dk2snsrecomp"><picture><source media="(prefers-color-scheme: dark)" srcset="https://recomplauncher.com/assets/press/launcher/badge-light.svg"><img alt="Get it on RecompLauncher" src="https://recomplauncher.com/assets/press/launcher/badge-dark.svg" height="48"></picture></a>

Run Donkey Kong Country 2 natively on Windows.



> **You must legally own a copy of the game.** No ROM data is distributed with
> this project, in the repository or in any release. The recompiled C is
> generated locally from your own copy and is never committed.

## ☕ Keep the ports coming

<p align="center">
  <a href="https://buymeacoffee.com/mpolizel"><img src="https://img.shields.io/badge/Buy%20me%20a%20coffee-support%20more%20ports-FFDD00?style=for-the-badge&logo=buymeacoffee&logoColor=black" alt="Buy me a coffee"></a>
</p>

**This project is free and always will be.** Every port in this series,
Donkey Kong Country 2 included, is built with many hours of AI-assisted reverse engineering,
and that AI time is paid. If you enjoy playing it, a coffee at
**[buymeacoffee.com/mpolizel](https://buymeacoffee.com/mpolizel)** keeps the AI running so **more SNES
games can be ported to native Recomp**. Any amount helps, and thank you!

## Download (ready-to-run Windows build)

Get the latest `donkeykongcountry2-<version>-windows-x64.zip` from the
[Releases page](https://github.com/mpolizel/DK2SNSRecomp/releases/latest).

The zip is a **setup pack**: it contains the launcher, the recompiler and this
source tree (with the framework patches already applied), but no game data.
On first run:

1. Unzip anywhere and start `DonkeyKongCountry2SNESRecomp.exe`.
2. Let it download the portable build tools (one time per machine), or point
   it at a `cmake-clang-v1` zip you already have.
3. Pick your own `Donkey Kong Country 2 (USA).sfc` — Diddy's Kong Quest,
   USA (En,Fr), CRC32 `006364db`.
4. Press **Generate & rebuild**. The playable game is built into `build/` and
   started; run it from there afterwards.

[RecompLauncher](https://recomplauncher.com) can install it too: the release
carries a `recomplauncher.json`, so the launcher asks for your ROM, opens this
same setup with it already picked, and shows the window, picture and sound
settings on the game's page.

In the launcher, **Settings → Shader** lists the scanline, CRT and upscaler
presets; choosing one switches the renderer to OpenGL automatically. A fresh
install starts with no shader (the plain picture), the lightest option for
any graphics card; pick a CRT or upscaler preset there if yours has room.
Your choice is saved in `config.ini` and kept. The upscalers include
**ScaleFX** and the neural **NNEDI3** presets.

During play, **Ctrl+L** (or **Select+L3** on a controller) reopens the
launcher: shader, window scale, volume and controls apply when you press
**Resume**, without restarting the game. **I** cycles the audio interpolation
between **Gaussian** (the console's own, the default), **Cubic** (crisper
highs) and **Sinc**; it only changes what you hear, never the game, and the
choice is saved in `audio_interpolation.txt`.

On laptops with two graphics cards (NVIDIA Optimus, AMD switchable graphics)
the game asks the driver for the dedicated one. If it still runs slowly,
set the game's executable to **High performance** in Windows Settings →
System → Display → Graphics.

### Updates

With **Check for updates on start** ticked (the default; on the launcher's main
screen, next to **Skip launcher on boot**), the game asks GitHub for the latest
release when it starts and offers to install a newer one. Accepting closes the
game, downloads the new setup pack, copies it over the install folder and
reopens the setup window: press **Generate & rebuild**. Nothing is deleted;
`build\` (the rebuilt game, `saves\`, save states, `config.ini`,
`keybinds.ini`) and `rom.cfg` are kept. Untick the box to turn the check off
(saved in `update.ini`). Version 0.1.0 has no updater: update from it by hand
once.

**Your saves are never lost or broken by an update.** In-game saves and save
states made by any earlier release keep working in every later one. Before
installing, the updater copies `build\saves\` to
`save-backups\<date>_before_<version>\` and never deletes those copies; save
files are left out of the copy, and if they changed anyway the backup is put
back. Every release is checked against the one before it with
`tools/check_update_compat.ps1`. That script builds the previous release,
makes an in-game save and a save state with it, installs the new pack with the
previous release's own updater and rebuilds. It fails unless every save file
is byte-identical and the new build continues the old save state.

See [CHANGELOG.md](CHANGELOG.md) for what changed in each release.

## Status

Boots through the copyright and title screen into the attract-mode demo
(Pirate Panic gameplay). Most code still runs through the snesrecomp interpreter; levels,
saves and full play-through are not yet verified. See
[Porting from here](#porting-from-here).

### Framework patches

`patches/` holds changes to the `snesrecomp` and `recomp-ui` submodules.
Reapply them after updating the submodules:

```sh
git -C snesrecomp apply ../patches/snesrecomp-apu-first-read-timeline.patch
git -C snesrecomp apply ../patches/snesrecomp-audio-interpolation.patch
git -C snesrecomp apply ../patches/snesrecomp-glsl-passprev-and-vao.patch
git -C snesrecomp apply ../patches/snesrecomp-joypad-manual-strobe.patch
git -C snesrecomp apply ../patches/snesrecomp-mosaic-frame-model.patch
git -C snesrecomp apply ../patches/snesrecomp-nmi-idle-loop-wai.patch
git -C snesrecomp apply ../patches/snesrecomp-nmi-wai-in-handler.patch
git -C snesrecomp apply ../patches/snesrecomp-raster-oam-and-hdma.patch
git -C snesrecomp apply ../patches/snesrecomp-resume-state-restart.patch
git -C snesrecomp apply ../patches/snesrecomp-shader-forces-opengl.patch
git -C snesrecomp apply ../patches/snesrecomp-state-load-raster-reset.patch
git -C recomp-ui apply ../patches/recomp-ui-host-toggle.patch
```

The second is required for this game: DKC2's NMI handler resets the stack and
falls into a `WAI / BRA` idle loop instead of returning with RTI, and without
the patch that loop runs to the interpreter's step cap every frame (black
screen at ~4 fps). The patch also lets such a handler outlast a frame:
DKC1's NMI uploads sound data with NMI off for several frames, and
without it the upload was cut and the game froze on the intro screen.

`snesrecomp-nmi-wai-in-handler.patch` makes any `WAI` inside an interrupt
handler halt until the next interrupt, as on hardware. In Donkey Kong Country
(same Rare engine) a `WAI` left inside NMI after saving at Candy's was skipped,
the interpreter spun to its step cap and the screen stayed black; this game
gets the same fix preventively. With the same input, its memory matches the
previous build frame for frame (a 3-frame timing difference in the boot logos
of Donkey Kong Country 2 reconverges at once).

`snesrecomp-raster-oam-and-hdma.patch` is the renderer fix shared with the
Super Mario Kart port. The renderer draws after the CPU frame and replays the
frame's display writes line by line. It now keeps each sprite table (OAM) with
the line it takes effect on, initializes HDMA channels enabled in vblank before
line 1, and files a write made early in a line with the line before it, but
never across the start of vblank: the NMI's first writes (screen mode,
brightness) belong to the next frame. Filed one line early they were applied
only after that frame was drawn, which in DKC2's boot showed the Rare logo
over the Nintendo screen. It also counts HDMA's first transfer, made in V=0's
H-blank, as a table line, as the hardware does. Every HDMA split landed one
line late without it; on the Gangplank Galleon island map the palette and
layer splits fall on the same table line, and the late one drew a bright line
across the screen.

`snesrecomp-audio-interpolation.patch` adds the Cubic and Sinc audio
interpolation (I key). They resample the dry output only; the echo buffer,
OUTX, pitch modulation and save states stay those of the console's Gaussian
filter, so the game runs identically in every mode.

`snesrecomp-glsl-passprev-and-vao.patch` fixes two shader bugs: a pass that
reads `PassPrev<n>` back to the game frame got nothing (ScaleFX drew black),
and switching to no shader mid-game drew a black screen because the shader
path left the plain path's vertex attributes disabled.

`snesrecomp-apu-first-read-timeline.patch` lets the sound chip run from power
on when the game reads its ports before writing them. Kirby Super Star read
the sound port once, right after the SA-1 finishes its start-up, and uploads
its sound driver only if the chip's boot ROM answers; the framework started
the sound chip's clock at the first port write, so the read found nothing and
the game waited forever on a black screen.

`snesrecomp-joypad-manual-strobe.patch` passes the manual-read strobe
($4016 write) to the controller. The reads already reached it, the strobe did
not, so a game that reads the pad by hand got its sixteen buttons once and then
every button held, for good. Bart's Nightmare reads the pad that way in the
doors and the nightmares: it chose a door by itself and, inside a nightmare,
fell into its pause screen and waited for a Start press that could never come
(the picture frozen, the music still playing).

`snesrecomp-mosaic-frame-model.patch` builds the mosaic table on every visible
line. The optimized renderer built it only on line 0, which frame-model hosts
never render, so every line of a mosaic-enabled layer sampled the layer's
first row.

`snesrecomp-resume-state-restart.patch` makes a setting that needs a restart
come back to the same moment. The in-game launcher saves `saves\resume.sav`,
restarts and loads it before the first frame, when no session exists yet. A
save state holds the machine but not the CPU half's registers or resume
point (a load during play keeps the session's own, the game's idle loop), so
the frame driver booted from the reset vector over it. The restart file is
now written in the rollback format (machine plus execution residue), and the
frame driver takes the interpreter's resume point at the start of a frame.
Save-state slots keep their format.

`snesrecomp-shader-forces-opengl.patch` switches the renderer to OpenGL when a
shader is picked, since the presets only run there.

`snesrecomp-state-load-raster-reset.patch` re-arms the raster journal when a
save state loads. The journal keeps the register file as the last field
started and puts it back before drawing, so after a load the previous scene's
BG mode, tilemaps and windows replaced the state's; a scene that sets them only
once (Bart's Nightmare's title, its doors) stayed garbled until it changed.

`recomp-ui-host-toggle.patch` lets a title add one checkbox of its own beside
"Skip launcher on boot"; this project uses it for the update check.

## ROM identity

| | |
|---|---|
| File | `Donkey Kong Country 2 (USA).sfc` |
| Publisher | — |
| Developer | — |
| Year | — |
| Mapping | hirom |
| Region | USA (North America) |
| Coprocessor | none |
| CRC32 | `006364db` |
| SHA-256 | `35421a9af9dd011b40b91f792192af9f99c93201d8d394026bdfb42cbf2d8633` |

`tools/regen.sh` refuses to run against anything else, so a mismatched
revision fails immediately instead of producing subtly wrong output.

## Build

```sh
git submodule update --init --recursive
bash tools/regen.sh --rom /path/to/Donkey Kong Country 2 (USA).sfc
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

The ROM does not have to live in the repository — keeping it on your own
drive is the better habit, and `SNESRECOMP_ROM` sets the path once for a
shell. Without either, `tools/regen.sh` finds `Donkey Kong Country 2 (USA).sfc` at the repo root,
then the path the setup wizard recorded in `rom.cfg`; `.gitignore` blocks
both from ever being committed.

`tools/regen.sh` verifies the ROM, generates `src/gen/*.c`, and re-syncs
`recomp/funcs.h`. Re-run it whenever you change anything under `recomp/`.

## Run

```sh
./build/DonkeyKongCountry2SNESRecomp                     # launcher picks the ROM
./build/DonkeyKongCountry2SNESRecomp /path/to/Donkey Kong Country 2 (USA).sfc # or name it and skip the launcher
```

With no ROM on the command line the build opens the recomp-ui launcher: a ROM
picker with a verification badge, plus display / audio / input settings. Your
choice is cached in `rom.cfg` beside the executable, so the next launch opens
on it and "Skip launcher on boot" makes it immediate. If the launcher is not
built in (`--no-recomp-ui`), the host falls back to a native file picker.

Either way the ROM is checked against the digests above before anything boots
— a dump that could not have produced this build is refused at the door rather
than mis-executing ten frames in.

## Layout

| Path | What lives there |
|---|---|
| `recomp/` | Analysis input: `bank*.cfg`, `symbols.toml`, generated `funcs.h` |
| `rom_identity.txt` | ROM digests — read by the build, `tools/regen.sh` and CI |
| `src/` | Host code you own: `main.c`, `game_rtl.c` |
| `src/gen/` | Generated C. Never committed — regenerate locally |
| `snesrecomp/` | Framework submodule (owns `lib/recomp-net`, `lib/retcomm-rbengine`) |
| `tools/` | `regen.sh` — the ROM → C pipeline |
| `scripts/` | `package_release.sh` — player-facing zip |
| `framework_pins.txt` | Exact framework commits this project was scaffolded against |

## Porting from here

The scaffold stops where the game-specific work starts. In rough order:

1. **Make it boot.** `src/game_rtl.c` holds the frame driver. It starts on
   the framework's beam-aligned driver (`snesrecomp/runner/src/beam_frame_driver.h`):
   one frame per PPU field, interrupts taken where the beam latches them,
   the field rasterized from the raster journal. A title whose main loop it
   does not fit replaces those calls with its own driver.
2. **Name things.** Add entries to `recomp/symbols.toml` as you identify
   routines, then re-run `tools/regen.sh`. Set `emit = true` to promote one
   into ahead-of-time analysis; leave it false to keep it interpreted.
   Regen synchronizes the marked blocks in each bank cfg, creating missing
   configs. Only proven variants become AOT code. See `recomp/README.md`.
3. **Resolve dispatch misses.** After every run, deal with unresolved
   indirect targets before anything else — they are the reason a port
   diverges, and they are cheap to fix early.
4. **Never synthesise a result** to get past uncovered code, and never edit
   `src/gen/` by hand. Fix the config or the framework and regenerate.

## Multiplayer

Two players, one controller per port.

## License

This project's own source is under the MIT license in `LICENSE`. The
framework carries its own terms (PolyForm Noncommercial 1.0.0) — see
`snesrecomp/LICENSE` and `snesrecomp/THIRD_PARTY_ATTRIBUTION.md`; the changes
in `patches/` apply to that framework and falls under its terms. The
shaders under `assets/shaders/_libretro/` come from libretro/glsl-shaders and
keep each author's license in their file headers. None of these cover the
game data, which is not distributed here.

---

<p align="center">
  Enjoying Donkey Kong Country 2 Recomp? <a href="https://buymeacoffee.com/mpolizel"><b>☕ Buy me a coffee</b></a> to help
  bring the next SNES game to native Recomp.
</p>
