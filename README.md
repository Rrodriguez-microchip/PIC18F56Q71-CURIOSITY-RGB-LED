# PIC18F56Q71-CURIOSITY-RGB-LED
PIC18F56Q71 Curiosity using 3 PWM's to work an RGB LED

An RGB LED control project for PIC18F-Q71 Curiosity Board with Melody (MCC).

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

- **Microcontroller**: PIC18F-Q71 family
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

- **MPLAB X IDE** (v6.0 or later)
- **XC8 Compiler**
- **MPLAB Code Configurator (MCC)** / Melody

## MCC Configuration

The project requires the following modules to be configured in MCC:

### Required Modules:
1. **System Clock**: Configure for your desired frequency
2. **Pin Manager**: Assign PWM outputs to appropriate pins
3. **PWM1_16BIT**: Configure for RGB Blue channel
4. **PWM2_16BIT**: Configure for RGB Green channel  
5. **PWM3_16BIT**: Configure for RGB Red channel
6. **TMR2**: Timer for PWM time base
7. **Interrupt Manager**: Enable global interrupts

### PWM Configuration:
- **Resolution**: 16-bit
- **Frequency**: 1-20 kHz (recommended for LED control)
- **Mode**: Left-aligned
- **Period**: 0xF9FF (64511) for smooth transitions

## Project Structure

```
├── main.c                     # Main application file
├── mcc_generated_files/       # Auto-generated MCC files
│   ├── system/
│   ├── pwm/
│   └── ...
└── README.md                  # This file
```

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

1. **LED stays at 50% brightness**
   - Check that you're using duty cycle functions, not period functions
   - Use `PWMx_16BIT_SetSlice1Output1DutyCycleRegister()` 
   - Call `PWMx_16BIT_LoadBufferRegisters()` after setting values

2. **Colors don't change**
   - Verify PWM modules are enabled: `PWMx_16BIT_Enable()`
   - Check pin assignments in MCC
   - Verify current limiting resistors

3. **Transitions too fast/slow**
   - Adjust `step` size in loop increments
   - Modify `_delay()` values
   - Consider your timing: `_delay(100)` ≈ 3ms

## Contributing

Feel free to submit issues and enhancement requests!

## License

This project is open source. Feel free to use and modify for your projects.

## Author

Created for PIC18F-Q71 RGB LED control applications.

---
