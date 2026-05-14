
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define PWM_PIN     PB0     // OC0A
#define BUTTON_PIN  PB2

#define BCD_A       PB1
#define BCD_B       PB3
#define BCD_C       PB4

uint8_t stepValue = 0;

const uint8_t pwmSteps[6] = {
	0,    // 0%
	51,   // 20%
	102,  // 40%
	153,  // 60%
	204,  // 80%
	255   // 100%
};

void setup_fast_pwm(void)
{
	DDRB |= (1 << PWM_PIN);

	// Fast PWM, non-inverting mode on OC0A / PB0
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);

	// Prescaler = 64
	TCCR0B = (1 << CS01) | (1 << CS00);

	OCR0A = 0;
}

void display_number(uint8_t number)
{
	// clear BCD pins
	PORTB &= ~((1 << BCD_A) | (1 << BCD_B) | (1 << BCD_C));

	if (number & 0x01)
	PORTB |= (1 << BCD_A);

	if (number & 0x02)
	PORTB |= (1 << BCD_B);

	if (number & 0x04)
	PORTB |= (1 << BCD_C);
}

int main(void)
{
	setup_fast_pwm();

	// Button input with pull-up
	DDRB &= ~(1 << BUTTON_PIN);
	PORTB |= (1 << BUTTON_PIN);

	// BCD output pins
	DDRB |= (1 << BCD_A) | (1 << BCD_B) | (1 << BCD_C);

	display_number(stepValue);

	uint8_t lastButton = 1;

	while (1)
	{
		uint8_t buttonNow = (PINB & (1 << BUTTON_PIN)) ? 1 : 0;

		if (lastButton == 1 && buttonNow == 0)
		{
			_delay_ms(50);

			if (!(PINB & (1 << BUTTON_PIN)))
			{
				stepValue++;

				if (stepValue > 5)
				{
					stepValue = 0;
				}

				OCR0A = pwmSteps[stepValue];
				display_number(stepValue);

				while (!(PINB & (1 << BUTTON_PIN)));
				_delay_ms(50);
			}
		}

		lastButton = buttonNow;
	}
}