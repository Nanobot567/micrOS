#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>
#include "fn.c"

void getHelp(void);

void getHelp(void) {
    zero();
    gfx_SetTextScale(2,2);
    PrintCentered("micrOS help",30);
    gfx_SetTextScale(1,1);
    PrintCentered("general info",60);
    PrintCentered("micrOS is a general-purpose shell",80);
    PrintCentered("written in C for the TI-84+CE.",90);
    PrintCentered("button actions",110);
    PrintCentered("Y= - main menu",130);
    PrintCentered("arrow up/down - navigate the shown list",140);
    PrintCentered("2nd - run program",150);
    PrintCentered("CLEAR - exit micrOS",160);
    waitForNext();
    PrintCentered("-- page 2 --",50);
    waitForNext();
}