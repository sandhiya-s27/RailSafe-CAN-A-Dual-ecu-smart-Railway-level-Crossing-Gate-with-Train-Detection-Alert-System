

#include <LPC21xx.H>
#include "header.h"
#include "can_driver.h"
volatile unsigned int ms_count = 0;

/* Train information */
unsigned int train_state = TRAIN_CLEAR;
unsigned int train_count = 0;
unsigned int distance = 0;

/* Gate information */
unsigned int gate_state = GATE_OPEN;
unsigned int signal_state = 0;
unsigned int buzzer_state = 0;

/* Communication monitoring */
unsigned int communication_timeout = 1;
unsigned int last_train_status_update = 0;
unsigned int last_ecu1_alive = 0;
unsigned int alive_received_flag = 0;

/* Emergency */
unsigned int emergency_active = 0;

/* Three-second warning timer */
unsigned int three_second_timer_start = 0;
unsigned int three_second_start_time = 0;

/* Servo */
unsigned int servo_position = 1000;
unsigned int servo_time = 0;

/* Red LED blinking */
unsigned int red_led_state = 0;
unsigned int red_led_time = 0;

/* Gate status transmission */
unsigned int ecu2_alive_counter = 0;
unsigned int gate_status_time = 0;

/* CAN message */
CAN2_MSG msg;

/* Function declarations */
void timer0_init(void);
void gpio_init(void);
void pwm_init(void);
void servo_control(void);
void process_train_status(CAN2_MSG msg);
void signal_control(void);
void send_gate_status(void);

__irq void timer0_isr(void);

#include "timer_delay.h"
#include "gpio.h"
#include "pwm.h"
#include "servo_control.h"
#include "train_status.h"
#include "signal.h"
#include "gatestatus.h"

/* ---------------- MAIN FUNCTION ---------------- */

int main(void)
{
    VPBDIV = 1;

    gpio_init();
    timer0_init();
    pwm_init();
    can2_init();

    while(1)
    {
        /* 1. Receive CAN message */
        if(can2_rx(&msg))
        {
            process_train_status(msg);
        }

        /* 2. Check communication timeout */
        if(ms_count - last_train_status_update >= 500)
        {
            communication_timeout = 1;
        }

        /* 3. Fail-safe operation */
        if(communication_timeout == 1 ||
           emergency_active == 1)
        {
            three_second_timer_start = 0;

            if(gate_state == GATE_OPEN ||
               gate_state == GATE_OPENING)
            {
                gate_state = GATE_CLOSING;
            }
        }

        /* 4. Check three-second warning delay */
        if(communication_timeout == 0 &&
           emergency_active == 0 &&
           train_state == TRAIN_APPROACHING &&
           three_second_timer_start == 1 &&
           ms_count - three_second_start_time >= 3000)
        {
            if(gate_state == GATE_OPEN ||
               gate_state == GATE_OPENING)
            {
                gate_state = GATE_CLOSING;
            }
        }

        /* 5. Move servo */
        servo_control();

        /* 6. Control LEDs and buzzer */
        signal_control();

        /* 7. Send gate status to ECU1 */
        send_gate_status();
    }
}
