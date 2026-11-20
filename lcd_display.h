


void display_lcd(void)
{
    if(train_state != old_train_state ||
       train_count != old_train_count ||
       gate_status != old_gate_status ||
       communication_timeout != old_communication_timeout)
    {
        LCD_COMMAND(0x80);

        if(train_state == TRAIN_APPROACHING)
            LCD_STRING("APPROACH C:0 ");
        else if(train_state == TRAIN_ON_CROSSING)
            LCD_STRING("CROSSING C:0 ");
        else if(train_state == TRAIN_CLEARED)
            LCD_STRING("CLEARED C:0 ");
        else
            LCD_STRING("CLEAR C:0 ");

        LCD_COMMAND(0x8B);
        LCD_DATA(train_count + '0');

        LCD_COMMAND(0xC0);

        if(communication_timeout == 1)
            LCD_STRING("ECU2 LOST ");
        else
        {
            if(gate_status == GATE_OPEN)
                LCD_STRING("GATE: OPEN ");
            else if(gate_status == GATE_CLOSING)
                LCD_STRING("GATE: CLOSING ");
            else if(gate_status == GATE_CLOSED)
                LCD_STRING("GATE: CLOSED ");
            else if(gate_status == GATE_OPENING)
                LCD_STRING("GATE: OPENING ");
        }

        old_train_state = train_state;
        old_train_count = train_count;
        old_gate_status = gate_status;
        old_communication_timeout = communication_timeout;
    }
}
