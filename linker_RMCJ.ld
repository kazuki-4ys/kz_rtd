ENTRY(__main)
SECTIONS
{
        .text 0x808DD440 : {
                *(.text.__main);
                *(.text*);
        }
        myGlobalVarPtr = 0x80000CC0;
        OSReport = 0x801A24F0;
        strcmp =  0x800131C0;
        Egg__Heap__Alloc = 0x80229734;
        DVDConvertPathToEntryNum = 0x8015DE6C;
        DvdArchive__ripFile = 0x80518a70;
        DVDFastOpen = 0x8015E174;
        DVDReadPrio = 0x8015E754;
        DVDClose = 0x8015E488;
        memcpy = 0x80005F34;
        memcmp = 0x8000F238;
        strncpy = 0x80013104;
        sprintf = 0x80011950;
        strcmp = 0x800131c0;
        NETCalcCRC32 = 0x801d1bc0;
        strlen = 0x80021178;
        ControlLoader__Load = 0x805c25e0;
        ISFS_Open = 0x8016ad7c;
        ISFS_Close = 0x8016b2a4;
        OSLaunchTitle = 0x801AD920;
        bmg_func = 0x805F85CC;
        IOS_Open = 0x80193818;
        IOS_Close = 0x801939f8;
}