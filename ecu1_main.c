 #include<LPC21XX.H>
#include"header.h"
#include "can_driver.h"


/* LCD connections: D4-D7 = P0.16-P0.19 */
#define LCD_D (0xF << 16)
#define RS (1 << 5)
#define E (1 << 6)

/* Train states */
#define TRAIN_CLEAR 0
#define TRAIN_APPROACHING 1
#define TRAIN_ON_CROSSING 2
#define TRAIN_CLEARED 3

/* Gate states */
#define GATE_OPEN 0
#define GATE_CLOSING 1
#define GATE_CLOSED 2
#define GATE_OPENING 3

/* Function declarations */
void Timer1_ISR(void) __irq;

void delay_milliseconds(unsigned int);
void LCD_SEND_NIBBLE(unsigned char);
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STRING(char *);

void timer1_init(void);
void IR_CHECK(void);
void safety_check(void);
int send_train_status(void);
void receive_gate_status(void);
void check_communication_timeout(void);
void startup_display(void);
void display_lcd(void);

/* Timer1 millisecond counter */
volatile unsigned int ms_count = 0;

/* Train information */
unsigned int train_count = 0;
unsigned int train_state = TRAIN_CLEAR;

/* IR sensor flags */
unsigned int ir1_flag = 0;
unsigned int ir2_flag = 0;

/* IR debounce timing */
unsigned int ir1_low_start = 0;
unsigned int ir1_high_start = 0;
unsigned int ir2_low_start = 0;
unsigned int ir2_high_start = 0;

unsigned int ir1_low_candidate = 0;
unsigned int ir1_high_candidate = 0;
unsigned int ir2_low_candidate = 0;
unsigned int ir2_high_candidate = 0;

/* Two-second safety wait */
unsigned int delay_2sec_ecu1 = 0;
unsigned int safety_wait_flag = 0;

/* CAN transmission timing */
unsigned int can_tx_time = 0;
unsigned char alive_counter = 0;

/* Received gate information */
unsigned int gate_status = GATE_OPEN;
unsigned int signal_status = 0;
unsigned int buzzer_status = 0;

unsigned int last_gate_rx_time = 0;
unsigned int communication_timeout = 0;

/* CAN messages */
CAN2_MSG tx_msg, rx_msg;

/* LCD previous display values */
unsigned int old_train_state = 255;
unsigned int old_train_count = 255;
unsigned int old_gate_status = 255;
unsigned int old_communication_timeout = 255;

/* Startup display timing */
unsigned int startup_time = 0;

#include "timer0_delay.h"
#include "lcd_header4bit.h"
#include "timerdelay.h"
#include "ir_check.h"
#include "safety.h"
#include "ecu1_tx.h"
#include "ecu1_rx.h"
#include "timeout.h"
#include "titledisplay.h"
#include"lcd_display.h"

/* ---------------- MAIN FUNCTION ---------------- */

int main(void)
{
    VPBDIV = 1;

    /* Configure IR pins as input */
    IODIR1 &= ~((1<<16) | (1<<17));

    /* Initialize CAN2 */
    can2_init();

    /* Initialize Timer1 */
    timer1_init();

    /* Initialize LCD */
    LCD_INIT();

    /* Display project title */
    startup_display();

    while(1)
    {
        IR_CHECK();

        safety_check();

        if(ms_count - can_tx_time >= 100)
        {
            if(send_train_status())
                can_tx_time = ms_count;
        }

        receive_gate_status();

        check_communication_timeout();

        if(ms_count - startup_time >= 2000)
        {
            display_lcd();
        }
    }
}

