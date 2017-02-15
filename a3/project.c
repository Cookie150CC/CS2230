#include <msp430.h>
int counter=1;
int main(void)
{
    WDTCTL  = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;


    P1OUT = 0;
    P1DIR = 7; //Blue | Red | Green respectively
    P1REN = 8; //enable pull-up resistor
    P1OUT |= 8; //Select a pull up resistor
    P1IE  |= 8; //Enable an interrupt
    P1IES |= 8; //Select high transition
    P1IFG &= ~8; //Clear interrupt flag

    P2DIR = 7;
    P2OUT = 0;

    TA0CTL   = TASSEL_2 | MC_1 | ID_3;
    TA0CCTL0 = CCIE;
    TA0CCR0  = 35000;

    TA1CTL   = TASSEL_2 | MC_1 | ID_3;
    TA1CCTL1 = OUTMOD_4;
    TA1CCR0  = 20000;

    __eint();
     for(;;){
       __delay_cycles(499999);
       if(counter==1){
        P1OUT ^= BIT1;
      }else if(counter==2){
        P1OUT ^= BIT1;
      }else if(counter==3){
        P1OUT &= ~BIT1;
        P2SEL ^= BIT1;
      }else if(counter==4){
        TA1CCR0 = 40000;
        P2SEL ^= BIT1;
      }else if(counter==5) {
        P1OUT &= ~7;
        P2OUT &= ~BIT0;
        counter=1;
      }

      }

   //Used in int.c probably useful here later
    // TA0CTL   = TASSEL_2 | MC_1 | ID_3;
    // TA0CCTL0 = CCIE;
    // TA0CCR0  = 62499;
    //
    return 0;

}

#pragma vector=PORT1_VECTOR
__interrupt void Mode(void)
{

    while (!(BIT3 & P1IN)) {}
    // is finger off of button yet?
    counter++;
    P1IFG &= ~8; //Clear interrupt flag

}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void blink (void)
{
    if(counter==2 || counter ==3){
      P1OUT ^=BIT0;
    }
    if(counter==4){
      P1OUT &= ~BIT0;
    }
}
