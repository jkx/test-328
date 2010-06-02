#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/sleep.h>

#include "rfm12.h"
#include "uart.h"


int main ( void )
{
  uint8_t *bufcontents;
  uint8_t i;
  uint8_t tv[] = "foobar1";
  uint16_t ticker = 0;
	
	
  uart_init();

  _delay_ms(250);
  _delay_ms(250);
  _delay_ms(250);
  rfm12_init();
  _delay_ms(250);
  //rfm12_set_wakeup_timer(100);	

  sei();

  uart_putstr ("AVR Boot Ok\r\n");
  _delay_ms(250);

  while (1)
    {
      ticker++;
      if (rfm12_rx_status() == STATUS_COMPLETE)
	{
	  uart_putstr ("new packet:[");
	  bufcontents = rfm12_rx_buffer();

	  // dump buffer contents to uart			
	  for (i=0;i<rfm12_rx_len();i++)
	    {
	      uart_putc ( bufcontents[i] );
	    }
	  uart_putstr ("]\r\n");
	  rfm12_rx_clear();
	}

      
      _delay_ms(10);

      rfm12_tick();
      // send data
      if (ticker == 20) 
	{ 
	  ticker = 0;
	  rfm12_tx (sizeof(tv), 0, tv);
	}
    }


}
