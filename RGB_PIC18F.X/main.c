 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "RGB_LED.h"
/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 


    while(1)
    {
//        colorCycle();       
//        breathingEffect();
//        rainbowCycle();
        setRGB(PWM_MAX,0,0);
        _delay(1000);
        setRGB(0,PWM_MAX,0);
    }    
}

void Load_bufferRegisters(void){
    
    PWM1_16BIT_LoadBufferRegisters();
    PWM2_16BIT_LoadBufferRegisters();
    PWM3_16BIT_LoadBufferRegisters();
        
}
void setRGB(uint16_t red, uint16_t green, uint16_t blue)
{
    // Assuming PWM1 = Blue, PWM2 = Green, PWM3 = Red
    PWM3_16BIT_SetSlice1Output1DutyCycleRegister(red);       // Red 
    PWM2_16BIT_SetSlice1Output1DutyCycleRegister(green);      // Green 
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(blue);      // Blue   
    Load_bufferRegisters();
    
}
