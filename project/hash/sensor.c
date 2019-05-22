#include <stdio.h>
#include "contiki-conf.h"
#include "net/netstack.h"
#include "net/rime/rime.h"
#include "net/mac/tsch/tsch.h"

const linkaddr_t sink_addr =    { { 1, 0 } };

/*---------------------------------------------------------------------------*/
PROCESS(hash_sensor_process, "Hash Sensor Node");
AUTOSTART_PROCESSES(&hash_sensor_process);
/*---------------------------------------------------------------------------*/
static struct abc_conn abc;
static linkaddr_t command_sender;

static void
recv(struct abc_conn *conn)
{
	linkaddr_copy(&command_sender, packetbuf_addr(PACKETBUF_ADDR_SENDER));
	printf("msg from %d.%d: '%s'\n",
					command_sender.u8[0], command_sender.u8[1],
					(char *)packetbuf_dataptr());

	process_post(&hash_sensor_process, PROCESS_EVENT_CONTINUE, NULL);
}

static void
sent(struct abc_conn *conn, int status, int num_tx){

}

static const struct abc_callbacks abc_callback = {recv, sent};
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hash_sensor_process, ev, data)
{

	PROCESS_EXITHANDLER(abc_close(&abc))
	PROCESS_BEGIN();

	abc_open(&abc, 123, &abc_callback);

	while (1) {
		PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_CONTINUE);
		packetbuf_set_addr(PACKETBUF_ADDR_RECEIVER, &command_sender);
		packetbuf_set_addr(PACKETBUF_ADDR_SENDER, &linkaddr_node_addr);
		packetbuf_copyfrom("sensor data", 11);
		abc_send(&abc);
	}

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
