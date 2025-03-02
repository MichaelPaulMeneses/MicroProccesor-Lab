#include <xc.h>
#include "LABORATORY 1.h"

#define _XTAL_FREQ 8000000

void main(void) {
    
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    //TRISDbits.TRISD3 = 0;
    
    while(1) {
        LATDbits.LATD0 = 1;
        __delay_ms(100);
        LATDbits.LATD0 = 0;
        __delay_ms(100);
        
        LATDbits.LATD1 = 1;
        __delay_ms(100);
        LATDbits.LATD1 = 0;
        __delay_ms(100);
        
        LATDbits.LATD2 = 1;
        __delay_ms(100);
        LATDbits.LATD2 = 0;
        __delay_ms(100);
       
        //LATDbits.LATD3 = 1;
        //__delay_ms(1000);
        //LATDbits.LATD3 = 0;
        //__delay_ms(1000);
    }
    
    
    return;
}
