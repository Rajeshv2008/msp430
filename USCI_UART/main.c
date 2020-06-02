#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    char msg[]= {'a','b','c'};

    int i,j;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Port1, pin 1 and 2 selected for UCA0Rx and Tx
    P1SEL|=BIT1+BIT2;
    P1SEL2|=BIT1+BIT2;


    UCA0CTL1|=UCSSEL_2+UCSWRST; // SMCLK as BRCLK, Put UCA0 in reset
    UCA0CTL0|=UCPEN; // Enable parity
    UCA0BR0=0x6D; // BRCLK=1mhz, UCA0BR0=6d, UCA0BR0=0 for 9600 baud
    UCA0CTL1&=~UCSWRST; // release for operation
    while(1){

        for (i=0;msg[i]!='\0';i++){
         UCA0TXBUF=msg[i];

         for (j=0;j<5000;j++){}
         if (i==2){

            UCA0TXBUF='\n';

         }

        }
    }


    return 0;
}
