#include "RC4EncryptTool.h"



std::string RC4EncryptTool::Encrypt( const char* szSource, const char* szPassWord )
{
	if(szSource == NULL || szPassWord == NULL)
	{
		return "";
	}

	unsigned char* ret = new unsigned char[strlen(szSource)];

	int ret_len = 0;

	if(RC4((unsigned char*)szSource, 
		strlen(szSource), 
		(unsigned char*)szPassWord, 
		strlen(szPassWord), 
		ret,
		&ret_len) == false)
	{
		delete[] ret;
		return "";
	}

	char* ret2 = ByteToHex(ret, ret_len);
	delete[] ret;

	std::string strRet = std::string(ret2);
	delete[] ret2;

	return strRet;
}

std::string RC4EncryptTool::Decrypt( const char* szSource, const char* szPassWord )
{
	if(szSource == NULL || (strlen(szSource)%2 != 0) || szPassWord == NULL)
	{
		return "";
	}

	unsigned char* src = HexToByte(szSource);

	unsigned char* ret = new unsigned char[strlen(szSource) / 2 + 1];

	int ret_len = 0;

	memset(ret, strlen(szSource) / 2 + 1, 0);

	if(RC4(src, strlen(szSource) / 2, (unsigned char*)szPassWord, strlen(szPassWord), ret, &ret_len) == false)
	{
		delete[] src;
		return "";
	}

	ret[ret_len] = '\0';

	std::string strRet = std::string((char*)ret);
	delete[] ret;
	delete[] src;

	return strRet;
}

//把字节码转为十六进制码,一个字节两个十六进制,内部为字符串分配空间,调用的地方负责释放
char* RC4EncryptTool::ByteToHex( const unsigned char* vByte, const int vLen )
{
	if(!vByte)
		return NULL;

	char* tmp = new char[vLen * 2 + 1];//一个字节两个十六进制码，最后要多一个'\0'

	int tmp2;
	for (int i=0;i<vLen;i++)
	{
		tmp2 = (int)(vByte[i])/16;
		tmp[i*2] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
		tmp2 = (int)(vByte[i])%16;
		tmp[i*2+1] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
	}

	tmp[vLen * 2] = '\0';
	return tmp;
}

//把十六进制字符串,转为字节码,每两个十六进制字符作为一个字节,内部为字符串分配空间,调用的地方负责释放
unsigned char* RC4EncryptTool::HexToByte( const char* szHex )
{
	if(!szHex)
		return NULL;

	int iLen = strlen(szHex);

	if (iLen<=0 || 0!=iLen%2) 
		return NULL;

	unsigned char* pbBuf = new unsigned char[iLen/2];//数据缓冲区

	int tmp1, tmp2;
	for (int i=0;i<iLen/2;i++)
	{
		tmp1 = (int)szHex[i*2] - (((int)szHex[i*2]>='A')?'A'-10:'0');
		tmp2 = (int)szHex[i*2+1] - (((int)szHex[i*2+1]>='A')?'A'-10:'0');
		pbBuf[i] = (tmp1*16 + tmp2);

		if((tmp1 >= 16) || (tmp2 >= 16)) 
		{
			if (pbBuf)
			{
				delete[] pbBuf;
				pbBuf = 0;
			}
			return NULL;
		}
	}

	return pbBuf;
}

bool RC4EncryptTool::RC4( const unsigned char* data, int data_len, const unsigned char* key, int key_len, unsigned char* out, int* out_len )
{
	if (data == NULL || key == NULL || out == NULL)
		return false;

	unsigned char* mBox = new unsigned char[BOX_LEN];

	if(GetKey(key, key_len, mBox) == false) 
		return false;

	int x=0;
	int y=0;

	for(int k = 0; k < data_len; k++)
	{
		x = (x + 1) % BOX_LEN;
		y = (mBox[x] + y) % BOX_LEN;
		swap_byte(&mBox[x], &mBox[y]);
		out[k] = data[k] ^ mBox[(mBox[x] + mBox[y]) % BOX_LEN];
	}

	*out_len = data_len;
	delete[] mBox;
	return true;
}

bool RC4EncryptTool::GetKey( const unsigned char* pass, int pass_len, unsigned char *out )
{
	if(pass == NULL || out == NULL)
		return false;

	for(int i = 0; i < BOX_LEN; i++)
	{
		out[i] = i;
	}

	int j = 0;
	for(int i = 0; i < BOX_LEN; i++)
	{
		j = (pass[i % pass_len] + out[i] + j) % BOX_LEN;
		swap_byte(&out[i], &out[j]); 
	}

	return true;
}

void RC4EncryptTool::swap_byte( unsigned char* a, unsigned char* b )
{
	unsigned char swapByte; 

	swapByte = *a;

	*a = *b;

	*b = swapByte;
}
