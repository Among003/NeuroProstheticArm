
void initUSARTwithParity(unsigned char usartNum)
{
	if (usartNum != 1) {
		// Turn on the reception circuitry of USART0
		// Turn on receiver and transmitter
		// Use 8-bit character sizes 
		UCSR0B |= (1 << RXEN0)  | (1 << TXEN0);
		UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
		// Load lower 8-bits of the baud rate value into the low byte of the UBRR0 register
		UBRR0L = BAUD_PRESCALE;
		// Load upper 8-bits of the baud rate value into the high byte of the UBRR0 register
		UBRR0H = (BAUD_PRESCALE >> 8);
	}
	else {
		// Turn on the reception circuitry for USART1
		// Turn on receiver and transmitter
		// Use 8-bit character sizes
		UCSR1B |= (1 << RXEN1)  | (1 << TXEN1);
		UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);
		// Load lower 8-bits of the baud rate value into the low byte of the UBRR1 register
		UBRR1L = BAUD_PRESCALE;
		// Load upper 8-bits of the baud rate value into the high byte of the UBRR1 register
		UBRR1H = (BAUD_PRESCALE >> 8);
	}
}
