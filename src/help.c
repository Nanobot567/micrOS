#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>
#include "fn.c"

void waitForNext(void);
void zero(void);

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

void zero(void) {
    gfx_ZeroScreen();
    gfx_SetColor(160);
    gfx_HorizLine(0,5,LCD_WIDTH);
    gfx_VertLine(5,0,LCD_HEIGHT);
    gfx_HorizLine(0,235,LCD_WIDTH);
    gfx_VertLine(315,0,LCD_HEIGHT);
    gfx_HorizLine(0,220,LCD_WIDTH);
    gfx_PrintStringXY("micrOS",16,224);
    gfx_VertLine(70,220,15);
    // print time using rtc_Time
}
void waitForNext(void) {
    delay(150);
    while (!os_GetCSC());
    zero();
}