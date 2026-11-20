	 

void send_gate_status(void)
{
    CAN2_MSG tx_msg;

    if(ms_count - gate_status_time >= 100)
    {
        tx_msg.id = GATE_STATUS_ID;
        tx_msg.dlc = 4;
        tx_msg.rtr = 0;

        tx_msg.byteA = gate_state |
                       (signal_state << 8) |
                       (buzzer_state << 16) |
                       (ecu2_alive_counter << 24);

        tx_msg.byteB = 0;

        can2_tx(tx_msg);

        gate_status_time = ms_count;

        ecu2_alive_counter++;

        if(ecu2_alive_counter > 255)
            ecu2_alive_counter = 0;
    }
}
