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
 +------+-----+----------+------+---+RepkaPi3H5+---+------+----------+-----+------+
 | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
 +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
 |      |     |     3.3V |      |   |  1 || 2  |   |      | 5V       |     |      |
 |   12 |   0 |     PA12 | ALT2 | 0 |  3 || 4  |   |      | 5V       |     |      |
 |   11 |   1 |     PA11 | ALT2 | 0 |  5 || 6  |   |      | GND      |     |      |
 |    7 |   2 |      PA7 |  OFF | 0 |  7 || 8  | 0 | ALT2 | PA4      | 3   | 4    |
 |      |     |      GND |      |   |  9 || 10 | 0 | ALT2 | PA5      | 4   | 5    |
 |    8 |   5 |      PA8 |  OFF | 0 | 11 || 12 | 0 | OFF  | PA6      | 6   | 6    |
 |    9 |   7 |      PA9 |  OFF | 0 | 13 || 14 |   |      | GND      |     |      |
 |   10 |   8 |     PA10 |  OFF | 0 | 15 || 16 | 0 | ALT2 | PL2      | 9   | 354  |
 |      |     |     3.3V |      |   | 17 || 18 | 0 | ALT2 | PL3      | 10  | 355  |
 |   64 |  11 |      PC0 | ALT3 | 0 | 19 || 20 |   |      | GND      |     |      |
 |   65 |  12 |      PC1 | ALT3 | 0 | 21 || 22 | 0 | OFF  | PA2      | 13  | 2    |
 |   66 |  14 |      PC2 | ALT3 | 0 | 23 || 24 | 0 | ALT3 | PC3      | 15  | 67   |
 |      |     |      GND |      |   | 25 || 26 | 1 | OUT  | PA3      | 16  | 3    |
 |   19 |  17 |     PA19 |  OFF | 0 | 27 || 28 | 0 | OFF  | PA18     | 18  | 18   |
 |    0 |  19 |      PA0 | ALT2 | 0 | 29 || 30 |   |      | GND      |     |      |
 |    1 |  20 |      PA1 | ALT2 | 0 | 31 || 32 | 0 | OFF  | PL11     | 21  | 363  |
 |  362 |  22 |     PL10 |  OFF | 0 | 33 || 34 |   |      | GND      |     |      |
 |   16 |  23 |     PA16 | ALT2 | 0 | 35 || 36 | 0 | ALT2 | PA13     | 24  | 13   |
 |   21 |  25 |     PA21 |  OFF | 0 | 37 || 38 | 0 | ALT2 | PA15     | 26  | 15   |
 |      |     |      GND |      |   | 39 || 40 | 0 | ALT2 | PA14     | 27  | 14   |
 +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
 | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
 +------+-----+----------+------+---+RepkaPi3H5+---+------+----------+-----+------+

```
