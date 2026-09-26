ENTRY(__main)
SECTIONS
{
        .text 0x808DD440 : {
                *(.text.__main);
                *(.text*);
        }
        myGlobalVarPtr = 0x80000cc0;
        OSReport = 0x801a24f0;
        strcmp = 0x800131c0;
        Egg__Heap__Alloc = 0x80229734;
        DVDConvertPathToEntryNum = 0x8015de6c;
        DvdArchive__ripFile = 0x80518a70;
        DVDFastOpen = 0x8015e174;
        DVDReadPrio = 0x8015e754;
        DVDClose = 0x8015e488;
        memcpy = 0x80005f34;
        memcmp = 0x8000f238;
        memmove = 0x8000f114;
        strncpy = 0x80013104;
        sprintf = 0x80011950;
        NETCalcCRC32 = 0x801d1bc0;
        strlen = 0x80021178;
        ControlLoader__Load = 0x805c25e0;
        ISFS_Open = 0x8016ad7c;
        ISFS_Close = 0x8016b2a4;
        OSLaunchTitle = 0x801ad920;
        bmg_func = 0x805f85cc;
        IOS_Open = 0x80193818;
        IOS_Close = 0x801939f8;
        MultiDvdArchive__clear = 0x8052a5c0;
        IOS_IoctlAsync = 0x80194078;
        IOS_IoctlvAsync = 0x8019441c;
        IOS_OpenAsync = 0x80193700;
        IOS_CloseAsync = 0x80193938;
        DCFlushRange = 0x801a154c;
        ICInvalidateRange = 0x801a1630;
        VIResetDimmingCount = 0x801bafcc;
        Egg__ExpHeap__create = 0x802269e8;
        sSystem__Q23EGG10BaseSystem = 0x803868e0;
        nw4r__ut__List_GetNext = 0x800af0a0;
        RACEDATA = 0x809bc788;
        SubtractTimers = 0x807edecc;
        trackMusicSpeedUpPatch4PlusCLwzAddr = 0x809c18b0;
        Egg__Heap__Free = 0x80229aa4;
        ISFS_Read = 0x8016b11c;
        UI__LayoutUIControl__setPicture = 0x8063d75c;
        UI__LayoutUIControl__setMiiPicture = 0x8063da48;
        UI__LayoutUIControl__hasPictureSourcePane = 0x8063d994;
        DVDOpen = 0x8015e1dc;
        DVDReadPrio = 0x8015e754;
        DVDClose = 0x8015e488;
        memset = 0x80006038;
        EGG__SceneManager__createSceneHookAddr = 0x8023b02c;
        EGG__Decomp__getExpandSize = 0x8021989c;
        EGG__Decomp__decodeSZS = 0x80218b4c;
        OSFatal = 0x801a4de4;
        PADReadHookAddr = 0x801af374;
        PADControlMotorHookAddr = 0x801af830;
        AutoPressAHookAddr = 0x800077c8;
        OnRelLoadedHookAddr = 0x8000a1f0;
        __OSBusClock = 0x800000f8;
        OSSleepTicks = 0x801aabc8;
        OSDisableInterrupts = 0x801a64cc;
        OSRestoreInterrupts = 0x801a64f4;
}
