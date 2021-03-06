#include <msp430.h>

int flip = 0;

int main(void)
{
    WDTCTL  = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1DIR = BIT2 | BIT1 | BIT0;
    P1OUT = 0;

    TA0CTL   = TASSEL_2 | MC_1 | ID_3;
    TA0CCTL0 = CCIE;
    TA0CCR0  = 62499;

    _BIS_SR(LPM0_bits | GIE);

    return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void blink (void)
{
    if (flip++) {
        P1OUT ^=  BIT0;
    } else {
        P1OUT ^= BIT1;
    }

    flip %= 2;
}

