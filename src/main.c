#include <tice.h>
#include <graphx.h>
#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>
#include "help.c"
#include "settings.c"
#include "fn.c"

void fileList(void);
void menu(void);

uint8_t numFiles = 0;
uint8_t numFilesShown = 0;
int selectedNum = 1;
char * prgmName;

/* Screen height: 240. Length: 320. When printing, the height goes from the top down.*/

int main(void)
{
    char * selectedName;
    uint8_t darkmode = 1;


    kb_SetMode(MODE_3_CONTINUOUS);
    gfx_Begin();
    gfx_ZeroScreen();
    Border(0,0);

    gfx_SetTextFGColor(224);
    gfx_SetTextScale(2,2);
    PrintCentered("micrOS",100);
    gfx_SetTextScale(1,1);
    PrintCentered("v1.1dev. press any key to continue.",125);
    PrintCentered("for help, press [y=] and navigate to help",200);

    while (!os_GetCSC());

    fileList();
    

    while (1==1) {
        if ((kb_IsDown(kb_KeyUp)) && ((selectedNum <= numFilesShown) && (selectedNum != 1))) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",20,5+(selectedNum*15));
            selectedNum--;
            gfx_SetTextFGColor(224);
            gfx_PrintStringXY(">",20,5+(selectedNum*15));
            delay(95);
        } else if ((kb_IsDown(kb_KeyDown)) && (selectedNum < numFilesShown)) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",20,5+(selectedNum*15));
            selectedNum++;
            gfx_SetTextFGColor(224);
            gfx_PrintStringXY(">",20,5+(selectedNum*15));
            delay(95);
        } else if ((kb_IsDown(kb_Yequ))) {
            menu();
            fileList();
            Border(1,1);
        // } else if ((kb_IsDown(kb_Graph)) && !((kb_IsDown(kb_KeyDown)))) {
        //     gfx_ZeroScreen();
        //     Border(1,0);
        //     selectedNum = 1;
        //     getHelp();
        //     fileList();
        } else if ((kb_IsDown(kb_2nd))) {
            delay(50);
            // FILE EXECUTION!!!!!

            // gfx_End();
            // os_RunPrgm(array[selectedNum-1],NULL,16,NULL);
            // gfx_Begin();
            // gfx_ZeroScreen();
            // Border(1,0);
            // selectedNum = 1;
            // fileList();
        } else if ((kb_IsDown(kb_Clear))) {
            break;
        } else {
            //
        }
    }
    
    /* End graphics drawing */
    gfx_End();

    return 0;
}

void menu(void) {
    int selectedMenuItem = 1;
    int maxMenuItems = 4;

    gfx_ZeroScreen();
    Border(1,0);
    gfx_PrintStringXY("settings",40,20);
    gfx_PrintStringXY("help",40,35);
    gfx_PrintStringXY("credits",40,50);
    gfx_PrintStringXY("exit menu",40,65);
    gfx_PrintStringXY(">",20,20);

    while (1==1) {
        if ((kb_IsDown(kb_KeyUp)) && ((selectedMenuItem <= maxMenuItems) && (selectedMenuItem != 1))) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",20,5+(selectedMenuItem*15));
            gfx_HorizLine(108,20,52);
            selectedMenuItem--;
            gfx_SetTextFGColor(224);
            gfx_PrintStringXY(">",20,5+(selectedMenuItem*15));
            delay(95);
        } else if ((kb_IsDown(kb_KeyDown)) && (selectedMenuItem < maxMenuItems)) {
            gfx_SetTextFGColor(0);
            gfx_PrintStringXY(">",20,5+(selectedMenuItem*15));
            selectedMenuItem++;
            gfx_SetTextFGColor(224);
            gfx_PrintStringXY(">",20,5+(selectedMenuItem*15));
            delay(95);
        } else if ((kb_IsDown(kb_2nd))) {
            if (selectedMenuItem == 1) {
                settings();
                gfx_ZeroScreen();
                selectedMenuItem = 1;
                selectedNum = 1;
                break;
            } else if (selectedMenuItem == 2) {
                getHelp();
                gfx_ZeroScreen();
                selectedMenuItem = 1;
                selectedNum = 1;
                break;
            } else if (selectedMenuItem == 3) {
                credits();
                gfx_ZeroScreen();
                selectedMenuItem = 1;
                selectedNum = 1;
                break;
            } else if (selectedMenuItem == 4) {
                gfx_ZeroScreen();
                selectedMenuItem = 1;
                selectedNum = 1;
                break;
            } else {
                gfx_ZeroScreen();
                selectedMenuItem = 1;
                selectedNum = 1;
                break;
            }
        } else {
            //pass
        }
    }
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
    gfx_SetTextFGColor(224);
    gfx_SetTextXY(10,10);

    while (((fileName = ti_DetectAny(&searchPos, NULL, &type)) != NULL) && (numFilesShown<12)) {
        if (type == TI_PRGM_TYPE || type == TI_PPRGM_TYPE) {
            if (*fileName == '!' || *fileName == '#' || *fileName == *"MICROS") { 
                continue;
            }
            
            slot = ti_Open(fileName,"r");
            size = ti_GetSize(slot);

            gfx_PrintStringXY(fileName,40,fileY);
            gfx_SetTextXY(114,fileY);
            gfx_PrintInt(size,5);

            // array[numFiles] = fileName;
            // gfx_PrintString(array[numFiles]);

            ti_Close(slot);

            numFiles++;
            numFilesShown++;
            fileY += 15;

        }
    }

    gfx_PrintStringXY(">",20,20);
}
