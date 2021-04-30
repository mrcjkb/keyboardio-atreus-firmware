# keyboardio-atreus-firmware
My Keyboardio Atreus firmware.

## Depends on:

- [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope)
- [Kaleidoscope-Languages](https://github.com/keyboardio/Kaleidoscope-Languages)
- arduino-cli


## Build/Flash firmware:

- Make sure [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope) is checked out and the `KALEIDOSCOPE_DIR` environment variable is set ([see Kaleidoscope readme](https://github.com/keyboardio/Kaleidoscope#use-git-to-check-out-a-copy-of-kaleidoscope)).
- Additonally, make sure [Kaleidoscope-Languages](https://github.com/keyboardio/Kaleidoscope-Languages) is checked out and set the KALEIDOSCOPE_LANGUAGES_DIR environment variable.
- `make compile` to build
- `make flash` to flash
