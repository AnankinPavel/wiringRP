#include "wiringPi.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "RepkaPi.h"

#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <limits.h>
#include "softPwm.h"
#include "softTone.h"

#ifdef CONFIG_REPKAPI

#if CONFIG_REPKAPI_3_H5
int pinToGpioRepkaPi [64] =
{
	12, 11,    // 0, 1
	 7,  4,    // 2, 3
	 5,  8,    // 4  5
	 6,  9,    // 6, 7
    10,354,    // 8, 9
   355, 64,    //10,11
	65,  2,    //12,13
	66, 67,    //14,15
     3, 19,    //16,17
	18,  0,    //18,19
	 1,363,    //20,21
   362, 16,    //22,23
	13, 21,    //24,25
	15, 14,    //26,27

	-1, -1,    //28,29
	-1, -1,    //30,31

	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // ... 47
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,// ... 63
};

int physToGpioRepkaPi [64] =
{
	-1,          // 0
	-1,    -1,   // 1, 2
	12,    -1,   // 3, 4
	11,    -1,   // 5, 6
	 7,     4,   // 7, 8
	-1,     5,   // 9, 10
	 8,     6,   //11, 12
	 9,    -1,   //13, 14
	10,   354,   //15, 16
	-1,   355,   //17, 18
	64,    -1,   //19, 20
	65,     2,   //21, 22
	66,    67,   //23, 24
	-1,     3,   //25, 26
	19,    18,   //27, 28
	 0,    -1,   //29, 30
	 1,   363,   //31, 32
   362,    -1,   //33, 34
	16,    13,   //35, 36
	21,    15,   //37, 38
	-1,    14,   //39, 40
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //41-> 55
	-1, -1, -1, -1, -1, -1, -1, -1 // 56-> 63
};

int physToPinRepkaPi [64] = //return wiringPI pin
{
  -1,       // 0
  -1, -1,   // 1, 2
   0, -1,  //3, 4
   1, -1,  //5, 6
   2,  3,  //7, 8
  -1,  4, //9,10
   5,  6, //11,12
   7, -1, //13,14
   8,  9, //15,16
  -1, 10, //17,18
  11, -1, //19,20
  12, 13, //21,22
  14, 15, //23, 24
  -1, 16,  // 25, 26
  17, 18,   //27, 28
  19,  -1,  //29, 30
  20, 21,  //31, 32
  22, -1, //33, 34
  23, 24, //35, 36
  25, 26, //37, 38
  -1, 27, //39, 40
// Padding:

  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // ... 56
  -1, -1, -1, -1, -1, -1, -1,   // ... 63
};

int REPKAPI_PIN_MASK[12][32] =  //[BANK]  [INDEX]
{
 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,-1,18,19,-1,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PA
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PB
 { 0, 1, 2, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PC
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PD
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PE
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PF
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PG
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PH
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PI
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PJ
 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PK
 {-1,-1, 2, 3,-1,-1,-1,-1,-1,-1,10,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},//PL
};
#endif


/*
 * Data for use with the boardId functions.
 * The order of entries here to correspond with the PI_MODEL_X
 * and PI_VERSION_X defines in wiringPi.h
 * Only intended for the gpio command - use at your own risk!
 */

const char *piModelNames[6] =
{
    "Unknown",
    "Model A",
    "Model B",
    "Model B+",
    "Compute Module",
#ifdef CONFIG_REPKAPI_3_H5
	"OrangePi H5 family",
#endif
};

volatile uint32_t *RepkaPi_gpio;
volatile uint32_t *RepkaPi_gpioC;
int pwmmode = 1;

const char * int2bin(uint32_t param) {
    int bits = sizeof(uint32_t)*CHAR_BIT;
    static char buffer[sizeof(uint32_t)*CHAR_BIT + 1];
    char chars[2] = {'0', '1'};
    int i,j,offset;
    for (i = 0; i < bits; i++) {
        j = bits - i - 1;
        offset = (param & (1 << j)) >> j;
        buffer[i] = chars[offset];
    }
    buffer[bits] = '\0';
    return buffer;
}

/*
 * Read register value helper  
 */
unsigned int readR(unsigned int addr)
{

	uint32_t val = 0;
	uint32_t mmap_base = (addr & ~MAP_MASK);
	uint32_t mmap_seek = ((addr - mmap_base) >> 2);

	if (addr >= GPIOL_BASE) {
		val = *(RepkaPi_gpioC + mmap_seek);
	} else		
		val = *(RepkaPi_gpio + mmap_seek);
	return val;

}

/*
 * Wirte value to register helper
 */
void writeR(unsigned int val, unsigned int addr)
{

	unsigned int mmap_base = (addr & ~MAP_MASK);
	unsigned int mmap_seek = ((addr - mmap_base) >> 2);
		        
	if (addr >= GPIOL_BASE) {
		*(RepkaPi_gpioC + mmap_seek) = val;
	} else
		*(RepkaPi_gpio + mmap_seek) = val;

}

void print_pwm_reg() {
    uint32_t val = readR(SUNXI_PWM_CTRL_REG);
    uint32_t val2 = readR(SUNXI_PWM_CH0_PERIOD);
    if (wiringPiDebug) {
        printf("SUNXI_PWM_CTRL_REG: %s\n", int2bin(val));
        printf("SUNXI_PWM_CH0_PERIOD: %s\n", int2bin(val2));
    }
}

void sunxi_pwm_set_enable(int en) {
    int val = 0;
    val = readR(SUNXI_PWM_CTRL_REG);
    if (en) {
        val |= (SUNXI_PWM_CH0_EN | SUNXI_PWM_SCLK_CH0_GATING);
    }
    else {
        val &= ~(SUNXI_PWM_CH0_EN | SUNXI_PWM_SCLK_CH0_GATING);
    }
    if (wiringPiDebug)
        printf(">>function%s,no:%d,enable? :0x%x\n", __func__, __LINE__, val);
    writeR(val, SUNXI_PWM_CTRL_REG);
    delay(1);
    print_pwm_reg();
}

void sunxi_pwm_set_mode(int mode) {
    int val = 0;
    val = readR(SUNXI_PWM_CTRL_REG);
    mode &= 1; //cover the mode to 0 or 1
    if (mode) { //pulse mode
        val |= (SUNXI_PWM_CH0_MS_MODE | SUNXI_PWM_CH0_PUL_START);
        pwmmode = 1;
    } else { //cycle mode
        val &= ~(SUNXI_PWM_CH0_MS_MODE);
        pwmmode = 0;
    }
    val |= (SUNXI_PWM_CH0_ACT_STA);
    if (wiringPiDebug)
        printf(">>function%s,no:%d,mode? :0x%x\n", __func__, __LINE__, val);
    writeR(val, SUNXI_PWM_CTRL_REG);
    delay(1);
    print_pwm_reg();   
}

void sunxi_pwm_set_clk(int clk) {
    int val = 0;
    if (wiringPiDebug)
        printf(">>function%s,no:%d\n", __func__, __LINE__);
    // sunxi_pwm_set_enable(0);
    val = readR(SUNXI_PWM_CTRL_REG);
    if (wiringPiDebug)
        printf("read reg val: 0x%x\n", val);
    //clear clk to 0
    val &= 0xf801f0;
    val |= ((clk & 0xf) << 15); //todo check wether clk is invalid or not
    writeR(val, SUNXI_PWM_CTRL_REG);
    sunxi_pwm_set_enable(1);
    if (wiringPiDebug)
        printf(">>function%s,no:%d,clk? :0x%x\n", __func__, __LINE__, val);
    delay(1);
    print_pwm_reg();
}

/**
 * ch0 and ch1 set the same,16 bit period and 16 bit act
 */
int sunxi_pwm_get_period(void) {
    uint32_t period_cys = 0;
    period_cys = readR(SUNXI_PWM_CH0_PERIOD); //get ch1 period_cys
    if (wiringPiDebug) {
        printf("periodcys: %d\n", period_cys);
    }
    period_cys &= 0xffff0000; //get period_cys
    period_cys = period_cys >> 16;
    if (wiringPiDebug)
        printf(">>func:%s,no:%d,period/range:%d", __func__, __LINE__, period_cys);
    delay(1);
    return period_cys;
}

int sunxi_pwm_get_act(void) {
    uint32_t period_act = 0;
    period_act = readR(SUNXI_PWM_CH0_PERIOD); //get ch1 period_cys
    period_act &= 0xffff; //get period_act
    if (wiringPiDebug)
        printf(">>func:%s,no:%d,period/range:%d", __func__, __LINE__, period_act);
    delay(1);
    return period_act;
}

void sunxi_pwm_set_period(int period_cys) {
    uint32_t val = 0;
    //all clear to 0
    if (wiringPiDebug)
        printf(">>func:%s no:%d\n", __func__, __LINE__);
    period_cys &= 0xffff; //set max period to 2^16
    period_cys = period_cys << 16;
    val = readR(SUNXI_PWM_CH0_PERIOD);
    if (wiringPiDebug)
        printf("read reg val: 0x%x\n", val);
    val &= 0x0000ffff;
    period_cys |= val;
    if (wiringPiDebug)
        printf("write reg val: 0x%x\n", period_cys);
    writeR(period_cys, SUNXI_PWM_CH0_PERIOD);
    delay(1);
    val = readR(SUNXI_PWM_CH0_PERIOD);
    if (wiringPiDebug)
        printf("readback reg val: 0x%x\n", val);
    print_pwm_reg();
}

void sunxi_pwm_set_act(int act_cys) {
    uint32_t per0 = 0;
    //keep period the same, clear act_cys to 0 first
    if (wiringPiDebug)
        printf(">>func:%s no:%d\n", __func__, __LINE__);
    per0 = readR(SUNXI_PWM_CH0_PERIOD);
    if (wiringPiDebug)
        printf("read reg val: 0x%x\n", per0);
    per0 &= 0xffff0000;
    act_cys &= 0xffff;
    act_cys |= per0;
    if (wiringPiDebug)
        printf("write reg val: 0x%x\n", act_cys);
    writeR(act_cys, SUNXI_PWM_CH0_PERIOD);
    delay(1);
    print_pwm_reg();
}


int RepkaPi_get_gpio_mode(int pin)
{
	unsigned int regval = 0;
	unsigned int bank   = pin >> 5;
	unsigned int index  = pin - (bank << 5);
	unsigned int phyaddr = 0;
	unsigned char mode = -1;
	

	int offset = ((index - ((index >> 3) << 3)) << 2);

	if (bank == 11) {
		phyaddr = GPIOL_BASE + ((index >> 3) << 2);
	}
	else
		phyaddr = GPIO_BASE_MAP + (bank * 36) + ((index >> 3) << 2);

	/* Ignore unused gpio */
	if (REPKAPI_PIN_MASK[bank][index] != -1) {
		regval = readR(phyaddr);
		mode = (regval >> offset) & 7;
	}

	return mode;
}

/*
 * Set GPIO Mode
 */
int RepkaPi_set_gpio_mode(int pin, int mode)
{
    unsigned int regval = 0;
    unsigned int bank   = pin >> 5;
    unsigned int index  = pin - (bank << 5);
    unsigned int phyaddr = 0;

	int offset = ((index - ((index >> 3) << 3)) << 2);

	if (bank == 11) {
		phyaddr = GPIOL_BASE + ((index >> 3) << 2);
	}
	else
		phyaddr = GPIO_BASE_MAP + (bank * 36) + ((index >> 3) << 2);

#ifdef CONFIG_REPKAPI_2G_IOT
    /* Offset of register */
	if (bank == 0)            /* group A */
		base_address = GPIOA_BASE;
	else if (bank == 1)       /* group B */
		base_address = GPIOB_BASE;
	else if (bank == 2)       /* group C */
		base_address = GPIOC_BASE;
	else if (bank == 3)       /* group D */
		base_address = GPIOD_BASE;
	else
		printf("Bad pin number\n");

	if (mode == INPUT) 
		phyaddr = base_address + SET_IN_REGISTER;
	else if (mode == OUTPUT)
		phyaddr = base_address + OEN_SET_OUT_REGISTER;
	else
		printf("Invalid mode\n");
#elif (defined CONFIG_REPKAPI_RK3399 || defined CONFIG_REPKAPI_4 || defined CONFIG_REPKAPI_4_LTS || defined CONFIG_REPKAPI_800)
	if(bank == 1){
		cru_phyaddr = PMUCRU_BASE + PMUCRU_CLKGATE_CON1_OFFSET;
		grf_phyaddr = PMUGRF_BASE + ((index >> 3) << 2) + 0x10;
		gpio_phyaddr = GPIO1_BASE + GPIO_SWPORTA_DDR_OFFSET;
	}

	else if(bank == 2){
		cru_phyaddr = CRU_BASE + CRU_CLKGATE_CON31_OFFSET;
		grf_phyaddr = GRF_BASE + ((index >> 3) << 2);
		gpio_phyaddr = GPIO2_BASE + GPIO_SWPORTA_DDR_OFFSET;
	}
	else if(bank == 4){
		cru_phyaddr = CRU_BASE + CRU_CLKGATE_CON31_OFFSET;
		grf_phyaddr = GRF_BASE + ((index >> 3) << 2) +0x20;
		gpio_phyaddr = GPIO4_BASE + GPIO_SWPORTA_DDR_OFFSET;
	}
	else;

#elif (defined CONFIG_REPKAPI_R1PLUS)
	if(bank == 2){ //gpio2
		cru_phyaddr = CRU_BASE + CRU_CLKGATE_CON16_OFFSET;
		//grf_phyaddr = GRF_BASE + ((index >> 3) << 2) + 0x10;
		gpio_phyaddr = GPIO2_BASE + GPIO_SWPORTA_DDR_OFFSET;
		if(0 == (index >> 3))//gpio2_ax
		{
			grf_phyaddr = GRF_BASE + 0x20;
		}
		else if(3 == (index >> 3))//gpio2_dx
		{
			grf_phyaddr = GRF_BASE + 0x34;
		}
	}
	else if(bank == 3){
		cru_phyaddr  = CRU_BASE + CRU_CLKGATE_CON16_OFFSET;
		//grf_phyaddr  = GRF_BASE + ((index >> 3) << 2) +0x20;
		gpio_phyaddr = GPIO3_BASE + GPIO_SWPORTA_DDR_OFFSET;
		if (0 == (index >> 3))
		{
			if(4 == offset)//gpio3_a4
			{
				grf_phyaddr  = GRF_BASE + 0x38;
			}
			else//gpio3_a567
			{
				grf_phyaddr  = GRF_BASE + 0x3c;
			}
		}
		else if(2 == (index >> 3)) //gpio3_c
		{
			grf_phyaddr  = GRF_BASE + 0x48;
		}
	}
	else;
#endif

    /* Ignore unused gpio */
    if (REPKAPI_PIN_MASK[bank][index] != -1) {
#if ! (defined CONFIG_REPKAPI_2G_IOT || defined CONFIG_REPKAPI_RK3399 || CONFIG_REPKAPI_4 || defined CONFIG_REPKAPI_4_LTS || defined CONFIG_REPKAPI_800 || CONFIG_REPKAPI_R1PLUS)
		regval = readR(phyaddr);
			if (wiringPiDebug)
				printf("Before read reg val: 0x%x offset:%d\n",regval,offset);
#endif
        if (wiringPiDebug)
            printf("Register[%#x]: %#x index:%d\n", phyaddr, regval, index);

        /* Set Input */
        if(INPUT == mode) {

			regval &= ~(7 << offset);
			writeR(regval, phyaddr);
            regval = readR(phyaddr);
            if (wiringPiDebug)
                printf("Input mode set over reg val: %#x\n",regval);

        } else if(OUTPUT == mode) { /* Set Output */

			regval &= ~(7 << offset);
			regval |=  (1 << offset);
			if (wiringPiDebug)
				printf("Out mode ready set val: 0x%x\n",regval);
			writeR(regval, phyaddr);
            regval = readR(phyaddr);
            if (wiringPiDebug)
                printf("Out mode get value: 0x%x\n",regval);

        }else if (PWM_OUTPUT == mode) {
            // set pin PWMx to pwm mode
            regval &= ~(7 << offset);
            regval |= (0x3 << offset);
            if (wiringPiDebug)
                printf(">>>>>line:%d PWM mode ready to set val: 0x%x\n", __LINE__, regval);
            writeR(regval, phyaddr);
            delayMicroseconds(200);
            regval = readR(phyaddr);
            if (wiringPiDebug)
                printf("<<<<<PWM mode set over reg val: 0x%x\n", regval);
            //clear all reg
            writeR(0, SUNXI_PWM_CTRL_REG);
            writeR(0, SUNXI_PWM_CH0_PERIOD);

            //set default M:S to 1/2
            sunxi_pwm_set_period(1024);
            sunxi_pwm_set_act(512);
            pwmSetMode(PWM_MODE_MS);
            sunxi_pwm_set_clk(PWM_CLK_DIV_120); //default clk:24M/120
            delayMicroseconds(200);
        } 
		else {
            printf("Unknow mode\n");
        }
    } else
        printf("Pin mode failed!\n");

    return 0;
}

/*
 * Set GPIO Pull Up/Down
 */
int RepkaPi_set_gpio_pullUpDnControl(int pin, int pud)
{
	unsigned int regval = 0;
	unsigned int bank = pin >> 5;
	unsigned int index = pin - (bank << 5);
	unsigned int phyaddr = 0;
	unsigned int bit_value = -1, bit_enable = 0;
	unsigned int offset;


	unsigned int pullOffset = 0x1C;
	switch (pud)
	{
	case PUD_OFF:
		bit_value = SUNXI_PUD_OFF;
		break;
	case PUD_UP:
		bit_value = SUNXI_PUD_UP;
		break;
	case PUD_DOWN:
		bit_value = SUNXI_PUD_DOWN;
		break;
	default:
		printf("Unknow pull mode\n");
		return 0;
	}
	offset = ((index - ((index >> 4) << 4)) << 1);
	pullOffset = 0x1C;

	if (bank == 11)
	{
		phyaddr = pullOffset + GPIOL_BASE + ((index >> 4) << 2);
	}
	else
		phyaddr = pullOffset + GPIO_BASE_MAP + (bank * 36) + ((index >> 4) << 2);

	/* Ignore unused gpio */
	if (REPKAPI_PIN_MASK[bank][index] != -1)
	{
		if (wiringPiDebug)
			printf("bank: %d, index: %d\n", bank, index);

		regval = readR(phyaddr);
		if (wiringPiDebug)
			printf("read val(%#x) from register[%#x]\n", regval, phyaddr);

		/* clear bit */
		regval &= ~(3 << offset);

		/* bit write enable*/
		regval |= bit_enable;

		/* set bit */
		regval |= (bit_value & 3) << offset;

		if (wiringPiDebug)
			printf("write val(%#x) to register[%#x]\n", regval, phyaddr);

		writeR(regval, phyaddr);
		regval = readR(phyaddr);

		if (wiringPiDebug)
			printf("over reg val: %#x\n", regval);
	}
	else
		printf("Pin pull control failed!\n");

	return 0;
}

//#if !(defined CONFIG_REPKAPI_RK3399 || defined CONFIG_REPKAPI_4 || defined CONFIG_REPKAPI_4_LTS || defined CONFIG_REPKAPI_800 || defined CONFIG_REPKAPI_R1PLUS || CONFIG_REPKAPI_2G_IOT)
int RepkaPi_set_gpio_alt(int pin, int mode)
{
	unsigned int regval = 0;
	unsigned int bank   = pin >> 5;
	unsigned int index  = pin - (bank << 5);
	unsigned int phyaddr = 0;
	int offset = ((index - ((index >> 3) << 3)) << 2);

	if (bank == 11) {
		phyaddr = GPIOL_BASE + ((index >> 3) << 2);
	}else
		phyaddr = GPIO_BASE_MAP + (bank * 36) + ((index >> 3) << 2);

	/* Ignore unused gpio */
	if (REPKAPI_PIN_MASK[bank][index] != -1) {
		if (wiringPiDebug)
			printf("Register[%#x]: %#x index:%d\n", phyaddr, regval, index);

		regval = readR(phyaddr);
		regval &= ~(7 << offset);
		regval |=  (mode << offset);
		writeR(regval, phyaddr);
	} else
		printf("Pin alt mode failed!\n");

	return 0;
}
//#endif

/*
 * RepkaPi Digital write 
 */
int RepkaPi_digitalWrite(int pin, int value)
{
    unsigned int bank   = pin >> 5;
    unsigned int index  = pin - (bank << 5);
    unsigned int phyaddr = 0;

    unsigned int regval = 0;
	
	if (bank == 11) {
		phyaddr = GPIOL_BASE + 0x10;
	}
	else
		phyaddr = GPIO_BASE_MAP + (bank * 36) + 0x10;


    /* Ignore unused gpio */
    if (REPKAPI_PIN_MASK[bank][index] != -1) {

		regval = readR(phyaddr);
		if (wiringPiDebug)
			printf("befor write reg val: 0x%x,index:%d\n", regval, index);
		if(0 == value) {
			regval &= ~(1 << index);
			writeR(regval, phyaddr);
			regval = readR(phyaddr);
			if (wiringPiDebug)
				printf("LOW val set over reg val: 0x%x\n", regval);
		} else {
			regval |= (1 << index);
			writeR(regval, phyaddr);
			regval = readR(phyaddr);
			if (wiringPiDebug)
				printf("HIGH val set over reg val: 0x%x\n", regval);
		}

    } else
        printf("Pin mode failed!\n");

    return 0;
}

/*
 * RepkaPi Digital Read
 */
int RepkaPi_digitalRead(int pin)
{
	int bank = pin >> 5;
	int index = pin - (bank << 5);
	int val;
#if ! (defined CONFIG_REPKAPI_2G_IOT || defined CONFIG_REPKAPI_RK3399 || CONFIG_REPKAPI_4 || defined CONFIG_REPKAPI_4_LTS || defined CONFIG_REPKAPI_800 || defined CONFIG_REPKAPI_R1PLUS)

	unsigned int phyaddr;
	
	if (bank == 11) {
		phyaddr = GPIOL_BASE + 0x10;
	}
	else
		phyaddr = GPIO_BASE_MAP + (bank * 36) + 0x10;
#endif


	if (REPKAPI_PIN_MASK[bank][index] != -1) {
#ifndef CONFIG_REPKAPI_2G_IOT
		val = readR(phyaddr);
		val = val >> index;
		val &= 1;
		if (wiringPiDebug)
			printf("Read reg val: 0x%#x, bank:%d, index:%d\n", val, bank, index);
		return val;
#else
		if (readR(phys_OEN_R) & GPIO_BIT(index))   /* Input */ 
			val = (readR(phys_VAL_R) & GPIO_BIT(index)) ? 1 : 0;
		else                                       /* Ouput */
			val = (readR(phys_SET_R) & GPIO_BIT(index)) ? 1 : 0;
		return val;
#endif
	}
	return 0;
}

/*
 * Probe RepkaPi Platform.
 */
int isRepkaPi(void)
{
	FILE *cpuFd;
	char line [120];
	char *d;
#ifdef CONFIG_REPKAPI_3_H5
	/* Support: RepkaPi 3 */
	char *OrangePi_string = "sun50iw2";


#else
	/* Non-support */
	char *OrangePi_string = "none";
#endif

       //printf("OrangePi String is %s\n", OrangePi_string);

       return 1;

	if ((cpuFd = fopen("/proc/cpuinfo", "r")) == NULL)
		piGpioLayoutOops ("Unable to open /proc/cpuinfo") ;
    
	while (fgets(line, 120, cpuFd) != NULL) {
		if (strncmp(line, "Hardware", 8) == 0)
			break;
	}

	fclose(cpuFd);

#if (defined CONFIG_REPKAPI_RK3399 || defined CONFIG_REPKAPI_4 || defined CONFIG_REPKAPI_4_LTS || defined CONFIG_REPKAPI_800)
	strcpy(line, "Hardware		  : Rockchip rk3399 Family");
#elif (defined CONFIG_REPKAPI_R1PLUS)
	strcpy(line, "Hardware		  : Rockchip rk3328 Family");	
#endif 

	if (strncmp(line, "Hardware", 8) != 0)
		piGpioLayoutOops("No \"Hardware\" line");

	for (d = &line [strlen (line) - 1]; (*d == '\n') || (*d == '\r') ; --d)
		*d = 0;

	if (wiringPiDebug)
		printf("piboardRev: Hardware string: %s\n", line);

	if (strstr(line, OrangePi_string) != NULL) {
		if (wiringPiDebug)
			printf("Hardware:%s\n",line);
		return 1;
	} else {
		if (wiringPiDebug)
			printf("Hardware:%s\n",line);
		return 0;
	}
}

#endif /* CONFIG_REPKAPI */
