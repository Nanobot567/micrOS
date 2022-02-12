#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>

uint8_t numFiles = 0;
uint8_t numFilesShown = 0;
uint8_t slot;
uint8_t numFile = 0;
uint8_t fileY = 20;
char * fileName;
int size = 0;
uint8_t selectedNum = 1; // number of currently selected file
char * selectedName; // pointer to name of selected file
bool key;
bool lastkey;
bool keytwo;
uint8_t darkmode = 1;
uint8_t cycle;

void PrintCentered(const char *str,int height);
void Border(int draw_taskbar);
uint8_t getKeyPress(void);
void files();




/* Screen height: 240. Length: 320. When printing, the height goes from the top down.*/

int main(void)
{
    kb_SetMode(MODE_3_CONTINUOUS);
    gfx_Begin();

    gfx_ZeroScreen();

    Border(0);

    gfx_SetTextFGColor(160);

    gfx_SetTextScale(2,2);
    PrintCentered("micrOS",100);
    gfx_SetTextScale(1,1);
    PrintCentered("v1.0a. press any key to continue.",125);


    while (!os_GetCSC());

    gfx_ZeroScreen();


    Border(1);


    gfx_SetTextXY(10,10);

    void *search_pos = NULL;
    uint8_t type;

     
      // loop to detect and display files
    while (((fileName = ti_DetectAny(&search_pos, NULL, &type)) != NULL) && (numFilesShown<10)) {
        if (type == TI_PRGM_TYPE || type == TI_PPRGM_TYPE) {
            slot = ti_Open(fileName,"r");
            size = ti_GetSize(slot);

            gfx_PrintStringXY(fileName,40,fileY);
            gfx_SetTextXY(135,fileY);
            gfx_PrintInt(size,4);

            numFiles++;
            numFile++;
            numFilesShown++;
            fileY += 15;
        }
    }


    
    key = kb_Data[7] == kb_Down;
    keytwo = kb_Data[6] == kb_Enter;

    gfx_PrintStringXY(">",30,20);

    while (!(kb_On)) {
        if ((kb_IsDown(kb_KeyDown)) && (selectedNum < numFiles) && (cycle > 50)) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",30,5+(selectedNum*15));
            selectedNum++;
            cycle = 0;
            gfx_SetTextFGColor(160);
            gfx_PrintStringXY(">",30,5+(selectedNum*15));
        } else if ((kb_IsDown(kb_KeyUp)) && (selectedNum != numFiles-5) && (cycle > 50)) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",30,5+(selectedNum*15));
            selectedNum--;
            cycle = 0;
            gfx_SetTextFGColor(160);
            gfx_PrintStringXY(">",30,5+(selectedNum*15));
        } else if ((kb_IsDown(kb_1))) {
            gfx_ZeroScreen();
            Border(1);
            while (cycle > 100) {
                cycle++;
            }
            gfx_SetTextScale(2,2);
            PrintCentered("micrOS",30);
            gfx_SetTextScale(1,1);
            PrintCentered("by nanobot567",50);
            PrintCentered("special thanks to...",80);
            PrintCentered("the CEMETECH community",95);
            gfx_PrintStringXY("1.0dev (do not distribute!)",16,204);
            while (!os_GetCSC());
        } else {
            cycle++;
            // gfx_PrintInt(cycle,4);
            kb_Scan();
        }
    }

    gfx_PrintInt(getKeyPress(),3);

    while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}

/* Prints a screen centered string */

void PrintCentered(const char *str,int height) {
    gfx_PrintStringXY(str,
                      (LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
                      height);
}

void Border(int draw_taskbar) {
    gfx_SetColor(160);
    gfx_HorizLine(0,5,LCD_WIDTH);
    gfx_VertLine(5,0,LCD_HEIGHT);
    gfx_HorizLine(0,235,LCD_WIDTH);
    gfx_VertLine(315,0,LCD_HEIGHT);
    if (draw_taskbar == 1) {
        gfx_HorizLine(0,220,LCD_WIDTH);
        gfx_PrintStringXY("micrOS",16,224);
        gfx_VertLine(70,220,15);
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
