#include "RGB_LED.h"

/**
 * Smooth color cycling effect
 */
void colorCycle(void)
{
    uint16_t i;
    uint16_t step = 48;  // Large step for reasonable speed
    
    // Red to Yellow (increase green)
    for(i = 0; i <= (PWM_MAX-step); i += step)
    {
        setRGB(PWM_MAX/2, i, PWM_OFF);
        _delay(10000);  // ~3ms delay
    }
    
    // Yellow to Green (decrease red)
    for(i = PWM_MAX; i >= step; i -= step)
    {
        setRGB(i, PWM_MAX, PWM_OFF);
        _delay(10000);
    }
    setRGB(PWM_OFF, PWM_MAX, PWM_OFF);  // Ensure pure green
    _delay(10000);
    
    // Green to Cyan (increase blue)
    for(i = 0; i <= (PWM_MAX-step); i += step)
    {
        setRGB(PWM_OFF, PWM_MAX, i);
        _delay(10000);
    }
    
    // Cyan to Blue (decrease green)
    for(i = PWM_MAX; i >= step; i -= step)
    {
        setRGB(PWM_OFF, i, PWM_MAX);
        _delay(10000);
    }
    setRGB(PWM_OFF, PWM_OFF, PWM_MAX);  // Ensure pure blue
    _delay(10000);
    
    // Blue to Magenta (increase red)
    for(i = 0; i <= (PWM_MAX-step); i += step)
    {
        setRGB(i, PWM_OFF, PWM_MAX);
        _delay(10000);
    }
    
    // Magenta to Red (decrease blue)
    for(i = PWM_MAX; i >= step; i -= step)
    {
        setRGB(PWM_MAX, PWM_OFF, i);
        _delay(10000);
    }
    setRGB(PWM_MAX, PWM_OFF, PWM_OFF);  // Ensure pure red
    _delay(10000);
    setRGB(PWM_OFF, PWM_OFF, PWM_OFF);  // Ensure pure red
    
}

/**
 * Breathing white light effect
 */
void breathingEffect(void)
{
    uint16_t i;
    uint8_t cycles = 3;    
    uint16_t step = 48;  // Large step for reasonable speed
    
    while(cycles--)
    {
        // Fade in
        for(i = 0; i <= (PWM_MAX- step); i += step)
        {
            setRGB(i, i, i);
            _delay(5000);
        }
        
        // Fade out
        for(i = PWM_MAX; i > (1+step); i -= step)
        {
            setRGB(i, i, i);
            _delay(5000);
        }
        
        setRGB(OFF_COLOR);
        _delay(5000);
    }
}

/**
 * Rainbow cycling effect
 */
void rainbowCycle(void){
    uint16_t j;
    uint16_t r, g, b;
    
    for(j = 0; j < 256; j++)
    {
        // Simple rainbow algorithm - fixed
        if(j < 85) 
        {
            // Red to Yellow: Red stays high, Green increases
            r = PWM_MAX;
            g = (j * PWM_MAX) / 85;    // Green increases from 0 to MAX
            b = 0;                     // Blue stays off
        }
        else if(j < 170) 
        {
            // Yellow to Cyan: Red decreases, Green stays high, Blue increases
            uint16_t phase = j - 85;   // 0 to 84
            r = ((85 - phase) * PWM_MAX) / 85;  // Red decreases from MAX to 0
            g = PWM_MAX;                        // Green stays high
            b = (phase * PWM_MAX) / 85;         // Blue increases from 0 to MAX
        }
        else 
        {
            // Cyan to Magenta: Green decreases, Blue stays high, Red increases
            uint16_t phase = j - 170;  // 0 to 85
            r = (phase * PWM_MAX) / 85;         // Red increases from 0 to MAX
            g = ((85 - phase) * PWM_MAX) / 85;  // Green decreases from MAX to 0
            b = PWM_MAX;                        // Blue stays high
        }
        
        setRGB(r, g, b);
        _delay(10000);  // About 70ms delay
    }
}


/**
 * Basic RGB test - cycles through primary colors
 */
void rgbTest1 (void){
    // Test Red at different brightness levels
        setRGB(16000,  0, 0);          //Red 25%,Green OFF,Blue OFF
        _delay(5000000);
        
        setRGB(32000,  0, 0);          //Red 50%,Green OFF,Blue OFF
        _delay(5000000);
        
        setRGB(64511,  0, 0);          //Red 100%,Green OFF,Blue OFF
        _delay(5000000);
        
        // Test Green at different brightness levels
        setRGB(0,16000, 0);          //Red OFF,Green 25%,Blue OFF
        _delay(5000000);
        
        setRGB(0,32000, 0);          //Red OFF,Green 50%,Blue OFF
        _delay(5000000);
        
        setRGB(0,64511, 0);          //Red OFF,Green 100%,Blue OFF
        _delay(5000000);
        
        // All OFF
        setRGB(0,0, 0);          //Red OFF,Green OFF,Blue OFF
        _delay(5000000);
        
         // Test Red at different brightness levels
        setRGB(0,0, 16000);          //Red OFF,Green OFF,Blue 25%
        _delay(5000000);
        
        setRGB(0,0, 32000);          //Red OFF,Green OFF,Blue 50%
        _delay(5000000);
        
        setRGB(0,0, 64511);          //Red OFF,Green OFF,Blue 100%
        _delay(5000000);
}
void rgbTest(void)
{
    // Turn off
    setRGB(OFF_COLOR);
    _delay(5000000);
   
    // Red
    setRGB(RED_COLOR);
    _delay(10000000);
    
    // Green  
    setRGB(GREEN_COLOR);
    _delay(10000000);
    
    // Blue
    setRGB(BLUE_COLOR);
    _delay(10000000);
    
    // White
    setRGB(WHITE_COLOR);
    _delay(10000000);
    
    // Yellow
    setRGB(YELLOW_COLOR);
    _delay(10000000);
    
    // Cyan
    setRGB(CYAN_COLOR);
    _delay(10000000);
    
    // Magenta
    setRGB(MAGENTA_COLOR);
    _delay(10000000);
    
    // Off
    setRGB(OFF_COLOR);
    _delay(5000000);
}
