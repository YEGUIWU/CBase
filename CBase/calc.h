#ifndef _YGW_TYPE_8848_
#define _YGW_TYPE_8848_
#include "link_list.h"

//����ʽ����
typedef struct Monomial
{
	double coefficient;	//ϵ��
	double exponent;	//ָ��
}MonomialBase;

typedef MonomialBase* Monmial;

//����ʽ����
typedef struct Polynomial
{
	List monmials;		//��δ֪������
	//double constant;	//������
}Polynomial;

//�ַ�������
#define STRING_BUF_SIZE 128
typedef struct StringBase
{
	char* pBuf;
}String;

//���쵥��ʽ
Monmial MakeMonomial(double coefficient,double exponent);
//���ٵ���ʽ
void DestroyMonmial(Monmial p);
//��ʼ������ʽ
Polynomial InitPolynomial();
//���ٶ���ʽ
Polynomial DestoryPolynomial(Polynomial poly);
//׷�ӳ�����
//Polynomial PushConstant(Polynomial poly, const double constant);
//׷�ӵ���ʽ
Polynomial PushMonmial(double coefficient, double exponent, Polynomial poly);
//��ӡ����ʽ
void PrintPolynomial(const Polynomial poly);
//�������ʽ
void SortPolynomial(Polynomial poly);
//��������ʽ
Monmial CopyMonmial(Monmial pMonm);
//��������ʽ
Polynomial CopyPolynomial(Polynomial poly);
//����ʽ�˳���
Polynomial PolynomialMultiply(Polynomial polyLeft, Polynomial polyRight);
Polynomial PolynomialDivide(Polynomial polyLeft, Polynomial polyRight);
//����ʽ�Ӽ���
Polynomial PolynomialAdd(Polynomial polyLeft, Polynomial polyRight);
Polynomial PolynomialSubtract(Polynomial polyLeft, Polynomial polyRight);
//make�ַ���
String MakeString(const char* cstr);
//remake�ַ���
String ReMakeString (String str, const char* cstr);
//�����ַ���
void DestoryString(String str);
//�ַ���ת����ʽ
//���ƣ�1. �������������ַ�����ĩβ
//	2. ��ǰ�������з���
Polynomial StringToPolynomial(const char* cstr);

#endif // !_YGW_TYPE_8848_