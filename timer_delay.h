

void timer0_init(void)
{
    T0TCR = 0x02;

    T0PR = 59;
    T0MR0 = 999;
    T0MCR = 0x03;

    VICIntSelect &= ~(1<<4);

    VICVectAddr0 = (unsigned long)timer0_isr;
    VICVectCntl0 = 0x20 | 4;

    VICIntEnable |= (1<<4);

    T0TCR = 0x01;
}

/* ---------------- TIMER0 INTERRUPT ---------------- */

__irq void timer0_isr(void)
{
    ms_count++;

    T0IR = 1;

    VICVectAddr = 0;
}
