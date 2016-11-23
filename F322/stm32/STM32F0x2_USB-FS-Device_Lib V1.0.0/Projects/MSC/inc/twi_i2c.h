#ifndef __TWI_I2C_H
#define __TWI_I2C_H

#define I2C_M_RD		0x0001
#define I2C_M_TEN		0x0010

#define I2C_SDA_OUTPUT		0x0000
#define I2C_SDA_INPUT		0x0001

#define u8 unsigned char 
#define u16 unsigned short int
#define u32 unsigned int 
#define vu32 unsigned int 
	


void TWI_Initialize();

u8 SyncCommandWrite(
		u8 Commandword,		//����
		u8 addr1,			//��ַ1
		u8 addr2,			//��ַ2
		u8 num,				//Ҫ���͵����ݳ���
		u8 *pdata);			//Ҫ���͵����ݻ�����


u8 SyncCommandRead(
		u8 Commandword,		//����
		u8 addr1,			//��ַ1
		u8 addr2,			//��ַ2
		u8 num,				//Ҫ���յ����ݳ���
		u8 *pdata);			//Ҫ���յ����ݻ�����


#endif