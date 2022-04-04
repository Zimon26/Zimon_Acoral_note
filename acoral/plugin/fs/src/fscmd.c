#include "../include/fs.h"

/*********************************************************************************************************
** ��������: FSCommand
** ��������: �ײ������������ϲ�Ľӿڳ���
**
** �䡡��: Cammand��DISK_INIT�����������ʼ��
**                 DISK_CLOSE���ر����������Ƴ���������                 
**                 DISK_CREATE_BOOT_SECTOR���ؽ���������
**                 DISK_READ_SECTOR��������
**                 DISK_WRITE_SECTOR��д����
**        Parameter��ʣ�����
** �䡡��: DISK_READ_OK�����������
**        DISK_READ_NOT_OK��������ʧ��
**        DISK_WRITE_OK��д�������
**        DISK_WRITE_NOT_OK��д����ʧ��
**        DISK_INIT_OK����ʼ�����
**        DISK_INIT_NOT_OK����ʼ��ʧ��
**        BAD_DISK_COMMAND����Ч������
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
        acoral_u16 FsCommand(acoral_u8 Cammand, void *Parameter)
{
    acoral_u16 rt;
    acoral_id dev_id;
    acoral_u8 drive;
    Disk_RW_Parameter * Dp;
    Disk_Info *DiskInfo1;
    
    
    Dp = (Disk_RW_Parameter *)Parameter;
    drive=Dp->Drive;
    switch (Cammand)
    {
        case DISK_INIT:										/*�豸��ʼ��*/
            rt = DISK_INIT_NOT_OK;
        	DiskInfo1 = &DiskInfo[drive];
        	if (DiskInfo1 != NULL)
        	{
				DiskInfo1->DiakCommand = FsCommand;
				dev_id=acoral_dev_open((acoral_char *)(Dp->Buf));
				if(dev_id!=ACORAL_DEV_ERR_ID)
				{
					DiskInfo1->DevId= dev_id;
					/*if(acoral_dev_config(dev_id,GET_DISK_INFO,NULL,0)==0)
					{
						if(SD_Initialize()==0);
							return DISK_INIT_OK;
					}
					else
						acoral_dev_close(dev_id);*/
					rt = DISK_INIT_OK;
				}
		/*	DiskInfo1->RsvdForLow = SDGetBlockSize();
			if(SD_Initialize()==SD_NO_ERR);*/
					
        	}
		
            break;
        	 
        case DISK_CLOSE:
			acoral_dev_close(DiskInfo[drive].DevId);
            break;
        case DISK_READ_SUPER_SECTOR:								/*������������*/
	    	rt = DISK_READ_OK;
            if(acoral_dev_read(DiskInfo[drive].DevId,(void *)Dp->Buf,512,0,0)!=0)
            { 
                rt = DISK_READ_NOT_OK;
            }
            break;

        case DISK_READ_SECTOR:									/*������*/
            rt = DISK_READ_OK;
            if(acoral_dev_read(
            	DiskInfo[drive].DevId,
            	(void *)Dp->Buf,
            	DiskInfo[drive].BytsPerSec,
            	Dp->SectorIndex*DiskInfo[drive].BytsPerSec,
            	0)!=0)
            { 
                rt = DISK_READ_NOT_OK;
            }
            break;
        case DISK_WRITE_SECTOR:									/*д����*/
            rt = DISK_WRITE_OK;
            if(acoral_dev_write(
            	DiskInfo[drive].DevId,
            	(void *)Dp->Buf,
            	DiskInfo[drive].BytsPerSec,
            	Dp->SectorIndex*DiskInfo[drive].BytsPerSec,
            	0)!=0)
            {
               rt = DISK_WRITE_NOT_OK;
            }

            break;
        default:
            rt = BAD_DISK_COMMAND;
            break;
    }
    return rt;
}


/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
