#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>

void Border(int drawTaskbar, int drawMoreInfo);
void microCredits(void);
void PrintCentered(const char *str,int height);
void waitForNext(void);
void zero(void);

void microCredits(void) {
    gfx_ZeroScreen();
    Border(1,0);
    gfx_SetTextScale(2,2);
    PrintCentered("micrOS",30);
    gfx_SetTextScale(1,1);
    PrintCentered("by nanobot567",50);
    PrintCentered("special thanks to...",80);
    PrintCentered("everyone in the CEMETECH community",95);
    PrintCentered("0x390,0x38d,0x39a,0x38d,0x348,0x38b,",125);
    PrintCentered("0x397,0x395,0x38d,0x348,0x38c,0x389,",135);
    PrintCentered("0x39c,0x348,0x38a,0x397,0x391,0x354,",145);
    PrintCentered("0x348,0x397,0x348,0x38b,0x39a,0x389,",155);
    PrintCentered("0x398,0x348,0x39f,0x389,0x38c,0x38c,",165);
    PrintCentered("0x39d,0x398",175);
    
    gfx_PrintStringXY("1.1.1dev (do not distribute!)",16,204);
    delay(800);
    while (!os_GetCSC());
}

void Border(int drawTaskbar, int drawMoreInfo) {
    gfx_SetColor(224);
    gfx_HorizLine(0,5,LCD_WIDTH);
    gfx_VertLine(5,0,LCD_HEIGHT);
    gfx_HorizLine(0,235,LCD_WIDTH);
    gfx_VertLine(315,0,LCD_HEIGHT);
    if (drawTaskbar == 1) {
        gfx_HorizLine(0,220,LCD_WIDTH);
        gfx_PrintStringXY("micrOS",16,224);
        gfx_VertLine(70,220,15);
        // print time using rtc_Time
    }
    if (drawMoreInfo == 1) {
        gfx_HorizLine(0,15,LCD_WIDTH);
        gfx_VertLine(38,5,10);
        gfx_VertLine(108,5,10);
        gfx_VertLine(LCD_WIDTH/2,5,230);
        gfx_PrintStringXY("name",59,7);
        gfx_PrintStringXY("size",120,7);
        gfx_PrintStringXY("more info",207,7);
        gfx_PrintStringXY("(null)",222,80);
    }
    gfx_SetColor(0);
}

void PrintCentered(const char *str,int height) {
    gfx_PrintStringXY(str,
                      (LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
                      height);
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