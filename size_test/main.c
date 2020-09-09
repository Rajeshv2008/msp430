#include <msp430.h> 


/**
 * main.c
 */

typedef struct{

    int a;
    char b;


}TEST;

typedef struct{

    int a:2;
    char b:1;


}TEST1;
//# define ()

//unsigned int  *P1_PORT_ = (unsigned int *)0x21;


#define P1_PORT_ (*(unsigned char *)0x21)

int main(void)
{
	TEST t;
	TEST1 t1;
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    int c= sizeof(t);
    int d= sizeof(t1);
	int sint= sizeof(int);
	int schar= sizeof(char);
	P1DIR|=BIT0;
	int i=0;
	while(1){

	    P1_PORT_|=BIT0;
	    for ( i=0;i<20000;i++){


	    }
	    P1_PORT_&=0;
	    for ( i=0;i<20000;i++){

	    }

	}
    return 0;
}
