#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(example_abc_process, "ABC example");
AUTOSTART_PROCESSES(&example_abc_process);
/*---------------------------------------------------------------------------*/
//static void
//abc_recv(struct abc_conn *c)
//{
//  printf("abc message received '%s'\n", (char *)packetbuf_dataptr());
//}
//static const struct abc_callbacks abc_call = {abc_recv};
//static struct abc_conn abc;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_abc_process, ev, data)
{
	PROCESS_BEGIN();

				printf("Hello, world\n");

	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
