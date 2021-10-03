#include "contiki.h"
//#include "dev/leds.h"

#include <stdio.h>

PROCESS(hello_world_process, "Hello World Process");
AUTOSTART_PROCESSES(&hello_world_process); //para indicar cuantos procesos

PROCESS_THREAD(hello_world_process, ev, data)
{ 
    PROCESS_BEGIN();

    printf("Hello, World!\n");
    //leds_on(LEDS_ALL);

    PROCESS_END();
} 