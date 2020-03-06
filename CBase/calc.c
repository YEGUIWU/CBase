#include "calc.h"
#include <math.h>

_Bool static inline IsEqual(const double db1, const double db2)
{
	return fabs(db1 - db2) < 1e-14;
}

//构造单项式
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

//销毁单项式
void DestroyMonmial(PtrToMonmial p)
{
	free(p);
}
//初始化多形式
Polynomial InitPolynomial()
{
	return (Polynomial) { NULL, 0 };
}
//销毁多项式
void DestoryPolynomial(Polynomial poly)
{
	DestroyList(poly.monmials);
}



// g_Number SetFunc Func  都是用于辅助PushMonial
static double g_Number = 0.0;			//g_Number用于保存指定指数
void inline SetFunc(PtrToMonmial pMonm)	//设定指定指数
{
	g_Number = pMonm->exponent;
}
//判断该单项式的指数是否等于g_Number
_Bool static Func(PtrToMonmial pMonm)
{
	if(IsEqual(pMonm->exponent, g_Number))
		return true;
	else
		return false;
}

//追加单项式
Polynomial PushMonmial(PtrToMonmial pMonm, Polynomial poly)
{
	if (IsEqual(0, pMonm->coefficient)) //如果系数为0就不用加进去了
		return poly;
	if (IsEqual(0, pMonm->exponent))	//如果指数为0，就是常数项了
	{
		poly.constant += pMonm->coefficient;
		return poly;
	}

	SetFunc(pMonm);
	//查找多项式中是否有指数相同的项
	ListPosition pFind = FindIf(Func, poly.monmials);
	if (pFind)	//如果找到，就
	{
		PtrToMonmial pTmp = pFind->ELement;
		pTmp->coefficient += pMonm->coefficient;
		//如果相加后系数为0，也不删除，采用惰性删除，
		//系数为0，就不打印
	}
	else
	{
		//没找到就直接追加
	}
	{
		poly.monmials = PushBack(pMonm, poly.monmials);
	}
	return poly;
}

//追加常数项
Polynomial PushConstant(Polynomial poly, const double constant)
{
	return (Polynomial) { poly.monmials, poly.constant + constant };
}


//排序多项式
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
//	打印单项式核心函数
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
// 打印多项式的第一项以后的项
void static PrintMonmial(ListPosition pos)
{
	if (!pos) return;
	PtrToMonmial pMonm = pos->ELement;
	if (pMonm->coefficient > 0)
		printf("+ ");
	PrintMonmialBase(pos);
}
//----------------------------------------
// 打印多项式驱动函数
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