#ifndef FS_CMD_H
#define FS_CMD_H
extern acoral_u16 FsCommand(acoral_u8 Command, void *Parameter);
/*********************************************************************************************************
** ��������: SDMMCCammand
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
#endif
