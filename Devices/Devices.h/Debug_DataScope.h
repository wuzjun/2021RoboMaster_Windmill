

#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
#include "main.h"
 
extern unsigned char DataScope_OutPut_Buffer[42];	   //������֡���ݻ�����



void Debug_show(int ChannelAmount);
void Debug_addData(float Data,unsigned char Channel);    // дͨ�������� ������֡���ݻ�����

unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // ����֡�������ɺ��� 
 
 
#endif 



