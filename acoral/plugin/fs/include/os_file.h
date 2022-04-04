#ifndef OS_FILE_H
#define OS_FILE_H
#define O_RDONLY	0x4
#define O_WRONLY	0x2
#define O_RDWR		0x6

#ifndef IN_OSFILE

extern void acoral_fs_init(void);

extern acoral_32 acoral_unlink(acoral_char *pathname);

extern acoral_32 acoral_open(acoral_char *pathname,acoral_32 oflag);

extern acoral_32 acoral_close(acoral_32 fd);

//extern uint8 OSFileGetCh(uint8 *Ch, HANDLE Handle);
/*********************************************************************************************************
** ��������: OSFileGetCh
** ��������: ���ļ���һ���ֽ�
**
** �䡡��: Ch:���ض���������
**        Handle:�ļ����
** �䡡��: RETURN_OK:�ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵�� 
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
********************************************************************************************************/

extern acoral_32 acoral_read(acoral_32 fd,void *buf,acoral_u32 nbytes);

//extern uint8 OSFilePutCh(uint8 Ch, HANDLE Handle);
/*********************************************************************************************************
** ��������: OSFilePutCh
** ��������: дһ���ֽڵ��ļ�
**
** �䡡��: Ch:Ҫд������
**        Handle:�ļ����
** �䡡��: RETURN_OK:�ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵�� 
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
********************************************************************************************************/

extern acoral_32 acoral_write(acoral_32 fd,const void *buf,acoral_u32 nbytes);

extern acoral_32 acoral_closeall(void);

//extern uint8 OSFileEof(HANDLE Handle);
/*********************************************************************************************************
** ��������: OSFileEof
** ��������: �ж��ļ��Ƿ񵽶�\д���ļ�β
**
** �䡡��: Handle:�ļ����
**
** �䡡��: 0:��
**        1:�� 
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
**
********************************************************************************************************/

extern acoral_u32 acoral_lseek(acoral_32 fd,acoral_32 offset,acoral_u8 whence);

extern acoral_32 acoral_mkdir(acoral_char *pathname,acoral_u8 mode);

extern acoral_32 acoral_rmdir(acoral_char *pathname);

extern acoral_32 acoral_chdir(acoral_char *pathname);


//extern uint8 OSChangeDrive(char *Drive);
/*********************************************************************************************************
** ��������: OSChangeDrive
** ��������: �ı䵱ǰ�߼���
**
** �䡡��: Drive:�߼��̷��ַ���
**        
** �䡡��: RETURN_OK:�ɹ�
**        NOT_FIND_DISK:�߼��̲�����
**        PARAMETER_ERR:�Ƿ�����
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
**
** ������: ������
** �ա���: 2003��9��8��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

//extern uint8 OSGetFDTInfo(FDT *Rt,uint8 Drive, uint32 ClusIndex, uint32 Index);
/*********************************************************************************************************
** ��������: OSGetFDTInfo
** ��������: ��ȡָ��Ŀ¼ָ���ļ���Ŀ¼����Ϣ
**
** �䡡��: Rt���洢������Ϣ��ָ��
**        Drive����������
**        ClusIndex��Ŀ¼�״غ�
**        Index���ļ���Ŀ¼����FDT�е�λ��
** �䡡��: RETURN_OK���ɹ�
**        �����ο�fat.h�й��ڷ���ֵ��˵��
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
**
********************************************************************************************************/

extern acoral_32 acoral_mount(acoral_char *source,const char *target,
					   const acoral_char *filesystemtype,acoral_u32 mountflags,
					   const void *data);

extern acoral_32 acoral_umount(const char *target);
/*********************************************************************************************************
** ��������: OSRemoveFileDriver
** ��������: ɾ��һ���ײ���������
**
** �䡡��: Drive:�߼���������
**
** �䡡��: ��
**         
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
**
********************************************************************************************************/

extern void acoral_flush(void);
//extern void OSAllCacheWriteBack(void);
/*********************************************************************************************************
** ��������: OSAllCacheWriteBack
** ��������: �������Ѹı������д���߼���
**
** �䡡��: ��
**
** �䡡��: NOT_RUN:û��ִ��
**        RETURN_OK:ִ�гɹ�
**         
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
**
********************************************************************************************************/

//extern void OSFileTask(void *pdata);
/*********************************************************************************************************
** ��������: OSFileTask
** ��������: �ļ�ϵͳ��������
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: 
** ����ģ��: OSQPost,OSTaskSuspend
**
********************************************************************************************************/
#endif

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
#endif
