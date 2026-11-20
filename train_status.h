		 

void process_train_status(CAN2_MSG msg)
{
    unsigned int received_alive;
    unsigned int received_state;

    /* Check emergency message */
    if(msg.id == EMERGENCY_ID &&
       msg.dlc == 1 &&
       msg.rtr == 0 &&
       (msg.byteA & 0xFF) == 0xFF)
    {
        emergency_active = 1;

        if(gate_state == GATE_OPEN ||
           gate_state == GATE_OPENING)
        {
            gate_state = GATE_CLOSING;
        }

        return;
    }

    /* Check TRAIN_STATUS message */
    if(msg.id != TRAIN_STATUS_ID ||
       msg.dlc != 4 ||
       msg.rtr != 0)
    {
        return;
    }

    /* Extract train state */
    received_state = msg.byteA & 0xFF;

    if(received_state > TRAIN_CLEARED)
        return;

    /* Extract alive counter */
    received_alive = (msg.byteA >> 24) & 0xFF;

    /* First received message */
    if(alive_received_flag == 0)
    {
        last_ecu1_alive = received_alive;
        alive_received_flag = 1;
    }
    else
    {
        /* Ignore duplicate message */
        if(received_alive == last_ecu1_alive)
            return;

        last_ecu1_alive = received_alive;
    }

    /* Fresh message received */
    last_train_status_update = ms_count;
    communication_timeout = 0;

    /* Extract train information */
    train_state = received_state;
    train_count = (msg.byteA >> 8) & 0xFF;
    distance = (msg.byteA >> 16) & 0xFF;

    /* Train approaching */
    if(train_state == TRAIN_APPROACHING)
    {
        if(three_second_timer_start == 0)
        {
            three_second_start_time = ms_count;
            three_second_timer_start = 1;
        }
    }

    /* Train on crossing */
    else if(train_state == TRAIN_CROSSING)
    {
        three_second_timer_start = 0;

        if(gate_state == GATE_OPEN ||
           gate_state == GATE_OPENING)
        {
            gate_state = GATE_CLOSING;
        }
    }

    /* Train cleared */
    else if(train_state == TRAIN_CLEARED ||
            train_state == TRAIN_CLEAR)
    {
        three_second_timer_start = 0;

        if(train_count == 0 &&
           emergency_active == 0 &&
           (gate_state == GATE_CLOSED ||
            gate_state == GATE_CLOSING))
        {
            gate_state = GATE_OPENING;
        }
    }
}
