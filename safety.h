				

void safety_check(void)
{
    if(train_count > 0)
        safety_wait_flag = 0;

    if(safety_wait_flag == 1)
    {
        if(ms_count - delay_2sec_ecu1 >= 2000)
        {
            if(train_count == 0)
                train_state = TRAIN_CLEARED;

            safety_wait_flag = 0;
        }
    }
}
