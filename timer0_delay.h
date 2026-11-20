																			


void delay_milliseconds(unsigned int milliseconds)
{
    T0TCR = 0x02;
    T0PR = 60000 - 1;
    T0TC = 0;
    T0TCR = 0x01;

    while(T0TC < milliseconds);

    T0TCR = 0x00;
}
