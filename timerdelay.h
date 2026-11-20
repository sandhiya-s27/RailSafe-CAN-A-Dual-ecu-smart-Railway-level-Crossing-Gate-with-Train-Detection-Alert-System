					   


void timer1_init(void)
{
    T1TCR = 0x02;

    T1PR = 59;
    T1MR0 = 999;
    T1MCR = 3;

    VICIntSelect &= ~(1<<5);

    VICVectAddr0 = (unsigned long)Timer1_ISR;
    VICVectCntl0 = 0x25;

    VICIntEnable |= (1<<5);

    T1TCR = 0x01;
}

/* ---------------- TIMER1 ISR ---------------- */

void Timer1_ISR(void) __irq
{
    T1IR = 1;

    ms_count++;

    VICVectAddr = 0;
}
