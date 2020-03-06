#include "calc.h"
#include <math.h>

_Bool static inline IsEqual(const double db1, const double db2)
{
	return fabs(db1 - db2) < 1e-14;
}

//���쵥��ʽ
PtrToMonmial MakeMonomial(
	double coefficient,
	double exponent)
{
	PtrToMonmial p = (PtrToMonmial)malloc(sizeof(Monomial));
	if (p)
	{
		p->coefficient = coefficient;
		p->exponent = exponent;
	}
	else
	{
		exit(1);
	}
	return p;
}

//���ٵ���ʽ
void DestroyMonmial(PtrToMonmial p)
{
	free(p);
}
//��ʼ������ʽ
Polynomial InitPolynomial()
{
	return (Polynomial) { NULL, 0 };
}
//���ٶ���ʽ
void DestoryPolynomial(Polynomial poly)
{
	DestroyList(poly.monmials);
}



// g_Number SetFunc Func  �������ڸ���PushMonial
static double g_Number = 0.0;			//g_Number���ڱ���ָ��ָ��
void inline SetFunc(PtrToMonmial pMonm)	//�趨ָ��ָ��
{
	g_Number = pMonm->exponent;
}
//�жϸõ���ʽ��ָ���Ƿ����g_Number
_Bool static Func(PtrToMonmial pMonm)
{
	if(IsEqual(pMonm->exponent, g_Number))
		return true;
	else
		return false;
}

//׷�ӵ���ʽ
Polynomial PushMonmial(PtrToMonmial pMonm, Polynomial poly)
{
	if (IsEqual(0, pMonm->coefficient)) //���ϵ��Ϊ0�Ͳ��üӽ�ȥ��
		return poly;
	if (IsEqual(0, pMonm->exponent))	//���ָ��Ϊ0�����ǳ�������
	{
		poly.constant += pMonm->coefficient;
		return poly;
	}

	SetFunc(pMonm);
	//���Ҷ���ʽ���Ƿ���ָ����ͬ����
	ListPosition pFind = FindIf(Func, poly.monmials);
	if (pFind)	//����ҵ�����
	{
		PtrToMonmial pTmp = pFind->ELement;
		pTmp->coefficient += pMonm->coefficient;
		//�����Ӻ�ϵ��Ϊ0��Ҳ��ɾ�������ö���ɾ����
		//ϵ��Ϊ0���Ͳ���ӡ
	}
	else
	{
		//û�ҵ���ֱ��׷��
	}
	{
		poly.monmials = PushBack(pMonm, poly.monmials);
	}
	return poly;
}

//׷�ӳ�����
Polynomial PushConstant(Polynomial poly, const double constant)
{
	return (Polynomial) { poly.monmials, poly.constant + constant };
}


//�������ʽ
int static MonmialCompare(PtrToMonmial p1, PtrToMonmial p2)
{
	double res = p1->exponent - p2->exponent;
	if (res > 0) return 1;
	else if (res < 0) return -1;
	else return 0;
}
void SortPolynomial(Polynomial poly)
{
	SortList(poly.monmials, NULL, MonmialCompare);
}

//----------------------------------------
//	��ӡ����ʽ���ĺ���
void static inline PrintMonmialBase(ListPosition pos)
{
	PtrToMonmial pMonm = pos->ELement;
	if (IsEqual(0, pMonm->coefficient))
		return;

	if (IsEqual(1, pMonm->coefficient))
		printf("X");
	else if (IsEqual(-1, pMonm->coefficient))
		printf("-X");
	else
		printf("%.1fX", pMonm->coefficient);

	if (!IsEqual(1, pMonm->exponent))
		printf("^%.1f", pMonm->exponent);
	putchar(' ');
}
//-----------------------------------------
// ��ӡ����ʽ�ĵ�һ���Ժ����
void static PrintMonmial(ListPosition pos)
{
	if (!pos) return;
	PtrToMonmial pMonm = pos->ELement;
	if (pMonm->coefficient > 0)
		printf("+ ");
	PrintMonmialBase(pos);
}
//----------------------------------------
// ��ӡ����ʽ��������
void PrintPolynomial(const Polynomial poly)
{
	PtrToListNode head = HeadOfList(poly.monmials);
	PrintMonmialBase(head);


	if (head->Next)
	{
		DisplayList(head->Next, PrintMonmial);
	}
	if (IsEqual(0, poly.constant))
	{
		printf("+ %.1f", poly.constant);
	}
	printf("\n");
}