# Keyboardio Atreus Firmaware
My Keyboardio Atreus firmware. Based on the standard US layout, with some additional modifications to add German language keys.

## Depends on

- [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope)
- [Kaleidoscope-Languages](https://github.com/keyboardio/Kaleidoscope-Languages)
- arduino-cli


## Build/Flash firmware

- Make sure [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope) is checked out and the `KALEIDOSCOPE_DIR` environment variable is set ([see Kaleidoscope readme](https://github.com/keyboardio/Kaleidoscope#use-git-to-check-out-a-copy-of-kaleidoscope)).
- Additonally, make sure [Kaleidoscope-Languages](https://github.com/keyboardio/Kaleidoscope-Languages) is checked out and set the KALEIDOSCOPE_LANGUAGES_DIR environment variable.
- `make compile` to build
- `make flash` to flash


## Credits

- The tapDanceAction is taken from https://community.keyboard.io/t/atreus-german-qwertz-layout-with-umlaute/4159
