#ifndef _REPKAPI_H
#define _REPKAPI_H

#if CONFIG_REPKAPI_3_H5
/************** RepkaPi H5 ***********************/
#define GPIOA_BASE                         (0x01C20000)
#define GPIO_NUM                           (0x40)
#define GPIO_BASE_MAP                      (0x01C20800)
#define MEM_INFO                           (1024)
#define GPIOL_BASE                         (0x01F02c00)
#define GPIOL_BASE_MAP                     (0x01F02000)  
#define MAP_SIZE_L                         (4096 * 2)
#define GPIO_PWM_OP			   (0x01C21000)
#endif

/****************** Global data *********************/
/* Current version */
#define PI_MAKER_REPKAPI  4
#define MAX_PIN_NUM        GPIO_NUM
#define MAP_SIZE           MAP_SIZE_L
#define MAP_MASK           (MAP_SIZE - 1)
#define PI_GPIO_MASK       (~(GPIO_NUM - 1))
#define GPIO_BASE          GPIOA_BASE
#define REPKAPI_MEM_INFO  MEM_INFO
#define GPIO_PWM 		   GPIO_PWM_OP


//sunxi_pwm
#define SUNXI_PWM_BASE (0x01c21400)
#define SUNXI_PWM_CTRL_REG  (SUNXI_PWM_BASE)
#define SUNXI_PWM_CH0_PERIOD  (SUNXI_PWM_BASE + 0x4)
#define SUNXI_PWM_CH1_PERIOD  (SUNXI_PWM_BASE + 0x8)

#define SUNXI_PWM_CH0_EN   (1 << 4)
#define SUNXI_PWM_CH0_ACT_STA  (1 << 5)
#define SUNXI_PWM_SCLK_CH0_GATING (1 << 6)
#define SUNXI_PWM_CH0_MS_MODE  (1 << 7) //pulse mode
#define SUNXI_PWM_CH0_PUL_START  (1 << 8)

#define PWM_CLK_DIV_120  0
#define PWM_CLK_DIV_180  1
#define PWM_CLK_DIV_240  2
#define PWM_CLK_DIV_360  3
#define PWM_CLK_DIV_480  4
#define PWM_CLK_DIV_12K  8
#define PWM_CLK_DIV_24K  9
#define PWM_CLK_DIV_36K  10
#define PWM_CLK_DIV_48K  11
#define PWM_CLK_DIV_72K  12

#define SUNXI_PUD_OFF   0
#define SUNXI_PUD_UP    1
#define SUNXI_PUD_DOWN  2

extern int pinToGpioRepkaPi[64];
extern int physToGpioRepkaPi[64];
extern int physToPinRepkaPi[64];
extern int physToWpiRepkaPi[64];
extern volatile unsigned int *RepkaPi_gpio;
extern volatile unsigned int *RepkaPi_gpioC;

extern int pinToGpioR3[64];
extern int physToGpioR3[64];
extern int physToPinR3[64];
extern int pwmmode;

extern unsigned int readR(unsigned int addr);
extern void writeR(unsigned int val, unsigned int addr);
extern int RepkaPi_set_gpio_mode(int pin, int mode);
extern int RepkaPi_set_gpio_pullUpDnControl(int pin, int pud);

extern int OrangePi_set_gpio_alt(int pin, int mode);

extern int RepkaPi_get_gpio_mode(int pin);
extern int isRepkaPi_2G_IOT(void);
extern int isRepkaPi(void);
extern unsigned int readR(unsigned int addr);
extern void writeR(unsigned int val, unsigned int addr);
extern int RepkaPi_digitalWrite(int pin, int value);
extern int RepkaPi_digitalRead(int pin);

extern void print_pwm_reg(void);
extern void sunxi_pwm_set_enable(int en);
extern void sunxi_pwm_set_mode(int mode);
extern void sunxi_pwm_set_clk(int clk);
extern int sunxi_pwm_get_period(void);
extern int sunxi_pwm_get_act(void);
extern void sunxi_pwm_set_period(int period_cys);
extern void sunxi_pwm_set_act(int act_cys);


#ifdef CONFIG_REPKAPI
extern const char *piModelNames[6];
#endif

#ifdef CONFIG_REPKAPI_3_H5
extern int REPKAPI_PIN_MASK[12][32];
#endif

#endif
