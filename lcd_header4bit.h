									   


void LCD_SEND_NIBBLE(unsigned char nibble)
{
    IOCLR0 = LCD_D;
    IOSET0 = (nibble & 0x0F) << 16;

    IOCLR0 = RS;

    IOSET0 = E;
    delay_milliseconds(2);
    IOCLR0 = E;
}

void LCD_COMMAND(unsigned char c)
{
    IOCLR0 = LCD_D;
    IOSET0 = (c & 0xF0) << 12;
    IOCLR0 = RS;
    IOSET0 = E;
    delay_milliseconds(2);
    IOCLR0 = E;

    IOCLR0 = LCD_D;
    IOSET0 = (c & 0x0F) << 16;
    IOSET0 = E;
    delay_milliseconds(2);
    IOCLR0 = E;
}

void LCD_DATA(unsigned char d)
{
    IOCLR0 = LCD_D;
    IOSET0 = (d & 0xF0) << 12;
    IOSET0 = RS;
    IOSET0 = E;
    delay_milliseconds(2);
    IOCLR0 = E;

    IOCLR0 = LCD_D;
    IOSET0 = (d & 0x0F) << 16;
    IOSET0 = E;
    delay_milliseconds(2);
    IOCLR0 = E;
}

void LCD_STRING(char *str)
{
    while(*str != '\0')
    {
        LCD_DATA(*str);
        str++;
    }
}

void LCD_INIT(void)
{
    IODIR0 |= LCD_D | RS | E;

    delay_milliseconds(20);

    /* LCD 4-bit initialization */
    LCD_SEND_NIBBLE(0x03);
    delay_milliseconds(5);

    LCD_SEND_NIBBLE(0x03);
    delay_milliseconds(2);

    LCD_SEND_NIBBLE(0x03);
    delay_milliseconds(2);

    LCD_SEND_NIBBLE(0x02);
    delay_milliseconds(2);

    LCD_COMMAND(0x28);
    LCD_COMMAND(0x0C);
    LCD_COMMAND(0x06);
    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);
}
