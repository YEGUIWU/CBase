#ifndef _YGW_TYPE_8848_
#define _YGW_TYPE_8848_
#include "link_list.h"

//����ʽ����
typedef struct Monomial
{
	double coefficient;	//ϵ��
	double exponent;	//ָ��
}Monomial;

typedef Monomial* PtrToMonmial;

//����ʽ����
typedef struct Polynomial
{
	List monmials;		//��δ֪������
	double constant;	//������
}Polynomial;


//���쵥��ʽ
PtrToMonmial MakeMonomial(double coefficient,double exponent);
//���ٵ���ʽ
void DestroyMonmial(PtrToMonmial p);
//��ʼ������ʽ
Polynomial InitPolynomial();
//���ٶ���ʽ
void DestoryPolynomial(Polynomial poly);
//׷�ӳ�����
Polynomial PushConstant(Polynomial poly, const double constant);
//׷�ӵ���ʽ
Polynomial PushMonmial(PtrToMonmial pMonm, Polynomial poly);
//��ӡ����ʽ
void PrintPolynomial(const Polynomial poly);
//�������ʽ
void SortPolynomial(Polynomial poly);
#endif // !_YGW_TYPE_8848_