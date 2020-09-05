#include <msp430.h> 


/**
 * main.c
 */

volatile int temp;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	 init_ADC();
    __enable_interrupt();
	
    while(1){
        int smpl[200];
        int i=0;
        for (i=0;i<200;i++){

            smpl[i]=computeTemp(temp);

        }



    }


	return 0;
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

    temp=ADC10MEM;

}
