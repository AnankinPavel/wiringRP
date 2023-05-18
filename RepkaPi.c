#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "RepkaPi.h"
#include <wiringPi.h>


#if CONFIG_REPKAPI_3_H5
int physToWpi [64] = //return wiringPI pin
{
	  -1,       // 0
  -1, -1,   	// 1, 2
   0, -1,  		// 3, 4
   1, -1,  		// 5, 6
   2,  3,  		// 7, 8
  -1,  4, 		// 9, 10
   5,  6, 		// 11, 12
   7, -1, 		// 13, 14
   8,  9, 		// 15, 16
  -1, 10, 		// 17, 18
  11, -1, 		// 19, 20
  12, 13, 		// 21, 22
  14, 15, 		// 23, 24
  -1, 16,  		// 25, 26
  17, 18,   	// 27, 28
  19, -1,  		// 29, 30
  20, 21,  		// 31, 32
  22, -1, 		// 33, 34
  23, 24, 		// 35, 36
  25, 26, 		// 37, 38
  -1, 27, 		// 39, 40

    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 41-> 55
    -1, -1, -1, -1, -1, -1, -1, -1 								// 56-> 63
};

char *physNames[64] =
{
	    NULL,
 "    3.3V", "5V      ",
 "    PA12", "5V      ",
 "    PA11", "GND     ",
 "     PA7", "PA4     ",
 "     GND", "PA5     ",
 "     PA8", "PA6     ",
 "     PA9", "GND     ",
 "    PA10", "PL2     ",
 "    3.3V", "PL3     ",
 "     PC0", "GND     ",
 "     PC1", "PA2     ",
 "     PC2", "PC3     ",
 "     GND", "PA3     ",
 "    PA19", "PA18    ",
 "     PA0", "GND     ",
 "     PA1", "PL11    ",
 "    PL10", "GND     ",
 "    PA16", "PA13    ",
 "    PA21", "PA15    ",
 "     GND", "PA14    ",
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
       NULL, NULL,
   NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
};
#endif /* CONFIG_REPKAPI_3_H5 */

/*
 * ReadAll 
 */
void RepkaPiReadAll(void)
{
    int pin;
	int tmp = wiringPiDebug;
    wiringPiDebug = FALSE;

#ifdef CONFIG_REPKAPI_3_H5
    printf (" +------+-----+----------+------+---+RepkaPi3H5+---+------+----------+-----+------+\n");
#endif

    printf (" | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |\n");
    printf (" +------+-----+----------+------+---+----++----+---+------+----------+-----+------+\n");

#if defined CONFIG_REPKAPI_3_H5
    for (pin = 1 ; pin <= 40; pin += 2)
#endif
        readallPhys(pin);

    printf (" +------+-----+----------+------+---+----++----+---+------+----------+-----+------+\n");
    printf (" | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |\n");

#ifdef CONFIG_REPKAPI_3_H5
    printf (" +------+-----+----------+------+---+RepkaPi3H5+---+------+----------+-----+------+\n");
#endif

    wiringPiDebug = tmp;
}
