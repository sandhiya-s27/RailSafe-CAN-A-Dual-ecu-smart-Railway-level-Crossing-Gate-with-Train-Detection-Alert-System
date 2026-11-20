

int send_train_status(void)
{
    tx_msg.id = 0x100;
    tx_msg.dlc = 4;
    tx_msg.rtr = 0;

    /* Byte 0: Train state
       Byte 1: Train count
       Byte 2: Distance = 0
       Byte 3: Alive counter */

    tx_msg.byteA = (train_state & 0xFF)
                 | ((train_count & 0xFF) << 8)
                 | ((unsigned int)alive_counter << 24);

    tx_msg.byteB = 0;

    can2_tx(tx_msg);

    alive_counter++;

    return 1;
}
