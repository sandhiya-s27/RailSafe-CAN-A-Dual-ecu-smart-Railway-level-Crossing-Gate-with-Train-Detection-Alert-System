

void pwm_init(void)
{
    /* PWM2 on P0.7 */
    PINSEL0 = (PINSEL0 & ~(3<<14)) | (2<<14);

    PWMTCR = 0x02;

    /* 1us PWM timer tick */
    PWMPR = 59;

    /* 20ms period */
    PWMMR0 = 20000;

    /* Initial servo position */
    PWMMR2 = 1000;

    PWMMCR = 0x02;

    /* Enable PWM2 */
    PWMPCR = (1<<10);

    PWMLER = (1<<0) | (1<<2);

    PWMTCR = 0x09;
}
