# My build of dwm

## FAQ

> What are the bindings?

This is suckless, buddy, the source code is the documentation! Check out [config.h](config.h).

## Patches and features

- Clickable statusbar with my build of [dwmblocks](https://github.com/joinemm/dwmblocks).
- Reads xresources colors/variables (i.e. works with `pywal`, etc.).
- Fully functional system tray.
- New layouts: bstack, fibonacci, deck, centered master and more. All bound to keys `super+(shift+)t/y/u/i`.
- True fullscreen (`super+shift+f`).
- Windows can be made sticky (`super+s`).
- stacker: Move windows up the stack manually (`super-K/J`).
- shiftview: Cycle through tags (`super+;/'`).
- vanitygaps: Runtime configurable gaps allowed across all layouts.
- swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.

## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the status/info bar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one.
