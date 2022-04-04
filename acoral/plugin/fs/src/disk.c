#define IN_DISK
#include "../include/fs.h"
Disk_Info DiskInfo[MAX_DRIVES];     //�߼�����Ϣ

/*********************************************************************************************************
** ��������: DiskInit
** ��������: ��ʼ���߼��̹���ģ��
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: DiskInfo
** ����ģ��: ��
********************************************************************************************************/
        void DiskInit(void)
{
    acoral_u8 i;
    
    for (i = 0; i < MAX_DRIVES; i++)
    {
        DiskInfo[i].Drive = EMPTY_DRIVE;    // û�з���
        DiskInfo[i].FATType = 0xff;         // ��Ч���ļ�ϵͳ
        DiskInfo[i].SecPerClus = 0;         // ÿ��������
        DiskInfo[i].NumFATs = 0;            // FAT����
        DiskInfo[i].DevId= -1;
        DiskInfo[i].SecPerDisk = 0xffffffff;// �߼�����������������
        DiskInfo[i].BytsPerSec = 0;         // ÿ�����ֽ���
        DiskInfo[i].RootDirTable = 0;       // ��Ŀ¼��ʼ�����ţ�FAT32Ϊ��ʼ�غţ�
        DiskInfo[i].RootSecCnt = 0;         // ��Ŀ¼ռ��������
        DiskInfo[i].FATStartSec = 0;        // FAT��ʼ������
        DiskInfo[i].FATSecCnt = 0;          // ÿ��FATռ��������
        DiskInfo[i].DataStartSec = 0;       // ��������ʼ������
        DiskInfo[i].PathClusIndex = 0;      // ��ǰĿ¼
        DiskInfo[i].DiakCommand = NULL;     // ��������
    }
    CacheInit();                //��ʼ������cache
}

/*********************************************************************************************************
** ��������: GetDiskInfo
** ��������: ��ȡָ���߼�����Ϣ
**
** �䡡��: �߼��̺�
**
** �䡡��: ָ���߼�����Ϣ�Ľṹ��ָ��
**         
** ȫ�ֱ���: DiskInfo
** ����ģ��: ��
********************************************************************************************************/
        Disk_Info * GetDiskInfo(acoral_u8 Drive)
{
    Disk_Info *Rt;
    Rt = NULL;
    if (Drive < MAX_DRIVES)
    {
        if (DiskInfo[Drive].Drive != EMPTY_DRIVE)
        {
            Rt = DiskInfo + Drive;
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: GetEmptyDiskInfoAddr
** ��������: ��ȡ�����߼���
**
** �䡡��: ��
**
** �䡡��: ָ���߼�����Ϣ�Ľṹ��ָ��
**         
** ȫ�ֱ���: DiskInfo
** ����ģ��: ��
********************************************************************************************************/
/*        Disk_Info * GetEmptyDiskInfoAddr(void)
{
    acoral_u8 i;
    Disk_Info *Rt;
    
    Rt = NULL;
    for (i = 0; i < MAX_DRIVES; i++)
    {
        if (DiskInfo[i].Drive == EMPTY_DRIVE)     // �߼��̺ſ���
        {
            Rt = DiskInfo + i;
            DiskInfo[i].Drive = i;
            break;
        }
    }
    return Rt;
}*/

/*********************************************************************************************************
** ��������: AddFileDriver
** ��������: ����һ���ײ���������
**
** �䡡��: DiakCommand����������ӿں���
**
** �䡡��: ��
**         
** ȫ�ֱ���: DiskInfo
** ����ģ��: ��
********************************************************************************************************/
static acoral_u8 Buf[512];
        acoral_32 AddFileDriver(acoral_u16  (* DiakCommand)(acoral_u8 Cammand, void *Parameter),acoral_char *devname,acoral_u8 drive)
{
	Disk_RW_Parameter Pa;
    acoral_u16 temp;
    acoral_u32 temp1;
    Pa.Drive=drive;
    Pa.Buf=(acoral_u8 *)devname;
    if(DiskInfo[drive].Drive!=EMPTY_DRIVE)
    	return -1;
    else
    	DiskInfo[drive].Drive=drive;
    
    
    if (DiakCommand == NULL)        // ������Ч�˳�
    {
        return -1;
    }

    if (DiakCommand(DISK_INIT, &Pa) == DISK_INIT_NOT_OK)   // �ײ�������ʼ�����ɹ��˳�
    {
        return -1;
    }

	/*��������ʱ��CurrentDrive��Ϊ��������Ӧ���豸*/
	CurrentDrive=drive;
	/*���豸ID�����豸�ṹ����*/
   /*	if(DiskInfo[i].DevId==ACORAL_DEV_ERR_ID)
		DiskInfo[i].DevId=acoral_dev_open(devname);
    *///Buf = OpenSec(DiskInfo[i].Drive, 0);    /* ������0������������ */
    ReadSuperSec(drive,Buf);
    if (Buf != NULL)
    {
        /* ÿ�����ֽ��� */
        DiskInfo[drive].BytsPerSec = Buf[11] | (Buf[12] << 8);
        /* ÿ�������� */
        DiskInfo[drive].SecPerClus = Buf[13];
        /* FAT��ʼ������ */
        DiskInfo[drive].FATStartSec = Buf[14] | (Buf[15] << 8);
        /* FAT����� */
        DiskInfo[drive].NumFATs = Buf[16];
        /* ��Ŀ¼ռ������ */ 
        DiskInfo[drive].RootSecCnt = ((Buf[17] | (Buf[18] << 8)) * 32 + 
                                   DiskInfo[drive].BytsPerSec - 1) /
                                   DiskInfo[drive].BytsPerSec;
        /* �߼��̣���ռ������ */
        temp = Buf[19] | (Buf[20] << 8);
        if (temp != 0)
        {
            DiskInfo[drive].SecPerDisk = temp;
        }
        else
        {
            DiskInfo[drive].SecPerDisk = Buf[32] | (Buf[33] << 8);
            DiskInfo[drive].SecPerDisk |= (((acoral_u32)Buf[34] << 16) | ((acoral_u32)Buf[35] << 24));
        }
        /* FAT��ռ�������� */
        temp = Buf[22] | (Buf[23] << 8);
        if (temp != 0)
        {
            DiskInfo[drive].FATSecCnt = temp;
        }
        else
        {
            DiskInfo[drive].FATSecCnt = Buf[36] | (Buf[37] << 8);
            DiskInfo[drive].FATSecCnt |= (((acoral_u32)Buf[38] << 16) | (acoral_u32)(Buf[39] << 24));
        }
        
        /* ��ǰĿ¼Ϊ��Ŀ¼ */
        DiskInfo[drive].PathClusIndex = 0;
    }
    /* ��Ŀ¼��ʼ������ */
    DiskInfo[drive].RootDirTable = DiskInfo[drive].NumFATs * DiskInfo[drive].FATSecCnt + 
                               DiskInfo[drive].FATStartSec;
    /* ��������ʼ������ */
    DiskInfo[drive].DataStartSec = DiskInfo[drive].RootDirTable + DiskInfo[drive].RootSecCnt;
    temp1 = DiskInfo[drive].SecPerDisk - DiskInfo[drive].DataStartSec;
    temp1 = temp1 / DiskInfo[drive].SecPerClus;
    DiskInfo[drive].ClusPerData = temp1;
    /* �ж���FAT12��FAT16����FAT32 */
    if (temp1 < 4085)
    {
        DiskInfo[drive].FATType = FAT12;
    }
    else if (temp1 < 65525)
    {
        DiskInfo[drive].FATType = FAT16;
    }
    else
    {
        DiskInfo[drive].FATType = FAT32;
        /* FAT32 RootDirTableΪ��ʼ�غ� */
        DiskInfo[drive].RootDirTable = Buf[44] | (Buf[45] << 8);
        DiskInfo[drive].RootDirTable |= (((acoral_u32)Buf[46] << 16) | ((acoral_u32)Buf[47] << 24));
        DiskInfo[drive].PathClusIndex = DiskInfo[drive].RootDirTable;
    }
            //CloseSec(DiskInfo[drive].Drive, 0);     /* �ر����� */
    return 0;
}

/*********************************************************************************************************
** ��������: RemoveFileDriver
** ��������: ɾ��һ���ײ���������
**
** �䡡��: Drive:�߼���������
**
** �䡡��: ��
**         
** ȫ�ֱ���: DiskInfo
** ����ģ��: ��
********************************************************************************************************/
        void RemoveFileDriver(acoral_u8 Drive)
{
    Disk_RW_Parameter Pa;
    
    if (Drive < MAX_DRIVES)
    if (DiskInfo[Drive].Drive != EMPTY_DRIVE)
    {
        AllCacheWriteBack();
        Pa.Drive = Drive;
        Pa.RsvdForLow = DiskInfo[Drive].RsvdForLow;
        DiskInfo[Drive].DiakCommand(DISK_CLOSE, &Pa);

        DiskInfo[Drive].Drive = EMPTY_DRIVE;    // û�з���
        DiskInfo[Drive].FATType = 0xff;         // ��Ч���ļ�ϵͳ
        DiskInfo[Drive].SecPerClus = 0;         // ÿ��������
        DiskInfo[Drive].NumFATs = 0;            // FAT����
        DiskInfo[Drive].DevId=-1;
        DiskInfo[Drive].SecPerDisk = 0xffffffff;// �߼�����������������
        DiskInfo[Drive].BytsPerSec = 0;         // ÿ�����ֽ���
        DiskInfo[Drive].RootDirTable = 0;       // ��Ŀ¼��ʼ�����ţ�FAT32Ϊ��ʼ�غţ�
        DiskInfo[Drive].RootSecCnt = 0;         // ��Ŀ¼ռ��������
        DiskInfo[Drive].FATStartSec = 0;        // FAT��ʼ������
        DiskInfo[Drive].FATSecCnt = 0;          // ÿ��FATռ��������
        DiskInfo[Drive].DataStartSec = 0;       // ��������ʼ������
        DiskInfo[Drive].PathClusIndex = 0;      // ��ǰĿ¼
        DiskInfo[Drive].DiakCommand = NULL;     // ��������
    }
}


/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
