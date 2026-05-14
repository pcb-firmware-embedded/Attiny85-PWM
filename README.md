PWM with ATtiny85

In this project, I use the ATtiny85 to control a PWM signal using a simple push button. 
Each time I press the button, the PWM level increases by one step, and this value is displayed on a 7-segment display.
For development, I used Atmel Studio, for simulation I used Proteus, and the ATtiny85 datasheet helped me correctly configure the pins, timers, and registers.
The PWM works in Fast PWM mode, where the timer counts from 0 to 255, compares the value with OCR0A, and generates a square wave signal. 
So, the higher the OCR0A value, the wider the pulse, which means more power delivered to a load like an LED or a motor.



https://www.youtube.com/watch?v=TKDO9VkM164

https://www.youtube.com/watch?v=KlZwSnbA6XY
