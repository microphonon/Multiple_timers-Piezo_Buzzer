#include <msp430.h> 
/*
Use the MSP430FR5969 Launchpad to play a repetitive two-tone sequence through an external piezoelectric buzzer. Square 
waves are generated at 2200 and 1300 Hz, which are the maritime radiotelephone distress frequencies. Tone duration is 
set by timer TA0 sourced to the VLO clock at 10 kHz. Tone frequency is set by TA1 sourced to SMCLK at 500 kHz. Drive 
the buzzer with TA1.1 output on P1.2. Use the TA0 interrupt to change the frequency.
*/
volatile int i;
void main(void) {

        WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
        _BIS_SR(GIE); //Enable global interrupts.

        P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7; //Set P1 pins to outputs
        //Setup TA1.1 output on P1.2
        P1SEL0 |= BIT2;
        P1SEL1 &= ~BIT2;
        PM5CTL0 &= ~LOCKLPM5; //Unlock the configured GPIO pins

        CSCTL0 = CSKEY; //Password to unlock the clock registers
        CSCTL2 |= SELA__VLOCLK;  //Set ACLK to VLO with default frequency ~ 10 kHz; SMCLK default 1 MHz
        CSCTL0_H = 0xFF; //Re-lock the clock registers; probably optional

        //Enable the TA0 interrupt, MC_1 to count up to TA0CCR0, set to ACLK (VLO)
        TA0CCTL0 = CCIE;
        TA0CTL |= MC_1 + TASSEL_1;

        TA1CCTL1 = OUTMOD_2; //Set output mode to toggle/reset on TA1.1; see Family Users Guide
        //Configure TA1. Select SMCLK at 1 MHz, divide it by 2, turn it on, no interrupt
        TA1CTL = TASSEL__SMCLK + ID_1 + MC_1 + TACLR;

        P1OUT |= BIT0; //Turn on green LED on Launchpad
        for (i=0; i < 6; i++) //Play two-tone sequence 6 times
        {
            TA1CCR0 = 227; //First period at 2200 Hz; 1 count is 2 us at 500 kHz SMCLK
            TA1CCR1 = 114; //50% modulation
            TA0CCR0 = 2000; //200 ms duration of 1st tone using VLO clock; Start slow timer TA0
            LPM3; //Count VLO cycles in low-power mode
            //TA0 timeout. Change TA1 frequency to 1300 Hz
            TA1CCR0 = 385; //Second period
            TA1CCR1 = 192; //50% modulation
            TA0CCR0 = 2000; //200 ms duration of 2nd tone; Re-start VLO timer
            LPM3;
            //TA0 timeout. Resume loop
        }
        TA1CTL = MC_0 + TACLR + OUT; //Turn off timer TA1
        TA1CCTL1 = OUTMOD_0; //Change output mode to prevent leaving it in high state
        P1OUT &= ~BIT0; //Turn off LED
}

#pragma vector=TIMER0_A0_VECTOR //This vector name is in header file
 __interrupt void timerfoo (void) //The name of this interrupt (timerfoo) is arbitrary
{
    LPM3_EXIT;
}
