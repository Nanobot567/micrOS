#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>
#include "help.c"

void PrintCentered(const char *str,int height);
void Border(int drawTaskbar, int drawTips);
uint8_t getKeyPress(void);
void fileList(void);

uint8_t numFiles = 0;
uint8_t numFilesShown = 0;
uint8_t selectedNum = 1;

/* Screen height: 240. Length: 320. When printing, the height goes from the top down.*/

int main(void)
{
    char * selectedName;
    uint8_t darkmode = 1;


    kb_SetMode(MODE_3_CONTINUOUS);
    gfx_Begin();
    gfx_ZeroScreen();
    Border(0,0);

    gfx_SetTextFGColor(160);
    gfx_SetTextScale(2,2);
    PrintCentered("micrOS",100);
    gfx_SetTextScale(1,1);
    PrintCentered("v1.0dev. press any key to continue.",125);

    while (!os_GetCSC());

    fileList();

    while (1==1) {
        if ((kb_IsDown(kb_KeyDown)) && (selectedNum < numFilesShown)) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",22,5+(selectedNum*15));
            selectedNum++;
            gfx_SetTextFGColor(160);
            gfx_PrintStringXY(">",22,5+(selectedNum*15));
            delay(80);
        } else if ((kb_IsDown(kb_KeyUp)) && ((selectedNum != numFilesShown))) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",22,5+(selectedNum*15));
            selectedNum--;
            gfx_SetTextFGColor(160);
            gfx_PrintStringXY(">",22,5+(selectedNum*15));
            delay(80);
        } else if ((kb_IsDown(kb_Yequ))) {
            gfx_ZeroScreen();
            Border(1,0);
            selectedNum = 1;
            gfx_SetTextScale(2,2);
            PrintCentered("micrOS",30);
            gfx_SetTextScale(1,1);
            PrintCentered("by nanobot567",50);
            PrintCentered("special thanks to...",80);
            PrintCentered("everyone in the CEMETECH community",95);
            PrintCentered("0x298,0x2a3,0x2aa,0x2a6,0x257,",125);
            PrintCentered("0x2ab,0x29f,0x2af,0x257,",140);
            PrintCentered("0x2a4,0x298,0x2ab,0x29c,",155);
            PrintCentered("0x2a6,0x257,0x2a3,0x2a6,0x2a3",170);
            
            gfx_PrintStringXY("1.0dev (do not distribute!)",16,204);
            delay(1000);
            while (!os_GetCSC());
            fileList();
        } else if ((kb_IsDown(kb_Enter))) {
            // nothing
        } else if ((kb_IsDown(kb_Clear))) {
            break;
        }
    }
    
    /* End graphics drawing */
    gfx_End();

    return 0;
}

void PrintCentered(const char *str,int height) {
    gfx_PrintStringXY(str,
                      (LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
                      height);
}

void Border(int drawTaskbar, int drawTips) {
    gfx_SetColor(160);
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
    if (drawTips == 1) {
        gfx_HorizLine(0,15,LCD_WIDTH);
        gfx_VertLine(40,5,10);
        gfx_VertLine(110,5,10);
        gfx_VertLine(170,5,10);
        gfx_PrintStringXY("name",61,6);
        gfx_PrintStringXY("size",127,6);
    }
    gfx_SetColor(0);
}

uint8_t getKeyPress(void) {
    static uint8_t last_key;
    uint8_t only_key = 0;
    kb_Scan();
    for (uint8_t key = 1, group = 7; group; --group) {
        for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
            if (kb_Data[group] & mask) {
                if (only_key) {
                    last_key = 0;
                    return 0;
                } else {
                    only_key = key;
                }
            }
        }
    }
    if (only_key == last_key) {
        return 0;
    }
    last_key = only_key;
    return only_key;
}

void fileList(void) {
    uint8_t size = 0;
    uint8_t slot;
    uint8_t fileY = 20;
    uint8_t type;
    char * fileName;
    void *searchPos = NULL;
    numFiles = 0;
    numFilesShown = 0;
    selectedNum = 1;


    gfx_ZeroScreen();
    Border(1,1);
    gfx_SetTextFGColor(160);
    gfx_SetTextXY(10,10);

    while (((fileName = ti_DetectAny(&searchPos, NULL, &type)) != NULL) && (numFilesShown<12)) {
        if (type == TI_PRGM_TYPE || type == TI_PPRGM_TYPE) {
            slot = ti_Open(fileName,"r");
            size = ti_GetSize(slot);

            gfx_PrintStringXY(fileName,42,fileY);
            gfx_SetTextXY(121,fileY);
            gfx_PrintInt(size,5);

            ti_Close(slot);

            numFiles++;
            numFilesShown++;
            fileY += 15;
        }
    }

    gfx_PrintStringXY(">",22,20);
}