#define IN_RWSEC
#include "../include/fs.h"
#include <mem.h>
//Disk_cache DiskCache[MAX_DISK_CACHES];      /* ����cache */
Disk_cache* HashTable[CACHE_HASH_SIZE]; //hash���ô���������ȡģ������
Disk_cache* FreeList;  //��������ͷ����ͷΪ������δʹ�õĻ�����
Disk_cache* FreeListTail;  //��������β��Ϊ�ո�ʹ�õĻ�����
acoral_u8 CacheNum;  //��ǰ����������Ŀ

/*********************************************************************************************************
** ��������: CacheInit
** ��������: ��ʼ������cache
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: ��
********************************************************************************************************/
        void CacheInit(void)
{
    acoral_u16 i;
    for(i=0;i<CACHE_HASH_SIZE;i++)
    	HashTable[i]=NULL;
    FreeList=NULL;
    FreeListTail = NULL;
    CacheNum = 0;
}


/*********************************************************************************************************
** ��������: CloseSec
** ��������: ����ָ��cache�������л����ڴ棩
**
** �䡡��: Drive���߼���������
**        Index�������������
** �䡡��: ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: ��
********************************************************************************************************/
        void CloseSec(acoral_u8 Drive, acoral_u32 Index)
{
    Drive = Drive;
    Index = Index;
}

/*********************************************************************************************************
** ��������: CacheWriteBack2
** ��������: ��ָ������д���߼���
**
** �䡡��: Index��cache����
**
** �䡡��: ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: GetDiskInfo
********************************************************************************************************/
        void CacheWriteBack2(Disk_cache* pcache)
{
    Disk_RW_Parameter Pa;
    Disk_Info * Disk;

    Disk = GetDiskInfo(pcache->Drive);     // ��ȡ�߼�����Ϣ
    if (Disk != NULL)
    if (Disk->DiakCommand != NULL)
    {
        pcache->Flag &= ~CACHE_WRITED;     // cache ������Ҫ��д
        /* ���ݲ��� */
        Pa.Drive = pcache->Drive;               
        Pa.SectorIndex = pcache->SecIndex;
        Pa.RsvdForLow = Disk->RsvdForLow;
        Pa.Buf = pcache->buf;
        
        Disk->DiakCommand(DISK_WRITE_SECTOR, &Pa);  /* ���õײ�����д���� */ 
    }
}

/*********************************************************************************************************
** ��������: CacheWriteBack
** ��������: ��ָ��cacheд���߼���
**
** �䡡��: Drive���߼���������
**        Index�������������
** �䡡��: ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: CacheWriteBack2
********************************************************************************************************/
       void CacheWriteBack(acoral_u8 Drive, acoral_u32 Index)
{
    Disk_cache* pcache;
    acoral_u8  hashindex = Index % CACHE_HASH_SIZE;
    for(pcache = HashTable[hashindex]; pcache != NULL; pcache = pcache->NextHash)
    {
    	if(pcache->Drive == Drive)
    	if(pcache->SecIndex == Index)
    	{
    		if((pcache->Flag & CACHE_WRITED) != 0)
    		{
    			CacheWriteBack2(pcache);
    		}
    		break;
    	}
    }
}

/*********************************************************************************************************
** ��������: AllCacheWriteBack
** ��������: �������Ѹı������д���߼���
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: CacheWriteBack2
********************************************************************************************************/
       void AllCacheWriteBack(void)
{
    Disk_cache* pcache;

    for (pcache = FreeList; pcache != NULL; pcache = pcache->NextFreeList)
    {
        if ((pcache->Flag & CACHE_WRITED) != 0)
        {
            CacheWriteBack2(pcache);
        }
    }
}

/*********************************************************************************************************
** ��������: GetCache
** ��������: ��ȡһ��cache
**
** �䡡��: ��
**
** �䡡��: cache����
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: ��
********************************************************************************************************/
        Disk_cache* GetCache(void)
{
	Disk_cache* pcache;
	
	//С����󻺳�����С��������»�����
	if(CacheNum < MAX_DISK_CACHES)
	{
		pcache = (Disk_cache *)acoral_malloc(sizeof(Disk_cache));
		if(pcache == NULL)
			return NULL;
		pcache->NextHash=NULL;
		pcache->FrontHash=NULL;
		pcache->NextFreeList=NULL;
		CacheNum++;
		if(FreeList == NULL)
		{
			FreeList = FreeListTail = pcache;
		}
		else //�·���Ļ�����������������ĩβ
		{
			FreeListTail->NextFreeList=pcache;
			FreeListTail=pcache;
		}
	}
	//����ժ�����л����������ͷ��㣬�����뵽β�ڵ㣬���Ӷ�Ӧ��hash����ɾ��
	else
	{
		if(FreeList != FreeListTail)
		{
			pcache=FreeList;
			FreeList=FreeList->NextFreeList;
			FreeListTail->NextFreeList=pcache;
			FreeListTail=pcache;
			FreeListTail->NextFreeList=NULL;
		}
		
		if(pcache->FrontHash == NULL)
		{
			if(pcache->NextHash != NULL)
				pcache->NextHash->FrontHash=NULL;
			HashTable[pcache->SecIndex % CACHE_HASH_SIZE] = pcache->NextHash;
		}
		else
		{
			if(pcache->NextHash != NULL)
				pcache->NextHash->FrontHash = pcache->FrontHash;
			pcache->FrontHash->NextHash = pcache->NextHash;
		}
		if(pcache->Drive != EMPTY_DRIVE)
		if((pcache->Flag & CACHE_WRITED) != 0)
		{
			CacheWriteBack2(pcache);
		}
	}
	return pcache;
}

/*********************************************************************************************************
** ��������: OpenSec
** ��������: Ϊ�߼����ϵ�һ��������һ��cache������
**
** �䡡��: Drive�����̺�
**        Index��������
** �䡡��: ָ��ָ���������ݵ�ָ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: ��
********************************************************************************************************/
        acoral_u8 *OpenSec(acoral_u8 Drive, acoral_u32 Index)
{
    Disk_cache *pcache;
    acoral_u8 *Rt;
    Disk_Info *Disk;
   	acoral_u8 hashindex;
   	acoral_u16 i;
   	hashindex = Index % CACHE_HASH_SIZE;

    /* �������Ƿ��Ѿ����� */
    Rt = NULL;
    for (pcache = HashTable[hashindex]; pcache != NULL; pcache = pcache->NextHash)
    {
        if (pcache->Drive == Drive )
        if (pcache->SecIndex == Index)
        {
            Rt = pcache->buf;
            break;
        }
    }
    
    /* Rt == NULL��δ���� */
    if (Rt == NULL)
    {
        Disk = GetDiskInfo(Drive);
        if (Disk != NULL)
        if (Disk->SecPerDisk > Index)
        {
            pcache = GetCache();                     /* ��ȡcache */
            if (pcache != NULL)
            {
                /* ��ʼ��cache  */
                pcache->Drive = Drive;     
                pcache->Flag = 0;
                pcache->SecIndex = Index;
                if(HashTable[hashindex] == NULL)
                {
                	pcache->FrontHash = NULL;
                	pcache->NextHash = NULL;
                	HashTable[hashindex] = pcache;
                }
                else
                {
                	pcache->FrontHash = NULL;
                	pcache->NextHash = HashTable[hashindex];
                	HashTable[hashindex]->FrontHash = pcache;
                	HashTable[hashindex] = pcache;
                }
                Rt = pcache->buf;
                for (i = 0; i < Disk->BytsPerSec; i++)
                {
                    Rt[i] = 0;
                }
            }
        }
    }
    return Rt;
}

acoral_u8 ReadSuperSec(acoral_u8 Drive,acoral_u8 *buf)
{
	Disk_RW_Parameter Pa;
	Disk_Info *Disk;
        Disk = GetDiskInfo(Drive);    
	Pa.Drive=Drive;
	Pa.Buf=buf;
        if(Disk->DiakCommand(DISK_READ_SUPER_SECTOR, &Pa) == DISK_READ_OK)
        {
                return RETURN_OK;
	}
	return SECTOR_READ_ERR;
}

/*********************************************************************************************************
** ��������: ReadSec
** ��������: ���߼��̶�����
**
** �䡡��: Disk���߼�����Ϣ
**        Index��������
** �䡡��: TRUE:�ɹ�
**         FALSE:ʧ��
** ȫ�ֱ���: DiskCache
** ����ģ��: GetDiskInfo
********************************************************************************************************/
        acoral_u8 ReadSec(acoral_u8 Drive, acoral_u32 Index)
{
    Disk_cache *pcache;
    Disk_RW_Parameter Pa;
    Disk_Info *Disk;
    acoral_u8 Rt;
    acoral_u8 hashindex = Index % CACHE_HASH_SIZE;
    
    for (pcache = HashTable[hashindex]; pcache != NULL; pcache = pcache->NextHash)
    {
        if (pcache->Drive == Drive)
        if (pcache->SecIndex == Index)
        {
            if ((pcache->Flag & CACHE_READED) != 0)
            {
                return RETURN_OK;
            }
            break;
        }
    }
    Rt = SECTOR_NOT_IN_CACHE;
    if (pcache != NULL)
    {
        Disk = GetDiskInfo(Drive);    

        pcache->Flag |= CACHE_READED;

        /* �Ӵ��̶�ȡ�������� */
        Pa.Drive = Drive;
        Pa.SectorIndex = Index;
        Pa.RsvdForLow = Disk->RsvdForLow;
        Pa.Buf = pcache->buf;
        Rt = NOT_FIND_DISK;
        if (Disk->DiakCommand != NULL)
        {

            Rt = SECTOR_READ_ERR;
            if (Disk->DiakCommand(DISK_READ_SECTOR, &Pa) == DISK_READ_OK)
            {
                return RETURN_OK;
            }
        }
    }
    return Rt;
}

/*********************************************************************************************************
** ��������: WriteSec
** ��������: ˵��ָ���߼��̵�ָ��һ����������д
**
** �䡡��: Disk���߼�����Ϣ
**        Index��������
** �䡡��: ��
**         
** ȫ�ֱ���: DiskCache
** ����ģ��: ��
********************************************************************************************************/
        void WriteSec(acoral_u8 Drive, acoral_u32 Index)
{
    Disk_cache *pcache;
    acoral_u8 hashindex = Index % CACHE_HASH_SIZE;
    
    for (pcache = HashTable[hashindex]; pcache != NULL; pcache = pcache->NextHash)
    {
        if (pcache->Drive == Drive)
        if (pcache->SecIndex == Index)
        {
            pcache->Flag |= (CACHE_WRITED | CACHE_READED);
            break;
        }
    }
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
