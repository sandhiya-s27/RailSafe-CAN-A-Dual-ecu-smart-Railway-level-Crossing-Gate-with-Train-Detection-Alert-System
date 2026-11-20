

void signal_control(void)
{
    /* Communication lost or emergency */
    if(communication_timeout == 1 ||
       emergency_active == 1)
    {
        IOCLR1 = (1<<16);
        IOSET1 = (1<<17);

        IOCLR1 = (1<<18);

        signal_state = 1;
        buzzer_state = 1;
    }

    /* Train approaching */
    else if(train_state == TRAIN_APPROACHING)
    {
        IOSET1 = (1<<17);

        if(ms_count - red_led_time >= 250)
        {
            red_led_time = ms_count;

            if(red_led_state == 0)
            {
                IOCLR1 = (1<<16);
                red_led_state = 1;
            }
            else
            {
                IOSET1 = (1<<16);
                red_led_state = 0;
            }
        }

        IOCLR1 = (1<<18);

        signal_state = 1;
        buzzer_state = 1;
    }

    /* Train crossing */
    else if(train_state == TRAIN_CROSSING)
    {
        IOCLR1 = (1<<16);
        IOSET1 = (1<<17);

        IOCLR1 = (1<<18);

        signal_state = 1;
        buzzer_state = 1;
    }

    /* Train cleared */
    else if(train_state == TRAIN_CLEARED ||
            train_state == TRAIN_CLEAR)
    {
        IOSET1 = (1<<16);

        if(gate_state == GATE_OPEN)
        {
            IOCLR1 = (1<<17);
        }
        else
        {
            IOSET1 = (1<<17);
        }

        IOSET1 = (1<<18);

        signal_state = 0;
        buzzer_state = 0;
    }
}
