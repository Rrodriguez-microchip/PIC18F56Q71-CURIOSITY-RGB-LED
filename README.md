# PIC18F56Q71-CURIOSITY-RGB-LED
PIC18F56Q71 Curiosity using 3 PWM's to work an RGB LED

An RGB LED control project for PIC18F-Q71 Curiosity Board with Melody (MCC).

##Objective:
This repository contains an example of Melody generated code for 3PWM control of an RGB LED 
The PIC18F56Q71 features four 16-bit PWM generators. In this demo, the PWM1, PWM2 and PWM3 peripherals in conjunction with TMR2 are used to produce PWM signals featuring a color game on an RGB LED. Three GPIO pins are used as outputs: RB0, RB3 and RC0.

##Related Documentation
- [PIC18F56Q71 Curiosity Nano Evaluation Kit]([url](https://www.microchip.com/en-us/development-tool/ev01g21a))
- [PIC18F56Q71 Product Page]([url](https://www.microchip.com/en-us/product/PIC18F56Q71))
- [PIC18F56Q71 Data Sheet]([url](https://www.microchip.com/en-us/product/PIC18F56Q71#Documentation))
- [Microchip PIC & AVR Examples]([url](https://github.com/microchip-pic-avr-examples))

## Features

- **RGB LED Control**: Full control of RGB LEDs using 3 PWM modules
- **Color Effects**: Multiple pre-programmed lighting effects including:
  - Basic color cycling (Red → Green → Blue → White, etc.)
  - Smooth rainbow transitions
  - Breathing effect (fade in/out)
  - Custom color mixing
- **16-bit PWM Resolution**: High-resolution PWM control for smooth color transitions
- **Modular Design**: Easy-to-use functions for custom color effects

## Hardware Requirements

-  The [PIC18F56Q71 Curiosity Nano]([url](https://www.microchip.com/en-us/development-tool/EV01G21A)) development board is used as a test platform:
<img width="800" height="190" alt="image" src="https://github.com/user-attachments/assets/21f27230-9f98-49d4-bd67-c67313d5733d" />
  
- **RGB LED**: Common cathode or common anode RGB LED
- **Current Limiting Resistors**: Appropriate resistors for each color channel
- **Development Board**: Any PIC18F-Q71 development board

## Hardware Connections

| PWM Module | Color Channel | Recommended Pin |
|------------|---------------|-----------------|
| PWM1       | Blue          | Configured via MCC |
| PWM2       | Green         | Configured via MCC |
| PWM3       | Red           | Configured via MCC |
<img width="1348" height="802" alt="image" src="https://github.com/user-attachments/assets/6c2e234f-6ca9-4a3d-b94c-93f280adb262" />

> **Note**: Pin assignments are configured through MPLAB Code Configurator (MCC). Refer to your specific board's datasheet for available PWM pins.
<img width="1352" height="460" alt="image" src="https://github.com/user-attachments/assets/5c3254f4-2f13-40ac-899c-fd594245aa99" />

## Software Requirements

- **MPLAB X IDE** (v6.20 or later)
- **XC8 Compiler**
- **MPLAB Code Configurator (MCC)** / Melody

## MCC Configuration

The project requires the following modules to be configured in MCC:

* Clock Control:

  *Clock Source: HFINTOSC
  *HF Internal Clock: 64 MHz
  *Clock Divider: 1
<img width="539" height="527" alt="image" src="https://github.com/user-attachments/assets/61fd327f-3a32-43c3-8581-b82dca1869af" />


* Configuration bits:
    * WDT operating mode: WDT disabled
  <img width="638" height="680" alt="image" src="https://github.com/user-attachments/assets/f90d4dc1-647d-4a40-83e4-f8ece7e367b0" />

* Interrupt Manager
<img width="561" height="831" alt="image" src="https://github.com/user-attachments/assets/aa7eb8fa-45ce-4443-980f-a7c0ea2b44f3" />

### PWM Configuration:

* PWMx_16bits
    * all three PWM's will be having the same configuration
    * Hardware Settings 
      * Enable PWM: Yes
      * Clock Source: FOSC
      * Clock Prescaler: No prescale
    * Slice 1 Output Settings
      * Mode: Left-aligned mode
      * Requested Frequency: 1 kHz
      * Output1 Duty Cycle: 50%
      * Invert Output1 Polarity: No
      * Period Interrupt Enable: No
    * Interrupt Settings
      * Interrupt Enable : No
      * Period Interrupt Postscaler: No postscale
      <img width="547" height="439" alt="image" src="https://github.com/user-attachments/assets/89e3abc8-2f6c-425e-b727-b14441d42ba3" />
      <img width="544" height="667" alt="image" src="https://github.com/user-attachments/assets/1b33be8c-985b-4e62-a94a-cad79154e88f" />



## Key Functions

### Core Functions
- `setRGB(red, green, blue)` - Set RGB color values (0-64511)
- `rgbTest()` - Cycle through basic colors
- `colorCycle()` - Smooth color transitions
- `breathingEffect()` - Fade in/out white light
- `rainbowCycle()` - Continuous rainbow effect

### Color Definitions
```c
#define PWM_MAX 64511
#define RED_COLOR       PWM_MAX, PWM_OFF, PWM_OFF
#define GREEN_COLOR     PWM_OFF, PWM_MAX, PWM_OFF
#define BLUE_COLOR      PWM_OFF, PWM_OFF, PWM_MAX
#define WHITE_COLOR     PWM_MAX, PWM_MAX, PWM_MAX
```

## Usage

### Basic Color Control
```c
// Set pure red
setRGB(PWM_MAX, 0, 0);

// Set purple (red + blue)
setRGB(PWM_MAX, 0, PWM_MAX);

// Set dim white (50% brightness)
setRGB(PWM_MAX/2, PWM_MAX/2, PWM_MAX/2);
```

### Running Effects
```c
while(1)
{
    rgbTest();          // Test all basic colors
    colorCycle();       // Smooth rainbow
    breathingEffect();  // Breathing white
}
```

## Timing Notes

The project uses `_delay()` function where:
- `_delay(100)` ≈ 3ms
- Adjust delay values based on desired effect speed
- Larger step sizes in loops = faster transitions
- Smaller step sizes = smoother transitions

## Customization

### Adjusting Speed
Modify the `step` variable in color functions:
```c
uint16_t step = 2048;  // Fast transitions
uint16_t step = 512;   // Smooth transitions
```

### Creating Custom Colors
```c
void customEffect(void)
{
    setRGB(PWM_MAX/4, PWM_MAX/2, PWM_MAX);  // Custom purple-blue
    _delay(50000);
}
```

## Troubleshooting

### Common Issues:

1. **LED stays at 50% brightness**(default Duty Cycle of PWM's)
   - Check that you're using duty cycle functions, not period functions
   - Use `PWMx_16BIT_SetSlice1Output1DutyCycleRegister()` 
   - Call `PWMx_16BIT_LoadBufferRegisters()` after setting values

2. **Colors don't change**
   - Verify PWM modules are enabled: `PWMx_16BIT_Enable()` , ( enabled by default) 
   - Check pin assignments in MCC
   -Delays too fast: Use larger delays (minimum _delay(50) for visible changes)
   - PWM_MAX overflow: Ensure loop increments don't exceed PWM_MAX to avoid infinite loops
   -Loop variable underflow: Use i >= step instead of i > 0 in decrementing loops

3. **Transitions too fast/slow**
   - Adjust `step` size in loop increments
   - Modify `_delay()` values
   - Consider your timing: `_delay(100)` ≈ 3ms


## License

This project is open source. Feel free to use and modify for your projects.

## Author

Created for PIC18F-Q71 RGB LED control applications.

---
