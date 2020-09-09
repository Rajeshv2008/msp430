#include <msp430.h> 


/**
 * main.c
 */

volatile int temp,fetched=0; // fetched flag to indicate adc value read
volatile int conv_value; // hold the deg C value
int conv_value_[5],str[5];
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	init_UART();
	init_ADC();

    __enable_interrupt();
	
    while(1){
        if (fetched==1){ // if adc is read proceed with computation
            conv_value=computeTemp(temp);
            // enable UTART TX after ensuring ADC value is read
            int_char(conv_value);
            UCA0CTL1&=~UCSWRST;
            UC0IE|=UCA0TXIFG;
            fetched=0;
        }

    }
	return 0;
}
void init_UART(){
    // Port1, pin 1 and 2 selected for UCA0Rx and Tx
    P1SEL|=BIT1+BIT2;
    P1SEL2|=BIT1+BIT2;

    UCA0CTL0|=UCPEN;
    UCA0CTL1|=UCSSEL_2+UCSWRST;
    UCA0BR0=0x6D; // BRCLK=1mhz, UCA0BR0=6d, UCA0BR0=0 for 9600 baud

}



void init_ADC(){
    ADC10CTL0|=SREF_1+ADC10SHT_3+ADC10IE+ADC10ON+REFON; // (Vref,Vss), 64adc clk sample and hold,IE
    ADC10CTL1|=INCH_10+ADC10DIV_3 ; // TEMP Sensor, div by 4,
    ADC10CTL0|=ENC+ADC10SC;
}


int  computeTemp(int raw_value){

    // equation for temp : temp_value =(raw_value*0.413)-277.75;
    // optizmize float computation by mul and div by 2^16 (div done by right shift)
    //temp_value =((raw_value*27069)-18202393+2^15)>>16; improve rounding by adding 2^15
   //int  temp_value =((raw_value*27069)-18202393+2^15)>>16;
    raw_value = ((raw_value * 27069L - 18169625L)>>16);;

  return raw_value;
}

#pragma vector = ADC10_VECTOR
__interrupt void adc_interrupt(){

    temp=ADC10MEM; // read ADC temperature value
    fetched=1; // ready to convert and tx

}

#pragma vector =USCIAB0TX_VECTOR
__interrupt void UCA0TX(){
    UCA0TXBUF=conv_value;
    UC0IE&=~UCA0TXIFG; // clear interrupt flag
}

void convToChar(int In_value){

    conv_value_[0]=In_value;
    //work in progress/

}



