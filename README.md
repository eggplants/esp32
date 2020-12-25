# What is this

- handle esp32 with [micropython](https://github.com/micropython/micropython)
- with [arduino ide]()

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
