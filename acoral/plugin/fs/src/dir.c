#define IN_DIR
#include "../include/fs.h"

acoral_u8 CurrentDrive;

acoral_u32 GetDirClusIndex(acoral_char *Path);

/*********************************************************************************************************
** ��������: StrToFDTName
** ��������: �û��ļ�\Ŀ¼��ת��Ϊϵͳ��
**
** �䡡��: Str:�û�����
**        
** �䡡��: ��������
**
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 StrToFDTName(acoral_char *FDTName, acoral_char *Str)
{
    acoral_u8 i, temp;
    
    /* �ļ�\Ŀ¼���Ƿ���Ч */
    if (Str[0] == 0x20 || Str[0] == 0)
    {
        return FILE_NAME_ERR; 
    }

    for (i = 11; i != 0; i--)
    {
        *FDTName++ = 0x20;
    }
    FDTName -= 11;
    

    /* �Ƿ�Ϊ"." */
    if (Str[0] == '.')
    if (Str[1] == 0 || Str[1] == '\\' || Str[1] == '/')
    {
        FDTName[0] = '.';
        return RETURN_OK;
    }

    /* �Ƿ�Ϊ".." */
    if (Str[0] == '.')
    if (Str[1] == '.' )
    if (Str[2] == 0 || Str[2] == '\\' || Str[2] == '/')
    {
        FDTName[0] = '.';
        FDTName[1] = '.';
        return RETURN_OK;
    }
    
    /* ��ȡ���ļ�/Ŀ¼�� */
    for (i = 8; i != 0; i--)
    {
        temp = *Str;
        if (temp == 0 || temp == '\\' || temp == '/')
        {
            break;
        }
        Str++;
        if (temp == '.')
        {
            break;
        }
        *FDTName++ = temp;
    }
    FDTName += i;
    
    /* ��ȡ�ļ�\Ŀ¼��չ�� */
    for (i = 3; i != 0; i--)
    {
        temp = *Str;
        if (temp == 0 || temp == '\\' || temp == '/')
        {
            break;
        }
        Str++;
        *FDTName++ = temp;
    }
    return RETURN_OK;
}

/*********************************************************************************************************
** ��������: _GetFDTInfo
** ��������: ��ȡFDT���ڵ�Ŀ¼�Ŀ�ʼ�غż�ϵͳ�����ƣ��ڲ�ʹ��
**
** �䡡��: DirFileName:�û�ʹ�õ�FDT��������·����
**         FDTName:���ڷ���ϵͳʹ�õ�FDT����������·����
** �䡡��: FDT���ڵ�Ŀ¼�Ŀ�ʼ�غţ�BAD_CLUS��ʾ�Ҳ���·��
**         
** ȫ�ֱ���: ��
** ����ģ��: GetDirClusIndex,StrToFDTName
********************************************************************************************************/
        acoral_u32 _GetFDTInfo(acoral_char *FDTName, acoral_char *DirFileName)
{
    acoral_u32 Rt;
    acoral_char *temp;
    acoral_u8 i;

    /* ��ȡ�ַ�������λ�� */
    temp = DirFileName;
    while (*temp != 0)
    {
         temp++;
    }
    temp--;
    if (*temp == '\\' || *temp == '/')  /* ����ַ�Ϊ\������Ч�ļ�/Ŀ¼�� */
    {
        return BAD_CLUS;
    }

    
    /* ��ȡĿ¼��ʼ�غ� */
    Rt = BAD_CLUS;
    while (1)
    {
        if (*temp == '\\' || *temp == '/' || *temp == ':')
        {
            /* �ҵ�Ŀ¼�ָ����'\' �� */
            /* �ҵ��߼��̷ָ����':'��������ָ���߼��̵�ǰĿ¼ */
            temp++;
            i = *temp;
            *temp = 0;
            Rt = GetDirClusIndex(DirFileName);
            *temp = i;
            break;
        }
        if (temp == DirFileName)
        {
            /* ֻ���ļ�\Ŀ¼���������ǵ�ǰ�߼��̵�ǰĿ¼ */
            Rt = GetDirClusIndex(".");
            break;
        }
        temp--;
    }
    /* ��ȡϵͳ���ļ�\Ŀ¼�� */
    if (StrToFDTName(FDTName, temp) != RETURN_OK)
    {
        Rt = BAD_CLUS;
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: GetDrive
** ��������: ��ȡָ��Ŀ¼��������
**
** �䡡��: Path:·����
**        
** �䡡��: ��������
**
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 GetDrive(const acoral_char *Path)
{
    acoral_u8 Drive;

    Drive = CurrentDrive;
    if (Path != NULL)
    {
//        strupr(Path);                           /* ��Ϊ��д */
        if (Path[1] == ':')
        {
        	if(Path[0]>='A' && Path[0]<='Z')
            	Drive = Path[0] - 'A';
            else
            	Drive = Path[0] - 'a';
            	
        }
    }
    return Drive;
}

/*********************************************************************************************************
** ��������: ChangeDrive
** ��������: �ı䵱ǰ�߼���
**
** �䡡��: Drive:�߼��̷��ַ���
**        
** �䡡��: RETURN_OK:�ɹ�
**        NOT_FIND_DISK:�߼��̲�����
**        PARAMETER_ERR:�Ƿ�����
** ȫ�ֱ���: ��
** ����ģ��: strupr,GetDiskInfo
********************************************************************************************************/
        acoral_u8 ChangeDrive(acoral_char *Drive)
{
    acoral_u8 Rt;
    Disk_Info *Disk;
    
    Rt = PARAMETER_ERR;
    strupr(Drive);                           /* ��Ϊ��д */
    if (Drive[1] == ':')
    {
        Rt = NOT_FIND_DISK;
        Disk = GetDiskInfo(Drive[0] - 'A');
        if (Disk != NULL)
        {
            CurrentDrive = Drive[0] - 'A';
            Rt = RETURN_OK;
        }
    }
    return Rt;    
}

/*********************************************************************************************************
** ��������: GetDirClusIndex
** ��������: ��ȡָ��Ŀ¼��ʼ�غ�
**
** �䡡��: Path:·����
**        
** �䡡��: ��ʼ�غţ�EMPTY_CLUS��Ϊ��Ŀ¼
**
** ȫ�ֱ���: ��
** ����ģ��: strupr,GetDiskInfo,FindFDTInfo
********************************************************************************************************/
        acoral_u32 GetDirClusIndex(acoral_char *Path)
{
    acoral_char DirName[12];
    acoral_u8 Drive;
    acoral_u32 Rt;
    FDT temp;
    Disk_Info *Disk;
    
    Rt = BAD_CLUS;
    if (Path != NULL)
    {
        strupr(Path);                           /* ��Ϊ��д */
        Drive = GetDrive(Path);                 /* ��ȡ·���̷� */
        if (Path[1] == ':')
        {
            Path += 2;
        }
        Disk = GetDiskInfo(Drive);              /* ��ȡ�߼�����Ϣ */
        if (Disk != NULL)
        {
            Rt = 0;
            if (Disk->FATType == FAT32)         /* FAT32 ��Ŀ¼ */
            {
                Rt = Disk->RootDirTable;
            }
            if (Path[0] != '\\' || Path[0] != '/')                /* ����Ŀ¼�ָ����ţ���������ǵ�ǰ·�� */
            {
                Rt = Disk->PathClusIndex;
            }
            else
            {
                Path++;
            }
            if (Path[0] == '.')             /* '\.'��������ǵ�ǰ·�� */
            {
                Rt = Disk->PathClusIndex;
                if (Path[1] == 0 || Path[1] == '\\' || Path[1] == '/')
                {
                    Path++;
                }
            }
            if (Path[0] == '\\' || Path[0] == '/')
            {
                Path++;
            }
            
            DirName[11] = 0;
            while (Path[0] != 0)
            {
                /* ��ȡ��Ŀ¼�� */
                StrToFDTName(DirName , Path);

                /* ��Ŀ¼����ʼ�غ� */
                if (DirName[0] == 0x20)
                {
                    Rt = BAD_CLUS;
                    break;
                }
                /* ��ȡFDT��Ϣ */
                if (FindFDTInfo(&temp, Drive, Rt, DirName) != RETURN_OK)
                {
                    Rt = BAD_CLUS;
                    break;
                }
                /* FDT�Ƿ���Ŀ¼ */
                if ((temp.Attr & ATTR_DIRECTORY) == 0)
                {
                    Rt = BAD_CLUS;
                    break;
                }
                Rt = temp.FstClusLO + ((acoral_u32)(temp.FstClusHI) << 16);
                /* �ַ�������һ��Ŀ¼ */
                while (1)
                {
                    if (*Path == '\\' || *Path == '/')
                    {
                        Path++;
                        break;
                    }
                    if (*Path == 0)
                    {
                        break;
                    }
                    Path++;
                }
            }
        }
        if (Disk->FATType == FAT32)
        if (Rt != BAD_CLUS)
        if (Rt == Disk->RootDirTable)
        {
            Rt = 0;
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: MakeDir
** ��������: ����Ŀ¼
**
** �䡡��: Path:·����
**
** �䡡��: RETURN_OK���ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵��
** ȫ�ֱ���: ��
** ����ģ��: strupr,ClearClus,AddFDT
********************************************************************************************************/
        acoral_u8 MakeDir(acoral_char *Path)
{
    acoral_u32 ClusIndex, Temp1;
    acoral_u8 Drive, Rt;
    FDT temp;
    
    strupr(Path);                       /* ��Ϊ��д */

    ClusIndex = _GetFDTInfo(temp.Name, Path);
    if (ClusIndex == BAD_CLUS)
    {
        return PATH_NOT_FIND;
    }

    Drive = GetDrive(Path);
    
    /* FDT�Ƿ���� */
    Rt = FDTIsLie(Drive, ClusIndex, temp.Name);
    if (Rt != NOT_FIND_FDT)
    {
        return Rt;
    }
    
    /* ������ */
    Temp1 = FATAddClus(Drive, 0);               /* ��ȡĿ¼������̿ռ� */
    if ((Temp1 <= EMPTY_CLUS_1) || (Temp1 >= BAD_CLUS))
    {
        /* û�п��пռ� */
        return  DISK_FULL;
    }

    ClearClus(Drive, Temp1);                /* ��մ� */
        
        /* ����FDT���� */
    temp.Attr = ATTR_DIRECTORY;             
    temp.FileSize = 0;

    temp.NTRes = 0;
    temp.CrtTimeTenth = 0;
    temp.CrtTime = 0;
    temp.CrtDate = 0;
    temp.LstAccDate = 0;
    temp.WrtTime = 0;
    temp.WrtDate = 0;

    temp.FstClusLO = Temp1 & 0xffff;
    temp.FstClusHI = Temp1 / 0x10000;

    Rt = AddFDT(Drive, ClusIndex, &temp);       /* ����Ŀ¼�� */
    if (Rt == RETURN_OK)
    {
        /* ����'.'Ŀ¼ */
        temp.Name[0] = '.';
        temp.Name[1] = 0x20;
        temp.Name[2] = 0x20;
        temp.Name[3] = 0x20;
        temp.Name[4] = 0x20;
        temp.Name[5] = 0x20;
        temp.Name[6] = 0x20;
        temp.Name[7] = 0x20;
        temp.Name[8] = 0x20;
        temp.Name[9] = 0x20;
        temp.Name[10] = 0x20;
        
        AddFDT(Drive, Temp1, &temp);

        /* ����'..'Ŀ¼ */
        temp.Name[1] = '.';
        
        temp.FstClusLO = ClusIndex & 0xffff;
        temp.FstClusHI = ClusIndex / 0x10000;
        Rt = AddFDT(Drive, Temp1, &temp);
    }
    else
    {
        FATDelClusChain(Drive, Temp1);
    }
    
    return Rt;
}

/*********************************************************************************************************
** ��������: RemoveDir
** ��������: ɾ��Ŀ¼
**
** �䡡��: Path:·����
**
** �䡡��: RETURN_OK���ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵��
** ȫ�ֱ���: ��
** ����ģ��: strupr,DelFDT
********************************************************************************************************/
        acoral_u8 RemoveDir(acoral_char *Path)
{
    acoral_u32 ClusIndex, ClusIndex1;
    acoral_u8 Drive, Rt;
    acoral_char DirName[12];
    FDT temp;
    
    strupr(Path);                       /* ��Ϊ��д */

    ClusIndex = _GetFDTInfo(DirName, Path);
    if (ClusIndex == BAD_CLUS)
    {
        return PATH_NOT_FIND;
    }

    Drive = GetDrive(Path);
    
    /* ��ȡFDT����Ϣ */
    Rt = FindFDTInfo(&temp, Drive, ClusIndex, DirName);
    if (Rt == RETURN_OK)
    {
        /* �Ƿ���Ŀ¼ */
        if ((temp.Attr & ATTR_DIRECTORY) != 0)
        {
            /* �� */
            ClusIndex1 = temp.FstClusLO + ((acoral_u32)(temp.FstClusHI) << 16);
            /* �Ƿ��ǿ�Ŀ¼ */
            Rt = DirIsEmpty(Drive, ClusIndex1);
            if (Rt == DIR_EMPTY)
            {
                /* �ǣ�ɾ�� */
                FATDelClusChain(Drive, ClusIndex1);
                Rt = DelFDT(Drive, ClusIndex, DirName);
            }
        }
        else
        {
            return PATH_NOT_FIND;
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: ChangeDir
** ��������: �ı䵱ǰĿ¼
**
** �䡡��: Path:·����
**
** �䡡��: RETURN_OK���ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵��
** ȫ�ֱ���: ��
** ����ģ��: GetDirClusIndex,GetDiskInfo
********************************************************************************************************/
        acoral_u8 ChangeDir(acoral_char *Path)
{
    acoral_u32 ClusIndex;
    acoral_u8 Rt, Drive;
    Disk_Info *Disk;

    Rt = PATH_NOT_FIND;
    ClusIndex = GetDirClusIndex(Path);
    if (ClusIndex != BAD_CLUS)
    {
        Drive = GetDrive(Path);
        Disk = GetDiskInfo(Drive);
        Rt = NOT_FIND_DISK;
        if (Disk != NULL)
        {
            Rt = RETURN_OK;
            Disk->PathClusIndex = ClusIndex;
        }
    }
    return Rt;
}
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
