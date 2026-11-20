			
/* ---------------- SERVO CONTROL ---------------- */

void servo_control(void)
{
    if(ms_count - servo_time >= 20)
    {
        servo_time = ms_count;

        /* Close gate */
        if(gate_state == GATE_CLOSING)
        {
            if(servo_position < 1500)
            {
                servo_position += 10;

                if(servo_position > 1500)
                    servo_position = 1500;

                PWMMR2 = servo_position;
                PWMLER = (1<<2);
            }

            if(servo_position >= 1500)
            {
                gate_state = GATE_CLOSED;
            }
        }

        /* Open gate */
        else if(gate_state == GATE_OPENING)
        {
            if(servo_position > 1000)
            {
                servo_position -= 10;

                if(servo_position < 1000)
                    servo_position = 1000;

                PWMMR2 = servo_position;
                PWMLER = (1<<2);
            }

            if(servo_position <= 1000)
            {
                gate_state = GATE_OPEN;
            }
        }
    }
}
