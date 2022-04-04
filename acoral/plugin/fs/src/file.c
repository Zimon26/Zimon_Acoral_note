#define IN_FILE
#include "../include/fs.h"

static MY_FILE FileInfo[MAX_OPEN_FILES];        /* ���ļ���Ϣ�� */

extern acoral_u32 _GetFDTInfo(acoral_char *FDTName, acoral_char *DirFileName);


/*********************************************************************************************************
** ��������: FileInit
** ��������: ��ʼ���ļ�ָ��ϵͳ
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        void FileInit(void)
{
    HANDLE i;
    
    for (i = 0; i < MAX_OPEN_FILES; i++)
    {
        FileInfo[i].Flags = 0;
    }
}

/*********************************************************************************************************
** ��������: FindOpenFile
** ��������: �����Ѵ򿪵�ָ���ļ����ļ�������ڲ�ʹ��
**
** �䡡��: Drive:�ļ����ڵ��߼��̺�
**        DirClus:�ļ�����Ŀ¼�Ŀ�ʼ�غ�
**        FileName:�ڲ��ļ���
** �䡡��: �ļ������Not_Open_FILEΪû�д�
**         
** ȫ�ֱ���: FileInfo
** ����ģ��: _GetFDTInfo,GetDrive,FindFDTInfo,
********************************************************************************************************/
        HANDLE FindOpenFile(acoral_u8 Drive, acoral_u32 DirClus, acoral_char FileName[11])
{
    HANDLE Rt;
    MY_FILE *fp;
    
    fp = FileInfo;
    for (Rt = 0; Rt < MAX_OPEN_FILES; Rt++)
    {
        if (fp->Flags != 0)
        if (fp->Drive == Drive)
        if (fp->DirClus == DirClus)
        if (fp->Name[0] == FileName[0])
        if (fp->Name[1] == FileName[1])
        if (fp->Name[2] == FileName[2])
        if (fp->Name[3] == FileName[3])
        if (fp->Name[4] == FileName[4])
        if (fp->Name[5] == FileName[5])
        if (fp->Name[6] == FileName[6])
        if (fp->Name[7] == FileName[7])
        if (fp->Name[8] == FileName[8])
        if (fp->Name[9] == FileName[9])
        if (fp->Name[10] == FileName[10])
        {
            break;
        }
        fp++;
    }
    if (Rt >= MAX_OPEN_FILES)
    {
        Rt = Not_Open_FILE;
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: RemoveFile
** ��������: ɾ���ļ�
**
** �䡡��: DirFileName:�û�ʹ�õ��ļ���
**
** �䡡��: RETURN_OK���ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵��
** ȫ�ֱ���: ��
** ����ģ��: strupr,_GetFDTInfo,GetDrive,FindFDTInfo,FATDelClusChain,DelFDT
********************************************************************************************************/
        acoral_u8 RemoveFile(acoral_char *DirFileName)
{
    acoral_u32 ClusIndex, ClusIndex1;
    acoral_u8 Drive, Rt;
    acoral_char DirName[12];
    FDT temp;
    
    strupr(DirFileName);                       /* ��Ϊ��д */
    ClusIndex = _GetFDTInfo(DirName, DirFileName);
    Rt = PATH_NOT_FIND;
    if (ClusIndex != BAD_CLUS)
    {
        Drive = GetDrive(DirFileName);     /* ��ȡ�ļ������߼��̺� */
        Rt = FindFDTInfo(&temp, Drive, ClusIndex, DirName);
        if (Rt == RETURN_OK)
        {
            Rt = NOT_FIND_FILE;
            if ((temp.Attr & ATTR_DIRECTORY) == 0)  /* ���ļ���ɾ�� */
            {
                Rt = FILE_LOCK;
		/****************MODIFY BY GAOPAN*****************/
       //         if (FindOpenFile(Drive, ClusIndex, DirName) < MAX_OPEN_FILES)
                if (FindOpenFile(Drive, ClusIndex, DirName) == Not_Open_FILE)
		/****************MODIFY BY GAOPAN******END*******/

                {
                    /* �ļ�û�д򿪲�ɾ�� */
                    ClusIndex1 = temp.FstClusLO + ((acoral_u32)(temp.FstClusHI) << 16);
                    FATDelClusChain(Drive, ClusIndex1);
                    Rt = DelFDT(Drive, ClusIndex, DirName);
                }
            }
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: FindOpenFileW
** ��������: �����Զ�д��ʽ�򿪵�ָ���ļ����ļ�������ڲ�ʹ��
**
** �䡡��: Drive:�ļ����ڵ��߼��̺�
**        DirClus:�ļ�����Ŀ¼�Ŀ�ʼ�غ�
**        FileName:�ڲ��ļ���
** �䡡��: �ļ������Not_Open_FILEΪû�д�
**         
** ȫ�ֱ���: FileInfo
** ����ģ��: _GetFDTInfo,GetDrive,FindFDTInfo,
********************************************************************************************************/
        HANDLE FindOpenFileW(acoral_u8 Drive, acoral_u32 DirClus, acoral_char FileName[11])
{
    HANDLE Rt;
    MY_FILE *fp;
    
    fp = FileInfo;
    for (Rt = 0; Rt < MAX_OPEN_FILES; Rt++)
    {
        if ((fp->Flags & FILE_FLAGS_WRITE) != 0)
        if (fp->Drive == Drive)
        if (fp->DirClus == DirClus)
        if (fp->Name[0] == FileName[0])
        if (fp->Name[1] == FileName[1])
        if (fp->Name[2] == FileName[2])
        if (fp->Name[3] == FileName[3])
        if (fp->Name[4] == FileName[4])
        if (fp->Name[5] == FileName[5])
        if (fp->Name[6] == FileName[6])
        if (fp->Name[7] == FileName[7])
        if (fp->Name[8] == FileName[8])
        if (fp->Name[9] == FileName[9])
        if (fp->Name[10] == FileName[10])
        {
            break;
        }
        fp++;
    }
    if (Rt >= MAX_OPEN_FILES)
    {
        Rt = Not_Open_FILE;
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: _FileOpenR
** ��������: ֻ����ʽ���ļ����ڲ�ʹ��
**
** �䡡��: DirFileName:�û�ʹ�õ��ļ���
**
** �䡡��: �ļ������Not_Open_FILEΪ���ܴ�
**         
** ȫ�ֱ���: FileInfo
** ����ģ��: _GetFDTInfo,GetDrive,FindFDTInfo,
********************************************************************************************************/
        HANDLE _FileOpenR(acoral_char *DirFileName)
{
    MY_FILE *fp;
    HANDLE Rt;
    FDT FileFDT;
    
    /* ���ҿ����ļ��Ǽ��� */
    for (Rt = 0; Rt < MAX_OPEN_FILES; Rt++)
    {
        if (FileInfo[Rt].Flags == 0)
        {
            break;
        }
    }
    
    if (Rt < MAX_OPEN_FILES)
    {
        fp = FileInfo + Rt;
        
        /* ��ȡĿ¼��ʼ�غź��ļ��� */
        fp->DirClus = _GetFDTInfo(fp->Name, DirFileName);
        if (fp->DirClus < BAD_CLUS)
        {
            fp->Drive = GetDrive(DirFileName);     /* ��ȡ�ļ������߼��̺� */
            
            /* ��ȡ�ļ���Ϣ */
            if (FindFDTInfo(&FileFDT, fp->Drive, fp->DirClus, fp->Name) == RETURN_OK)
            {
                if ((FileFDT.Attr & ATTR_DIRECTORY) == 0)
                {
                    fp->Flags = FILE_FLAGS_READ;
                    fp->FileSize = FileFDT.FileSize;
                    fp->FstClus = FileFDT.FstClusLO | (acoral_u32)FileFDT.FstClusHI << 16;
                    fp->Clus = fp->FstClus;
                    fp->Offset = 0;
                    return Rt;
                }
            }
        }
    }
    return Not_Open_FILE;
}

/*********************************************************************************************************
** ��������: _FileOpenW
** ��������: ֻд��ʽ���ļ����ڲ�ʹ��
**
** �䡡��: DirFileName:�û�ʹ�õ��ļ���
**
** �䡡��: �ļ������Not_Open_FILEΪ���ܴ�
**         
** ȫ�ֱ���: FileInfo
** ����ģ��: _GetFDTInfo,GetDrive,FindFDTInfo,
********************************************************************************************************/
        HANDLE _FileOpenW(acoral_char *DirFileName)
{
    MY_FILE *fp;
    FDT temp;
    HANDLE Rt;
    acoral_u8 i;

    for (Rt = 0; Rt < MAX_OPEN_FILES; Rt++)
    {
        if (FileInfo[Rt].Flags == 0)
        {
            break;
        }
    }
    
    if (Rt < MAX_OPEN_FILES)
    {
        fp = FileInfo + Rt;
        
        /* ��ȡĿ¼��ʼ�غź��ļ��� */
        fp->DirClus = _GetFDTInfo(fp->Name, DirFileName);
        if (fp->DirClus < BAD_CLUS)
        {
            fp->Drive = GetDrive(DirFileName);     /* ��ȡ�ļ������߼��̺� */

            /* �ļ��Ѿ��Զ�д��ʽ�򿪣������ٴ��Զ�д��ʽ�� */
            if (FindOpenFileW(fp->Drive, fp->DirClus, fp->Name) == Not_Open_FILE)
            {
                if (FindFDTInfo(&temp, fp->Drive, fp->DirClus, fp->Name) == RETURN_OK)
                {
                    if ((temp.Attr & ATTR_DIRECTORY) != 0)
                    {
                       return Not_Open_FILE;
                    }
                    if (RemoveFile(DirFileName) != RETURN_OK)   /* ɾ���ļ� */
                    {
                       return Not_Open_FILE;
                    }
                }
                /* �����ļ� */
                for (i = 0; i < 11; i++)
                {
                    temp.Name[i] = fp->Name[i];
                }
                temp.Attr = 0;
                temp.FileSize = 0;

                temp.NTRes = 0;
                temp.CrtTimeTenth = 0;
                temp.CrtTime = 0;
                temp.CrtDate = 0;
                temp.LstAccDate = 0;
                temp.WrtTime = 0;
                temp.WrtDate = 0;

                temp.FstClusLO = 0;
                temp.FstClusHI = 0;
                if (AddFDT(fp->Drive, fp->DirClus, &temp) == RETURN_OK)       /* �����ļ� */
                {
                    /* �����ļ���Ϣ */
                    fp->Flags = FILE_FLAGS_READ | FILE_FLAGS_WRITE;
                    fp->FileSize = 0;
                    fp->FstClus = 0;
                    fp->Clus = 0;
                    fp->Offset = 0;
                    return Rt;
                }
            }
        }
    }
    return Not_Open_FILE;
}

/*********************************************************************************************************
** ��������: _FileOpenRW
** ��������: ֻ��д��ʽ���ļ����ڲ�ʹ��
**
** �䡡��: DirFileName:�û�ʹ�õ��ļ���
**
** �䡡��: �ļ������Not_Open_FILEΪ���ܴ�
**         
** ȫ�ֱ���: ��
** ����ģ��: _FileOpenR,_FileOpenW
********************************************************************************************************/
        HANDLE _FileOpenRW(acoral_char *DirFileName)
{
    HANDLE Rt;
    
    Rt = _FileOpenR(DirFileName);
    if (Rt == Not_Open_FILE)
    {
        Rt = _FileOpenW(DirFileName);
    }
    else
    {
        if (FindOpenFileW(FileInfo[Rt].Drive, FileInfo[Rt].DirClus, FileInfo[Rt].Name) == Not_Open_FILE)
        {
            FileInfo[Rt].Flags |=  (FILE_FLAGS_WRITE | FILE_FLAGS_READ);
        }
        else
        {
            FileInfo[Rt].Flags = 0;
            Rt = Not_Open_FILE;
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: FileOpen
** ��������: ��ָ����ʽ���ļ�
**
** �䡡��: DirFileName:�û�ʹ�õ��ļ���
**        Type:�򿪷�ʽ
** �䡡��: �ļ������Not_Open_FILEΪ���ܴ�
**         
** ȫ�ֱ���: ��
** ����ģ��: _FileOpenR,_FileOpenW,_FileOpenRW
********************************************************************************************************/
        HANDLE FileOpen(acoral_char *DirFileName, acoral_char *Type)
{
    HANDLE Rt;

    Rt = Not_Open_FILE;    
    strupr(Type);
    strupr(DirFileName);
    if (Type[0] == 'R')
    {
        if (Type[1] == 'W')
        {
            Rt = _FileOpenRW(DirFileName);
        }
        else
        {
            Rt = _FileOpenR(DirFileName);
        }
        return Rt;
    }
    if (Type[0] == 'W')
    {
        if (Type[1] == 'R')
        {
            Rt = _FileOpenRW(DirFileName);
        }
        else
        {
            Rt = _FileOpenW(DirFileName);
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: FileClose
** ��������: �ر�ָ���ļ�
**
** �䡡��: Handle:�ļ����
**
** �䡡��: RETURN_OK:�ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵�� 
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 FileClose(HANDLE Handle)
{
    acoral_u8 Rt;
    FDT FileFDT;
    MY_FILE *fp;
    
    Rt = PARAMETER_ERR;
    if (Handle >= 0 && Handle < MAX_OPEN_FILES)
    {
        Rt = RETURN_OK;
        fp = FileInfo + Handle;
        if ((fp->Flags & FILE_FLAGS_WRITE) == FILE_FLAGS_WRITE)
        {
            Rt = FindFDTInfo(&FileFDT, fp->Drive, fp->DirClus, fp->Name);
            if (Rt == RETURN_OK)
            if (FileFDT.FileSize < fp->FileSize)
            {
                FileFDT.FileSize = fp->FileSize;
                if (FileFDT.FstClusLO == 0)
                if (FileFDT.FstClusHI == 0)
                {
                    FileFDT.FstClusLO = fp->FstClus & 0xffff;
                    FileFDT.FstClusHI = (fp->FstClus >> 16) & 0xffff;
                }
                ChangeFDT(fp->Drive, fp->DirClus, &FileFDT);
            }
        }
        fp->Flags = 0;
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: FileGetCh
** ��������: ���ļ���һ���ֽ�
**
** �䡡��: Ch:���ض���������
**        Handle:�ļ����
** �䡡��: RETURN_OK:�ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵�� 
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 FileGetCh(acoral_u8 *Ch, HANDLE Handle)
{
    acoral_u32 i, j, SecIndex;
    MY_FILE *fp;
    Disk_Info * DiskInfo;
    acoral_u8 Rt;
    acoral_u8 *Buf;
    
    Rt = PARAMETER_ERR;
    fp = FileInfo + Handle;
    if (Handle >= 0 && Handle < MAX_OPEN_FILES)     /* Handle�Ƿ���Ч */
    if (fp->Flags != 0)                             /* ��Ӧ�Ĵ��ļ���Ϣ���Ƿ���ʹ�� */
    {
        Rt = FILE_EOF;
        if (fp->Offset >= fp->FileSize)
        {
            /* ��������ݳ����ļ��ĳ��ȣ���һ��˭���б�ĳ�������д����ļ� */
            /* ����У�������ļ��ĳ����б仯������֮*/
            Handle = FindOpenFileW(fp->Drive, fp->DirClus, fp->Name);
            if (Handle !=  Not_Open_FILE)
            {
                fp->FileSize = FileInfo[Handle].FileSize;
                if (fp->Offset == 0)
                {
                    fp->FstClus = FileInfo[Handle].FstClus;
                    fp->Clus = FileInfo[Handle].Clus;
                }
            }
        }
        Rt = FILE_EOF;
        if (fp->Offset < fp->FileSize)              /* �Ƿ��ļ����� */
        {
            Rt = NOT_FIND_DISK;
                /* ��ȡ�ļ������߼�����Ϣ */
            DiskInfo = GetDiskInfo(fp->Drive);
            if (DiskInfo != NULL)
            {
                /* ���������������� */
                j = fp->Offset % (DiskInfo->SecPerClus * DiskInfo->BytsPerSec);
                i = j / DiskInfo->BytsPerSec;
                j = j % DiskInfo->BytsPerSec;
                SecIndex = (fp->Clus - 2) * DiskInfo->SecPerClus + 
                           DiskInfo->DataStartSec + i;
                Rt = SECTOR_READ_ERR;
                /* ������ */
                Buf = OpenSec(fp->Drive, SecIndex);
                if (Buf != NULL)
                {
                    /* ��ȡ�������� */
                    if (ReadSec(fp->Drive, SecIndex) == RETURN_OK)
                    {
                        /* ��ȡ���� */
                        *Ch = Buf[j];
                        /* �����ļ�ָ�� */
                        fp->Offset++;
                        j++;
                        if (j >= DiskInfo->BytsPerSec)
                        {
                            i++;
                            if (i >= DiskInfo->SecPerClus)
                            {
                                fp->Clus = FATGetNextClus(fp->Drive, fp->Clus);
                            }
                        }
                        Rt = RETURN_OK;
                    }
                    /* �ر����� */
                    CloseSec(fp->Drive, SecIndex);
                }
            }
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: FileRead
** ��������: ��ȡ�ļ�
**
** �䡡��: Buf:������ص�����
**        Size:Ҫ�����ֽ���
**        Handle:�ļ����
** �䡡��: ʵ�ʶ������ֽ���
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
 /*       acoral_32 FileRead(void *Buf, acoral_u32 Size, HANDLE Handle)
{
    acoral_u8 *temp;
    acoral_u32 i;
    
    temp = (acoral_u8 *)Buf;
    for (i = 0; i < Size; i++)
    {
        if (FileGetCh(temp, Handle) != RETURN_OK)
        {
            break;
        }
        temp++;
    }
    return i;
}*/
	/***************re-write by gaopan*******************/
	acoral_32 FileRead(void *Buf_out, acoral_u32 Size, HANDLE Handle)
{
	acoral_32 Rt;
	MY_FILE * fp;
	acoral_u32 i,j,k,SecIndex,RealSize,FirstSize;
	Disk_Info *DiskInfo;
	acoral_u8 *SecBuf;
	acoral_u8 *Buf=(acoral_u8 *)Buf_out;

	Rt = -1;
	RealSize=Size;
	fp = FileInfo + Handle;
	if(Buf!=NULL)
	if(Handle >= 0 && Handle < MAX_OPEN_FILES)
	if(fp->Flags != 0 )
	{
		Rt = 0;
		if(fp->Offset+Size >= fp->FileSize)
		{
			Handle = FindOpenFileW(fp->Drive,fp->DirClus,fp->Name);
			if(Handle !=  Not_Open_FILE)
			{
				fp->FileSize = FileInfo[Handle].FileSize;
				if(fp->Offset == 0)
				{
					fp->FstClus = FileInfo[Handle].FstClus;
					fp->Clus = FileInfo[Handle].FstClus;
				}
			}
		}
		if(fp->Offset < fp->FileSize)
		{
			if(fp->Offset+Size >= fp->FileSize)
				RealSize=fp->FileSize - fp->Offset;
			Rt = RealSize;
//			Rt=NOT_FIND_DISK;
			DiskInfo = GetDiskInfo(fp->Drive);
			if(DiskInfo != NULL)
			{
				j=fp->Offset % (DiskInfo->SecPerClus * DiskInfo->BytsPerSec);
				i=j / DiskInfo->BytsPerSec;
				j=j % DiskInfo->BytsPerSec;
				SecIndex = (fp->Clus-2) * DiskInfo->SecPerClus+DiskInfo->DataStartSec+i;
//				Rt = SECTOR_READ_ERR;
				//�����һ������
				SecBuf = OpenSec(fp->Drive,SecIndex);
				if(SecBuf == NULL)
				{
					return -1;
				}
				
				if(ReadSec(fp->Drive,SecIndex) == RETURN_OK)
				{
					FirstSize = ((DiskInfo->BytsPerSec-j)<RealSize) ? (DiskInfo->BytsPerSec-j):RealSize;
					for(k=FirstSize;k>0;k--)
					{
						*Buf++ = SecBuf[j];
						j++;
					}
					fp->Offset = fp->Offset + FirstSize;
					RealSize = RealSize - FirstSize;
				}
				else
					return -1;
				
				CloseSec(fp->Drive,SecIndex);
				if(j>=DiskInfo->BytsPerSec)
				{
					i++;
					if(i>=DiskInfo->SecPerClus)
					{
						i=0;
						fp->Clus = FATGetNextClus(fp->Drive,fp->Clus);
					}
				}

				//�����м�����
				for(;RealSize >= DiskInfo->BytsPerSec;RealSize -= DiskInfo->BytsPerSec)
				{
					SecIndex=(fp->Clus-2) * DiskInfo->SecPerClus+DiskInfo->DataStartSec+i;
					if((SecBuf = OpenSec(fp->Drive,SecIndex))==NULL)
						return -1;
					if(ReadSec(fp->Drive,SecIndex) != RETURN_OK)
						return -1;
					for(k=0;k<DiskInfo->BytsPerSec;k+=4)
					{
						Buf[0] = SecBuf[k];
						Buf[1] = SecBuf[k+1];
						Buf[2] = SecBuf[k+2];
						Buf[3] = SecBuf[k+3];
						Buf += 4;
					}
					CloseSec(fp->Drive,SecIndex);
					fp->Offset = fp->Offset+DiskInfo->BytsPerSec;
					i++;
					if(i>=DiskInfo->SecPerClus)
					{
						i=0;
						fp->Clus = FATGetNextClus(fp->Drive,fp->Clus);
					}
					
				}

				//�������һ������
				if(RealSize>0)
				{
					SecIndex=(fp->Clus-2) * DiskInfo->SecPerClus+DiskInfo->DataStartSec+i;
					if((SecBuf = OpenSec(fp->Drive,SecIndex))==NULL)
						return -1;
					if(ReadSec(fp->Drive,SecIndex) != RETURN_OK)
						return -1;
					for(k=0;k<RealSize;k++)
						*Buf++ = SecBuf[k];
					CloseSec(fp->Drive,SecIndex);
					fp->Offset = fp->Offset+RealSize;					
				}
			}
			else
				return -1;
		}
	}
	return Rt;
}
/*********************************************************************************************************
** ��������: FilePutCh
** ��������: дһ���ֽڵ��ļ�
**
** �䡡��: Ch:Ҫд������
**        Handle:�ļ����
** �䡡��: RETURN_OK:�ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵�� 
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 FilePutCh(acoral_u8 Ch, HANDLE Handle)
{
    acoral_u32 i, j, SecIndex;
    MY_FILE *fp;
    Disk_Info * DiskInfo;
    acoral_u8 Rt;
    acoral_u8 *Buf;

    Rt = PARAMETER_ERR;
    fp = FileInfo + Handle;
    if (Handle >= 0 && Handle < MAX_OPEN_FILES)      /* Handle�Ƿ���Ч */
    if (((fp->Flags) & FILE_FLAGS_WRITE) != 0)       /* ��Ӧ�Ĵ��ļ���Ϣ���Ƿ���ʹ�� */
    {
        Rt = FILE_EOF;
        if (fp->Offset <= fp->FileSize)
        {
            Rt = NOT_FIND_DISK;
                /* ��ȡ�ļ������߼�����Ϣ */
            DiskInfo = GetDiskInfo(fp->Drive);
            if (DiskInfo != NULL)
            {
                
                /* �����ļ�ָ�� */
                j = (fp->Offset) % (DiskInfo->SecPerClus * DiskInfo->BytsPerSec); 
                
                if (j == 0)
                {
                    if (fp->Offset < fp->FileSize)
                    {
                        fp->Clus = FATGetNextClus(fp->Drive, fp->Clus);
                    }
                    else
                    {
                        i = FATAddClus(fp->Drive, fp->Clus);
                        if (i >= BAD_CLUS)
                        {
                            return DISK_FULL;
                        }
                        fp->Clus = i;
                        if (fp->FstClus == EMPTY_CLUS)
                        {
                            fp->FstClus = i;
                        }
                    }
                }
                
                /* ���������������� */
                i = j / DiskInfo->BytsPerSec;
                j = j % DiskInfo->BytsPerSec;
                SecIndex = (fp->Clus - 2) * DiskInfo->SecPerClus + DiskInfo->DataStartSec + i;
                Rt = SECTOR_READ_ERR;
                
                /* �������ļ���Ϣ�� */
                fp->Offset++;
                if (fp->Offset > fp->FileSize)
                {
                    fp->FileSize = fp->Offset;
                }

                /* ������ */
                Buf = OpenSec(fp->Drive, SecIndex);
                if (Buf != NULL)
                {
                    /* д�������� */
                    if (ReadSec(fp->Drive, SecIndex) == RETURN_OK)
                    {
                        /* �洢���� */
                        Buf[j] = Ch;
                        WriteSec(fp->Drive, SecIndex);
                        Rt = RETURN_OK;
                    }
                    CloseSec(fp->Drive, SecIndex);
                }
            }
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: FileWrite
** ��������: д�ļ�
**
** �䡡��: Buf:Ҫд������
**        Size:Ҫд���ֽ���
**        Handle:�ļ����
** �䡡��: ʵ��д���ֽ���
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
/*        acoral_32 FileWrite(void *Buf, acoral_u32 Size, HANDLE Handle)
{
    acoral_u8 *temp;
    acoral_u32 i;
    
    temp = (acoral_u8 *)Buf;
    for (i = 0; i < Size; i++)
    {
        if (FilePutCh(*temp, Handle) != RETURN_OK)
        {
            break;
        }
        temp++;
    }
    return i;
}*/
	acoral_32 FileWrite(const void *Buf_in,acoral_u32 Size,HANDLE Handle)
{
	acoral_u8 *Buf=(acoral_u8 *)Buf_in;
	MY_FILE *fp;
	acoral_u8 *SecBuf=NULL;
	Disk_Info *DiskInfo;
	acoral_u32 i,j,k,SecIndex,FirstSize,RealSize;

	fp=FileInfo+Handle;
	RealSize=Size;

	if(Buf_in==NULL||Handle<0||Handle>=MAX_OPEN_FILES)
		return -1;
	if(fp->Offset>fp->FileSize || (((fp->Flags)&FILE_FLAGS_WRITE)==0))
		return -1;
	if(Size==0)
		return 0;

	if((DiskInfo=GetDiskInfo(fp->Drive))==NULL)
		return -1;
	j=fp->Offset%(DiskInfo->SecPerClus * DiskInfo->BytsPerSec);
	if(j==0)
	{
		if(fp->Offset<fp->FileSize)
			fp->Clus=FATGetNextClus(fp->Drive,fp->Clus);
		else
		{
			i=FATAddClus(fp->Drive,fp->Clus);
			if(i>=BAD_CLUS)
				return -1;
			fp->Clus = i;
			if(fp->FstClus==EMPTY_CLUS)
				fp->FstClus=i;
		}
	}
	i=j/DiskInfo->BytsPerSec;
	j=j%DiskInfo->BytsPerSec;
	SecIndex=(fp->Clus-2)*DiskInfo->SecPerClus+DiskInfo->DataStartSec+i;
	//�����һ������
	SecBuf = (acoral_u8 *)OpenSec(fp->Drive,SecIndex);
	if(SecBuf == NULL)
		return -1;
	if(ReadSec(fp->Drive,SecIndex) != RETURN_OK)
		return -1;
	FirstSize=(DiskInfo->BytsPerSec-j)<Size?(DiskInfo->BytsPerSec-j):Size;
	for(k=0;k<FirstSize;k++)
	{
		SecBuf[j]=*Buf++;
		j++;
	}
	WriteSec(fp->Drive,SecIndex);
	CloseSec(fp->Drive,SecIndex);
	RealSize=RealSize-FirstSize;
	fp->Offset=fp->Offset+FirstSize;
	if(fp->Offset>fp->FileSize)
		fp->FileSize=fp->Offset;
	//�����м������
	for(;RealSize>=DiskInfo->BytsPerSec;RealSize-=DiskInfo->BytsPerSec)
	{
		i++;
		if(i>=DiskInfo->SecPerClus)
		{
			i=0;
			if(fp->Offset<fp->FileSize)
				fp->Clus=FATGetNextClus(fp->Drive,fp->Clus);
			else
			{
				k=FATAddClus(fp->Drive,fp->Clus);
				if(k>=BAD_CLUS)
					return (Size-RealSize);
				fp->Clus=k;
			}
		}		
		SecIndex=(fp->Clus-2)*DiskInfo->SecPerClus+DiskInfo->DataStartSec+i;
		if((SecBuf=OpenSec(fp->Drive,SecIndex))==NULL)
			return (Size-RealSize);
		if((ReadSec(fp->Drive,SecIndex))!=RETURN_OK)
			return (Size-RealSize);
		for(k=0;k<DiskInfo->BytsPerSec;k+=4)
		{
			SecBuf[k]=Buf[0];
			SecBuf[k+1]=Buf[1];
			SecBuf[k+2]=Buf[2];
			SecBuf[k+3]=Buf[3];
			Buf+=4;
				
		}
		WriteSec(fp->Drive,SecIndex);
		CloseSec(fp->Drive,SecIndex);
		fp->Offset=fp->Offset+DiskInfo->BytsPerSec;
		if(fp->Offset>fp->FileSize)
			fp->FileSize=fp->Offset;
	}

	//��������һ������
	if(RealSize>0)
	{
		i++;
		if(i>=DiskInfo->SecPerClus)
		{
			i=0;
			if(fp->Offset<fp->FileSize)
				fp->Clus=FATGetNextClus(fp->Drive,fp->Clus);
			else
			{
				k=FATAddClus(fp->Drive,fp->Clus);
				if(k>=BAD_CLUS)
					return (Size-RealSize);
				fp->Clus=k;
			}
		}		
		SecIndex=(fp->Clus-2)*DiskInfo->SecPerClus+DiskInfo->DataStartSec+i;
		if((SecBuf=OpenSec(fp->Drive,SecIndex))==NULL)
			return (Size-RealSize);
		if((ReadSec(fp->Drive,SecIndex))!=RETURN_OK)
			return (Size-RealSize);
		for(k=0;k<RealSize;k++)
		{
			SecBuf[k]=*Buf++;
				
		}
		WriteSec(fp->Drive,SecIndex);
		CloseSec(fp->Drive,SecIndex);
		fp->Offset=fp->Offset+RealSize;
		RealSize=0;
		if(fp->Offset>fp->FileSize)
			fp->FileSize=fp->Offset;		
	}
	return (Size-RealSize);
}


/*********************************************************************************************************
** ��������: FileCloseAll
** ��������: �ر����д򿪵��ļ�
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: FileInfo
** ����ģ��: AllCacheWriteBack
********************************************************************************************************/
        void FileCloseAll(void)
{
    acoral_u32 i;

    for (i = 0; i < MAX_OPEN_FILES; i++)
    {
        FileClose(i);
    }
    AllCacheWriteBack();
}

/*********************************************************************************************************
** ��������: FileEof
** ��������: �ж��ļ��Ƿ񵽶�\д���ļ�β
**
** �䡡��: Handle:�ļ����
**
** �䡡��: 0:��
**        1:�� 
** ȫ�ֱ���: FileInfo
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 FileEof(HANDLE Handle)
{
    if (Handle < MAX_OPEN_FILES)
    if (FileInfo[Handle].Offset < FileInfo[Handle].FileSize)
    {
        return FALSE;
    }
    return TRUE;
}

/*********************************************************************************************************
** ��������: FileSeek
** ��������: �ƶ��ļ���\дλ��
**
** �䡡��: Handle:�ļ����
**        offset:�ƶ�ƫ����
**        Whence:�ƶ�ģʽSEEK_SET:���ļ�ͷ����SEEK_CUR:�ӵ�ǰλ�ü���SEEK_END:���ļ�β����
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u32 FileSeek(HANDLE Handle, acoral_32 offset, acoral_u8 Whence)
{
    acoral_u32 Rt;
    acoral_u32 i, Clus;
    MY_FILE *fp;
    Disk_Info * DiskInfo;
    
    Rt = PARAMETER_ERR;
    fp = FileInfo + Handle;
    if (Handle >= 0 && Handle < MAX_OPEN_FILES)     /* Handle�Ƿ���Ч */
    if (fp->Flags  != 0)                            /* ��Ӧ�Ĵ��ļ���Ϣ���Ƿ���ʹ�� */
    {
        Rt = RETURN_OK;
        switch (Whence)
        {
            case SEEK_END:                          /* ���ļ�β���� */
                fp->Offset = fp->FileSize + offset;
//                offset = -offset;
                break;
            case SEEK_SET:
                fp->Offset = offset;
                break;
            case SEEK_CUR:                          /* �ӵ�ǰλ�ü��� */
                i = fp->Offset + offset;
                break;
            default:
                Rt = PARAMETER_ERR;
                break;
        }
        if (Rt == RETURN_OK)
        {
            if (fp->Offset > fp->FileSize)
	fp->Offset=fp->FileSize;
           if(fp->Offset<0)
    	fp->Offset=0;
            /* �ı䵱ǰ�غ� */
            Rt = NOT_FIND_DISK;
            DiskInfo = GetDiskInfo(fp->Drive);
            if (DiskInfo != NULL)
            {
                Rt = RETURN_OK;
                i = fp->Offset / (DiskInfo->BytsPerSec * DiskInfo->SecPerClus);
                Clus = fp->FstClus;
                for (; i != 0; i--)
                {
                    Clus = FATGetNextClus(fp->Drive, Clus);
                    if (Clus >= BAD_CLUS)
                    {
                        Rt = FAT_ERR;
                        break;
                    }
                }
                fp->Clus = Clus;
            }
        }
    }
    if(Rt!=RETURN_OK)
    	return -1;
    else
    	return fp->Offset;
}
/*********************************************************************************************************
**                            FS��ʹ�õĺ��� 
********************************************************************************************************/

 acoral_char  *strupr(acoral_char *Str)					
{    acoral_char *cp;
     cp = Str;
    while (*cp != 0)
    {   if (*cp >= 'a' && *cp <= 'z' )
            *cp -=  'a' - 'A';
       cp++;
    }
    return Str;
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
