# What is this

- handle esp32 with [micropython](https://github.com/micropython/micropython)
- with [arduino ide](https://www.arduino.cc/en/software)

## First

```bash
$ ./allow_dev.sh
```

## Useful links

- ESP32 MicroPython documentation
  - ja: <https://micropython-docs-ja.readthedocs.io/ja/latest/esp32/quickref.html>

- The reference of Arduino ESP32
  - ja: <https://garretlab.web.fc2.com/arduino/esp32/reference>

## Useful commands

### ampy

- write/read file

```bash
$ pip install adafruit-ampy
$ export AMPY_PORT=/dev/ttyUSB0
$ ampy ls
```

### mu-editor

- GUI code editor for micropython

```bash
$ pip install pipenv
$ pipenv --python 3.7
$ pipenv install mu-editor
# not japanese but english
$ LANG=C pipenv run mu-editor
# use latest version
$ git clone https://github.com/mu-editor/mu
$ pyenv global 3.7.9
$ cd mu && python -m pip install -e .
$ mu-editor
```

### picocom

- Connect to REPL through serial communication

```bash
$ sudo apt install picocom
$ picocom /dev/ttyUSB0 -b 115200
```

### fritzing

- Designing Circuits IDE

```bash
$ sudo apt install fritzing
$ fritzing
```

### esptool.py

```bash
$ pip install esptool
$ esptool.py --port /dev/ttyUSB0 erase_flash
# Micropython
$ wget \
    "http://micropython.org/resources/firmware/esp32-idf3-20200902-v1.13.bin"
# Original firmware
# Goto: https://github.com/espressif/esp-at/releases/tag/v2.1.0.0_esp32s2
# Download: ESP32-S2-WROOM_AT_Bin_V2.1.0.0.zip
# Copy: factory/factory_WROOM.bin
$ esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash \
    -z 0x1000 esp32-*.bin
```
