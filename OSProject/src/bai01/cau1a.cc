#include <stdio.h>
#include <Windows.h>
typedef struct BOOT_SECTOR
{
    BYTE jmpBoot[3];    //Lệnh nhảy đền đoạn boot code.
    BYTE OEMName[8];    //Version/tên HĐH
    WORD BytesPerSec;   //Số bytes/sector
    BYTE SecPerCluster; //Số sectors/cluster
    WORD RsvdSecCnt;    //Số sector trước bảng FAT
    BYTE NumFATs;       //Số bảng FAT
    WORD RootEntCnt;    //số entry trong bảng RDET
    WORD TotSec16;      //tổng số sector của Volume
    BYTE Media;         //Loại Voulme
    WORD FATSz16;       //số sector trong 1 bảng FAT
    WORD SecPerTrk;     //Số sectors/track
    WORD NumHeads;      //Số heads
    DWORD HiddSec;      //Số sector ẩn trước Volume
    DWORD TotSec32;     //Số sector ẩn trước Volume
    DWORD FATSz32;      //số sector trong 1 bảng FAT
    WORD ExtFlags;      //chỉ số bảng FAT active
    WORD FSVer;         //Version FAT32
    DWORD RootClus;     //Chỉ số cluster đầu tiên của RDET
    WORD FSInfo;        //Chỉ số sector chứa FSINFO – thông tin sector trống.
    WORD BkBootSec;     //Chỉ số sector chứa bản sao của bootsector
    BYTE Reserved[12];  //Dành riêng
    BYTE DrvNum;        //Ký hiệu vật lý đĩa
    BYTE Reserved1;     //Dành riêng
    BYTE BootSig;       //Ký hiệu nhận diện HĐH
    DWORD VolID;        //Volume serial number
    BYTE VolLab[11];    //Volume label.
    BYTE FilSysType[8]; //Chuỗi nhận diện loại FAT: ”FAT32 ”.
    BYTE BootCode[420]; //Boot code
    WORD EndOfBoot;     //Dấu hiệu kết thúc bootsector (0x55AA)
} BootSector;
BootSector bootSector;

void readBootSector()
{

    int nRetCode = 0;
    BYTE byteBoot[512];
    memset(&byteBoot, 0, 512);
    HANDLE hFloppy = NULL;
    hFloppy = CreateFile(L"\\\\.\\D:",    // Floppy drive to open
                         GENERIC_READ,    // Access mode
                         FILE_SHARE_READ, // Share Mode
                         NULL,            // Security Descriptor
                         OPEN_EXISTING,   // How to create
                         0,               // File attributes
                         NULL);           // Handle to template
    if (hFloppy != NULL)
    {
        DWORD dw = 0;
        //Đọc thông tin từ bootsector và gán vào byteBoot
        if (!ReadFile(hFloppy, byteBoot, sizeof(byteBoot), &dw, NULL))
        {
            printf("Error in Reading Boot Sector.\n");
        }
        else
        {
            BYTE *pByteBoot = byteBoot;
            //Gán dãy bit trong byteBoot vào bootSector
            memcpy(&bootSector, pByteBoot, sizeof(byteBoot));
            //In các thông tin quan trọng của bootsector
            printf("sb: %lu\n", bootSector.RsvdSecCnt);
            printf("nf: %lu\n", bootSector.NumFATs);
            printf("sf: %lu\n", bootSector.FATSz32);
            printf("byte/sector: %lu\n", bootSector.BytesPerSec);
            printf("sector/cluster: %lu\n", bootSector.SecPerCluster);
            printf("Start cluster: %lu\n", bootSector.RootClus);
            //sector bắt đầu của Fat
            DWORD startOfFat = (bootSector.RsvdSecCnt);
            //sector bắt đầu của vùng data
            DWORD startOfData = (bootSector.RsvdSecCnt + bootSector.NumFATs * bootSector.FATSz32);
            printf("Sector start of Data: %lu\n", startOfData);
            printf("Byte start of Data: %lu\n", startOfData * bootSector.BytesPerSec);
            printf("Sector start of Fat: %lu\n", startOfFat);
            printf("Byte start of Fat: %lu\n", startOfFat * bootSector.BytesPerSec);
        }
        CloseHandle(hFloppy);
    }
}