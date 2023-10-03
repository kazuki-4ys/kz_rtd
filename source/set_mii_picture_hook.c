#include "set_mii_picture_hook.h"

void set_mii_picture_hook_asm(void);
void set_mii_picture_hook_asm_end(void);

void installSetMiiPictureHook(void){
    injectC2Patch(UI__LayoutUIControl__setMiiPicture, set_mii_picture_hook_asm, set_mii_picture_hook_asm_end);
}

unsigned char setMiiPictureHook(void *self, char *targetPaneName, UI__MiiGroup_Struct *miis, unsigned int playedId, unsigned int r7){
    //1を返したらデフォルトの挙動
    char replacePaneName[32];
    Mii* mii = miis->m_miis[playedId];
    if(!mii)return 1;
    sprintf(replacePaneName, "mii_%08x", mii->mii_id);
    OSReport("[KZ-RTD]: replacePaneName = %s\n", replacePaneName);
    if(UI__LayoutUIControl__hasPictureSourcePane(self, replacePaneName)){
        UI__LayoutUIControl__setPicture(self, targetPaneName, replacePaneName);
        return 0;
    }
    return 1;
}