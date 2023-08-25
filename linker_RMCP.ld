ENTRY(__main)
SECTIONS
{
        .text 0x808DD440 : {
                *(.text.__main);
                *(.text*);
        }
        myGlobalVarPtr = 0x80000CC0;
        OSReport = 0x801a25d0;
        strcmp =  0x8001329c;
        Egg__Heap__Alloc = 0x80229814;
        DVDConvertPathToEntryNum = 0x8015df4c;
        DvdArchive__ripFile = 0x805190f0;
        DVDFastOpen = 0x8015e254;
        DVDReadPrio = 0x8015e834;
        DVDClose = 0x8015e568;
        memcpy = 0x80005F34;
        memcmp = 0x8000f314;
        strncpy = 0x800131e0;
        sprintf = 0x80011a2c;
        NETCalcCRC32 = 0x801d1ca0;
        strlen = 0x80021254;
        ControlLoader__Load = 0x805c2c60;
        ISFS_Open = 0x8016ae5c;
        ISFS_Close = 0x8016b384;
        OSLaunchTitle = 0x801ada00;
        bmg_func = 0x805f8cf0;
        IOS_Open = 0x801938f8;
        IOS_Close = 0x80193ad8;
        MultiDvdArchive__clear = 0x8052ac40;
}