  void receive_gate_status(void)
{
    if(can2_rx(&rx_msg))
    {
        if(rx_msg.id == 0x200 &&
           rx_msg.dlc == 4 &&
           rx_msg.rtr == 0)
        {
            gate_status = rx_msg.byteA & 0xFF;
            signal_status = (rx_msg.byteA >> 8) & 0xFF;
            buzzer_status = (rx_msg.byteA >> 16) & 0xFF;

            last_gate_rx_time = ms_count;
        }
    }
}
