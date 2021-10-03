#include "contiki.h"    //libreria necesaria de contiki
#include "net/netstack.h"   //libreria para cualquier nodo que requiera comunicacion, tiene primitivas para poder ewnviar informacion al medio fisico (radio)
#include "net/nullnet/nullnet.h" //herramiento dentro de contiki, es una red que no tiene una pila de protocolos, al activarla en contiki solo va aufncionar el radio solo sin ningun protocolo (ip, udp, coap), utilizar el radio directamente y crear nuevos protocolos

#include <string.h>  //libreria de C, para utilizar una funcion (memcpy)que copie lo que existe en una variable para otra direccion

#include "sys/log.h" // bitacoras dentro de contiki
#define LOG_MODULE "Broadcast Sending App" //nombre del modulo
#define LOG_LEVEL LOG_LEVEL_INFO  //nivel para obtener informaciòn que estamos depurando

#define SEND_INTERVAL (8 * CLOCK_SECOND)

PROCESS(broadcast_sender, "Broadcast Sender Example");
AUTOSTART_PROCESSES(&broadcast_sender);

PROCESS_THREAD(broadcast_sender, ev, data)
{
    static struct etimer periodic_timer;
    static unsigned counter =0;

    PROCESS_BEGIN();

    nullnet_buf = (uint8_t *) &counter;
    nullnet_len = sizeof (counter);

    etimer_set(&periodic_timer, SEND_INTERVAL);
    while(1){
        PROCESS_WAIT_UNTIL(etimer_expired(&periodic_timer));

        LOG_INFO("Sending %u\n",counter);
        memcpy(nullnet_buf, &counter, sizeof(counter));
        nullnet_len = sizeof(counter);

        NETSTACK_NETWORK.output(NULL);
        counter ++;
        etimer_reset(&periodic_timer);

    }
    PROCESS_END();
}
