#include <avr/io.h>

void initUsb(int ubrr) {
	/*Set baud rate */
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char) ubrr;
	/* Enable receiver and transmitter   */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Frame format: 8data, No parity, 1stop bit */
	UCSR1C = (3<<UCSZ10);
}

void delayLong()
{
	unsigned int delayvar;
	delayvar = 0; 
	while (delayvar <=  65500U)		
	{
		asm("nop");  
		delayvar++;
	}
}

unsigned char serialCheckRxComplete(void)
{
	return( UCSR1A & _BV(RXC1)) ;		// nonzero if serial data is available to read.
}

unsigned char serialCheckTxReady(void)
{
	return( UCSR1A & _BV(UDRE1) ) ;		// nonzero if transmit register is ready to receive new data.
}

unsigned char serialRead(void)
{
	while (serialCheckRxComplete() == 0)		// While data is NOT available to read
	{;;} 
	return UDR1;
}

void serialWrite(unsigned char DataOut)
{
	while (serialCheckTxReady() == 0)		// while NOT ready to transmit 
	{;;} 
	UDR1 = DataOut;
}