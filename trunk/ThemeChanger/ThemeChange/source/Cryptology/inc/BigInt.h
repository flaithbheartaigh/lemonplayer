/*****************************************************************
���������ͷ�ļ���BigInt.h
���ߣ�afanty@vip.sina.com
�汾��1.2 (2003.5.13)
˵����������MFC��1024λRSA����
*****************************************************************/

//��������1120λ�������ƣ����м���
#ifndef BI_MAXLEN

#include <e32std.h>

#define BI_MAXLEN 35
#define DEC 10
#define HEX 16

class CBigInt
{
public:
//������0x100000000�����µĳ���    
    unsigned m_nLength;
//�������¼������0x100000000������ÿһλ��ֵ
    unsigned long m_ulValue[BI_MAXLEN];

    CBigInt();
    ~CBigInt();

/*****************************************************************
��������������
Mov����ֵ���㣬�ɸ�ֵΪ��������ͨ������������Ϊ�������=��
Cmp���Ƚ����㣬������Ϊ�������==������!=������>=������<=����
Add���ӣ��������������������ͨ�����ĺͣ�������Ϊ�������+��
Sub�������������������������ͨ�����Ĳ������Ϊ�������-��
Mul���ˣ��������������������ͨ�����Ļ���������Ϊ�������*��
Div�������������������������ͨ�������̣�������Ϊ�������/��
Mod��ģ���������������������ͨ������ģ��������Ϊ�������%��
*****************************************************************/
    void Mov(unsigned __int64 A);
    void Mov(const CBigInt& A);
    CBigInt Add(const CBigInt& A);
    CBigInt Sub(const CBigInt& A);
    CBigInt Mul(CBigInt& A);
    CBigInt Div(CBigInt& A);
    CBigInt Mod(CBigInt& A);
    CBigInt Add(unsigned long A);
    CBigInt Sub(unsigned long A);
    CBigInt Mul(unsigned long A);
    CBigInt Div(unsigned long A);
    unsigned long Mod(unsigned long A); 
    int Cmp(const CBigInt& A); 

/*****************************************************************
�������
Get�����ַ�����10���ƻ�16���Ƹ�ʽ���뵽����
Put����������10���ƻ�16���Ƹ�ʽ������ַ���
*****************************************************************/
    void Get(const TDesC8& str, unsigned int system=HEX);
    void Put(TDes8& str, unsigned int system=HEX);

/*****************************************************************
RSA�������
Rab�����������㷨������������
Euc��ŷ������㷨���ͬ�෽��
RsaTrans������ƽ���㷨������ģ����
GetPrime������ָ�����ȵ����������
*****************************************************************/
//    int Rab();
    CBigInt Euc(CBigInt& A);
    CBigInt RsaTrans(CBigInt& A, CBigInt& B);
//    void GetPrime(int bits);
};
#endif
