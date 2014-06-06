#pragma once

/***************************************************************
RC4����(����/����):��ʵ,RC4ֻ�м���,�������ټ���һ��,���ǽ�����
GetKey����:����ַ���������,����������㷨����һ��������������
ByteToHex����:���ֽ���תΪʮ��������,һ���ֽ�����ʮ������
HexToByte����:��ʮ�������ַ���,תΪ�ֽ���
Encrypt����:���ַ�����RC4���ܺ�,�ٰ�����תΪʮ�������ַ�������
Decrypt����:ֱ������ʮ�������ַ�������,�ٽ���,�����ַ�������
***************************************************************/

#include <string>

#define BOX_LEN 256


class RC4EncryptTool
{
public:

	static std::string Encrypt(const char* szSource, const char* szPassWord);//����
																			 
	static std::string Decrypt(const char* szSource, const char* szPassWord);//����

private:

	static char* ByteToHex(const unsigned char* vByte, const int vLen);

	static unsigned char* HexToByte(const char* szHex);

	static bool RC4(
		const unsigned char* data,
		int data_len,
		const unsigned char* key,
		int key_len,
		unsigned char* out,
		int* out_len);

	static bool GetKey(
		const unsigned char* pass,
		int pass_len,
		unsigned char *out);
	
	static void swap_byte(unsigned char* a, unsigned char* b);
};
