# KBD firmware

## How to build

## 1. Setting Up Your QMK Environment

Please see https://docs.qmk.fm/#/newbs_getting_started and set up 1 to 3.

## 2. Getting source files

Please get source files of `qmk/qmk_firmware` and `vial-kb/vial-qmk`
```sh
make git-submodule
```

## 3. Building firmwares

### for VIA

```sh
make qmk-clean
kb=crkbd make qmk-init
kb=crkbd kr=rev4_1/standard km=via make qmk-compile
```
A built data will be stored on `keyboards/crkbd/qmk/qmk_firmware/.build`\
Please change `kb`, `kr` and `km` when build other.

### for Vial
```sh
make vial-qmk-clean
kb=crkbd make vial-qmk-init
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-compile
```
A built data will be stored on `keyboards/crkbd/vial-kb/vial-qmk/.build`\
Please change `kb`, `kr` and `km` when build other.

### All cleaning and building
```sh
make update-all
```



### Marcos lessons:

```sh
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-clean
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-init
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-compile
# crkbd in bootloader mode
kb=crkbd kr=rev4_1/standard km=vial make vial-qmk-flash
```

# Tmp fixes (hopefully to be solved in some future PR)
`.../kbd_firmware/keyboards/crkbd/qmk/qmk_firmware/rev4_1/info.json`

Find : `serial_usart` like

```
...
"transport": {
"protocol": "serial_usart",....
```

Replace `"serial_usart"` with `"serial"`

And, if you don't want to get warning, in

keyboards/crkbd/qmk/qmk_firmware/rev4_1/config.h

change :
#define RGB_DISABLE_WHEN_USB_SUSPENDED

for

#define RGB_MATRIX_SLEEP