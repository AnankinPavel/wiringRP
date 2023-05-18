#ifndef _REPKAPI_H_
#define _REPKAPI_H_

extern char *physNames[64];
extern int physToWpi[64];
extern int pinToGpioRepkaPi[64];

extern void RepkaPiReadAll(void);
extern void readallPhys(int physPin);

#endif
