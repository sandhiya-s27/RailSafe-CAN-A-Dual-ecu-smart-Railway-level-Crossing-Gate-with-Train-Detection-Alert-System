				

void gpio_init(void)
{
    IODIR1 |= (1<<16) | (1<<17) | (1<<18);

    /* Both LEDs OFF */
    IOSET1 = (1<<16) | (1<<17);

    /* Buzzer OFF - active LOW */
    IOSET1 = (1<<18);
}
