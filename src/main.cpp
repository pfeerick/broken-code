#include <Arduino.h>
#include "Nextion.h"

NexButton b0 = NexButton(0, 1, "b0");

char buffer[100] = {0};

NexTouch *nex_listen_list[] = 
{
    &b0,
    NULL
};

void b0PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    NexButton *btn = (NexButton *)ptr;
    dbSerialPrintln("b0PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr); 
    memset(buffer, 0, sizeof(buffer));
    btn->getText(buffer, sizeof(buffer));
    
    number = atoi(buffer);
    number += 1;

    memset(buffer, 0, sizeof(buffer));
    itoa(number, buffer, 10);
    
    btn->setText(buffer);
}

void setup(void)
{    
    nexInit();
    b0.attachPop(b0PopCallback, &b0);
    dbSerialPrintln("setup done"); 
}

void loop(void)
{   
    nexLoop(nex_listen_list);
}