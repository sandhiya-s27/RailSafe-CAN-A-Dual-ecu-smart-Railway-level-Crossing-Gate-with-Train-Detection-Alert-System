			

void IR_CHECK(void)
{
    /* IR1: Train entry */

    if((IOPIN1 & (1<<16)) == 0)
    {
        ir1_high_candidate = 0;

        if(ir1_low_candidate == 0)
        {
            ir1_low_candidate = 1;
            ir1_low_start = ms_count;
        }

        if(ir1_flag == 0 &&
           ms_count - ir1_low_start >= 20)
        {
            ir1_flag = 1;

            if(train_count < 9)
                train_count++;

            train_state = TRAIN_APPROACHING;

            safety_wait_flag = 0;
        }
    }
    else
    {
        ir1_low_candidate = 0;

        if(ir1_flag == 1)
        {
            if(ir1_high_candidate == 0)
            {
                ir1_high_candidate = 1;
                ir1_high_start = ms_count;
            }

            if(ms_count - ir1_high_start >= 20)
            {
                ir1_flag = 0;
                ir1_high_candidate = 0;
            }
        }
    }

    /* IR2: Train exit */

    if((IOPIN1 & (1<<17)) == 0)
    {
        ir2_high_candidate = 0;

        if(ir2_low_candidate == 0)
        {
            ir2_low_candidate = 1;
            ir2_low_start = ms_count;
        }

        if(ir2_flag == 0 &&
           ms_count - ir2_low_start >= 20)
        {
            ir2_flag = 1;

            if(train_count > 0)
                train_state = TRAIN_ON_CROSSING;
        }
    }
    else
    {
        ir2_low_candidate = 0;

        if(ir2_flag == 1)
        {
            if(ir2_high_candidate == 0)
            {
                ir2_high_candidate = 1;
                ir2_high_start = ms_count;
            }

            if(ms_count - ir2_high_start >= 20)
            {
                ir2_flag = 0;
                ir2_high_candidate = 0;

                if(train_count > 0)
                {
                    train_count--;

                    if(train_count == 0)
                    {
                        delay_2sec_ecu1 = ms_count;
                        safety_wait_flag = 1;
                    }
                }
            }
        }
    }
}
