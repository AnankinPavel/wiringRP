# wiringRP
wiringPi for Repka Pi
## How to download wiringRP

```
# apt-get update
# apt-get install -y git
# git clone https://github.com/AnankinPavel/wiringRP.git
```

## How to build wiringOP

```
# cd wiringRP
# ./build clean
# ./build 
```

---
## The output of the gpio readall command

## Allwinner H5

### Repka Pi 3

```
 +------+-----+----------+------+    RepkaPi3H5    +------+----------+-----+------+
 | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
 +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
 |      |     |     3.3V |      |   |  1 || 2  |   |      | 5V       |     |      |
 |   12 |   0 |    SDA.0 | ALT2 | 0 |  3 || 4  |   |      | 5V       |     |      |
 |   11 |   1 |    SCL.0 | ALT2 | 0 |  5 || 6  |   |      | GND      |     |      |
 |    6 |   2 |      PA6 |  OFF | 0 |  7 || 8  | 0 | ALT2 | TXD.1    | 3   | 198  |
 |      |     |      GND |      |   |  9 || 10 | 0 | ALT2 | RXD.1    | 4   | 199  |
 |    1 |   5 |    RXD.2 | ALT2 | 0 | 11 || 12 | 0 | OFF  | PA07     | 6   | 7    |
 |    0 |   7 |    TXD.2 | ALT2 | 0 | 13 || 14 |   |      | GND      |     |      |
 |    3 |   8 |    CTS.2 |  OFF | 0 | 15 || 16 | 0 | ALT3 | SDA.1    | 9   | 19   |
 |      |     |     3.3V |      |   | 17 || 18 | 0 | ALT3 | SCL.1    | 10  | 18   |
 |   15 |  11 |   MOSI.1 | ALT2 | 0 | 19 || 20 |   |      | GND      |     |      |
 |   16 |  12 |   MISO.1 | ALT2 | 0 | 21 || 22 | 0 | OFF  | RTS.2    | 13  | 2    |
 |   14 |  14 |   SCLK.1 | ALT2 | 0 | 23 || 24 | 0 | ALT2 | CE.1     | 15  | 13   |
 |      |     |      GND |      |   | 25 || 26 | 0 | OFF  | PA10     | 16  | 10   |
 +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
 | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
 +------+-----+----------+------+    RepkaPi3H5    +------+----------+-----+------+
```
