#pragma once

/***************************************************************
RC4函数(加密/解密):其实,RC4只有加密,将密文再加密一次,就是解密了
GetKey函数:随机字符串产生器,大多数加密算法都有一个随机密码产生器
ByteToHex函数:把字节码转为十六进制码,一个字节两个十六进制
HexToByte函数:把十六进制字符串,转为字节码
Encrypt函数:把字符串经RC4加密后,再把密文转为十六进制字符串返回
Decrypt函数:直接密码十六进制字符串密文,再解密,返回字符串明文
***************************************************************/

#include <string>

#define BOX_LEN 256


class RC4EncryptTool
{
public:

	static std::string Encrypt(const char* szSource, const char* szPassWord);//加密
																			 
	static std::string Decrypt(const char* szSource, const char* szPassWord);//解密

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
