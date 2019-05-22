#include <stdio.h>
#include "contiki-conf.h"
#include "net/netstack.h"
#include "net/rime/rime.h"
#include "net/mac/tsch/tsch.h"
#include "net/linkaddr.h"

/*---------------------------------------------------------------------------*/
PROCESS(hash_sink_process, "Hash Sink Node");
AUTOSTART_PROCESSES(&hash_sink_process);
/*---------------------------------------------------------------------------*/
static void
recv(struct abc_conn *conn)
{
	linkaddr_t sender;

	linkaddr_copy(&sender, packetbuf_addr(PACKETBUF_ADDR_SENDER));
	printf("msg from %d.%d: '%s'\n", sender.u8[0], sender.u8[1],
					(char *)packetbuf_dataptr());
}
static void
sent(struct abc_conn *conn, int status, int num_tx){

}
static const struct abc_callbacks abc_callback = {recv, sent};
static struct abc_conn abc;

static linkaddr_t linkaddr = {{100, 0}};
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hash_sink_process, ev, data)
{

	PROCESS_EXITHANDLER(abc_close(&abc))
	PROCESS_BEGIN();

	linkaddr_set_node_addr(&linkaddr);
	abc_open(&abc, 123, &abc_callback);

	while(1) {
		static struct etimer et;
		etimer_set(&et, CLOCK_SECOND);
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

		// prepare and send command packet
		packetbuf_copyfrom("cmd", 3);
		packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &linkaddr_node_addr);
		abc_send(&abc);
	}
	
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
