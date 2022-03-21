#include <avr/io.h>

#define LEDS_LED1        (1 << 4)
#define LEDS_LED2        (1 << 0)
#define LEDS_LED3        (1 << 1)
#define LEDS_LED4        (1 << 2)
#define LEDS_LED5        (1 << 3)

/** LED mask for all the LEDs on the board. */
#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4 \
						| LEDS_LED5)

/** LED mask for none of the board LEDs. */
#define LEDS_NO_LEDS     0

static inline void LEDs_Init(void)
{
	DDRD  |=  LEDS_ALL_LEDS;
	PORTD &= ~LEDS_ALL_LEDS;
}

static inline void LEDs_Disable(void)
{
	DDRD  &= ~LEDS_ALL_LEDS;
	PORTD &= ~LEDS_ALL_LEDS;
}

static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
{
	PORTD |= LEDMask;
}

static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
{
	PORTD &= ~LEDMask;
}

static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
{
	PORTD = ((PORTD & ~LEDS_ALL_LEDS) | LEDMask);
}

static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
									const uint8_t ActiveMask)
{
	PORTD = ((PORTD & ~LEDMask) | ActiveMask);
}

static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
{
	PIND  = LEDMask;
}

static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
static inline uint8_t LEDs_GetLEDs(void)
{
	return (PORTD & LEDS_ALL_LEDS);
}