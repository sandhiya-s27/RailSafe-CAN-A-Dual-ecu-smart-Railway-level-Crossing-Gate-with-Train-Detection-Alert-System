																				


void startup_display(void)
{
    LCD_COMMAND(0x80);
    LCD_STRING("RAILSAFE CAN ");

    LCD_COMMAND(0xC0);
    LCD_STRING("SYSTEM STARTING ");

    startup_time = ms_count;
}
