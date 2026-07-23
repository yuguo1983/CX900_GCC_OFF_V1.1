#ifndef _MALLOC_H
#define _MALLOC_H
#include "gd32f303e_eval.h"\



//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ڴ���� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#ifndef NULL
#define NULL 0
#endif

//���������ڴ��
#define SRAMIN 	0  //�ڲ��ڴ��
#define SRAMEX 	1  //�ⲿ�ڴ��
#define SRAMCCM 2  //CCM�ڴ��(�˲���SRAM����CPU���Է��ʣ�����)

#define SRAMBANK  3 //����֧�ֵ�SRAM����


//mem1�ڴ�����趨,mem1��ȫ�����ڲ�SRAM����
#define MEM1_BLOCK_SIZE	32  			//�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE		2*1024 	//�������ڴ� 40k
#define MEM1_ALLOC_TABLE_SIZE MEM1_MAX_SIZE/MEM1_BLOCK_SIZE  //�ڴ����С

//mem2�ڴ�����趨,mem2�����ⲿSRAM����
#define MEM2_BLOCK_SIZE	32  			//�ڴ���СΪ32�ֽ�
#define MEM2_MAX_SIZE		800*1024 	//�������ڴ� 200k
#define MEM2_ALLOC_TABLE_SIZE MEM2_MAX_SIZE/MEM2_BLOCK_SIZE  //�ڴ����С

//mem3�ڴ�����趨,mem3����CCM,���ڹ���CCM(�ر�ע��,�ⲿ��SRAM,��CPU���Է���)
#define MEM3_BLOCK_SIZE	32  			//�ڴ���СΪ32�ֽ�
#define MEM3_MAX_SIZE		60*1024 	//�������ڴ� 60k
#define MEM3_ALLOC_TABLE_SIZE MEM3_MAX_SIZE/MEM3_BLOCK_SIZE  //�ڴ����С

//�ڴ����������
struct _m_mallco_dev
{
	void (*init)(uint8_t);  		//��ʼ��
	uint8_t (*perused)(uint8_t); 		//�ڴ�ʹ����
	uint8_t *membase[SRAMBANK]; //�ڴ��,����SRAMBANK��������ڴ�
	uint16_t *memmap[SRAMBANK];  //�ڴ�״̬��
	uint8_t memrdy[SRAMBANK];   //�ڴ�����Ƿ����
};
extern struct _m_mallco_dev mallco_dev;  //��malloc.c���涨��

void mymemset(void *s,uint8_t c,uint32_t count);	 //�����ڴ�
void mymemcpy(void *des,void *src,uint32_t n);//�����ڴ�     
void mem_init(uint8_t memx);					 //�ڴ������ʼ������(��/�ڲ�����)
uint32_t mem_malloc(uint8_t memx,uint32_t size);		 //�ڴ����(�ڲ�����)
uint8_t mem_free(uint8_t memx,uint32_t offset);		 //�ڴ��ͷ�(�ڲ�����)
uint8_t mem_perused(uint8_t memx);				 //����ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void myfree(uint8_t memx,void *ptr);  			//�ڴ��ͷ�(�ⲿ����)
void *mymalloc(uint8_t memx,uint32_t size);			//�ڴ����(�ⲿ����)
void *myrealloc(uint8_t memx,void *ptr,uint32_t size);//���·����ڴ�(�ⲿ����)


uint8_t FATFS_Init(void);
#endif


