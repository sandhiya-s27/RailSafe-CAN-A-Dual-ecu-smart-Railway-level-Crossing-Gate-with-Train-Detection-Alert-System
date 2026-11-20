			

void check_communication_timeout(void)
{
    if(ms_count - last_gate_rx_time >= 500)
        communication_timeout = 1;
    else
        communication_timeout = 0;
}