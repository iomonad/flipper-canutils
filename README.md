# Flipper CANutils [![FAP: Build for multiple SDK sources](https://github.com/iomonad/flipper-canutils/actions/workflows/build.yml/badge.svg)](https://github.com/iomonad/flipper-canutils/actions/workflows/build.yml)
Leverage Flipper Zero SPI ports to interact with MCP2515 and provide CANbus Sniss Knife inside your pocket

## Wiring

```
[A6] <--> MISO
[A7] <--> MOSI
[B3] <--> SCK
[A4] <--> CS
```

## Building

```
make
make launch
```

## Resources
- Visual Component Guide https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/
- OBD-II Arduino https://github.com/stanleyhuangyc/ArduinoOBD
- https://github.com/jamisonderek/flipper-zero-tutorials/wiki/User-Interface
