#define _CRT_SECURE_NO_WARNINGS
#include "calc.h"
#include <math.h>
#include <string.h>
#include <varargs.h>

//#define MY_DEBUG //自定义输出调试信息开关


//----------------------------------------
//输出调试信息函数
int static inline OutputDebugInfo(va_alist) va_dcl
{
	int n = 0;
#ifdef MY_DEBUG
	va_list ap;
	char* format;
	va_start(ap);
	format = va_arg(ap, char*);
	n = vprintf(format, ap);
	va_end(ap);
#endif 
	return n;
}



//----------------------------------------
//判断浮点数是否相等
_Bool static inline IsEqual(const double db1, const double db2)
{
	return fabs(db1 - db2) < 1e-14;
}


//----------------------------------------
//构造单项式
Monmial MakeMonomial(
	double coefficient,
	double exponent)
{
	Monmial p = (Monmial)malloc(sizeof(MonomialBase));
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


//----------------------------------------
//销毁单项式
void DestroyMonmial(Monmial p)
{
	free(p);
}


//----------------------------------------
//初始化多形式
Polynomial InitPolynomial()
{
	return (Polynomial) { NULL, 0 };
}


//----------------------------------------
//销毁多项式
Polynomial DestoryPolynomial(Polynomial poly)
{
	if (!poly.monmials) return;
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = poly.monmials; itr; itr = itr->Next)
	{
		DestroyMonmial(itr->ELement);
	}
	DestroyList(poly.monmials);
	poly.monmials = NULL;
	return poly;
}


//----------------------------------------
// g_Number SetFunc Func  都是用于辅助PushMonial
static double g_Number = 0.0;			//g_Number用于保存指定指数
void inline SetFunc(double exponent)	//设定指定指数
{
	g_Number = exponent;
}

//----------------------------------------
//判断该单项式的指数是否等于g_Number
_Bool static Func(Monmial pMonm)
{
	if (IsEqual(pMonm->exponent, g_Number))
		return true;
	else
		return false;
}

//----------------------------------------
//追加单项式
Polynomial PushMonmial(double coefficient, double exponent, Polynomial poly)
{
	if (IsEqual(0, coefficient)) //如果系数为0就不用加进去了
		return poly;
	if (IsEqual(0, exponent))	//如果指数为0，就是常数项了
	{
		poly.constant += coefficient;
		return poly;
	}

	SetFunc(exponent);
	//查找多项式中是否有指数相同的项
	ListPosition pFind = FindIf(Func, poly.monmials);
	if (pFind)	//如果找到，就
	{
		Monmial pTmp = pFind->ELement;
		pTmp->coefficient += coefficient;
		//如果相加后系数为0，也不删除，采用惰性删除，
		//系数为0，就不打印
	}
	else
	{//没找到就直接追加
		poly.monmials = PushBack(MakeMonomial(coefficient, exponent), poly.monmials);
	}
	return poly;
}

//----------------------------------------
//追加常数项
Polynomial PushConstant(Polynomial poly, const double constant)
{
	return (Polynomial) { poly.monmials, poly.constant + constant };
}

//----------------------------------------
//排序多项式
int static MonmialCompare(Monmial p1, Monmial p2)
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
	if (!pos) return;
	Monmial Monm = pos->ELement;
	if (IsEqual(0, Monm->coefficient))
		return;

	if (IsEqual(1, Monm->coefficient))
		printf("X");
	else if (IsEqual(-1, Monm->coefficient))
		printf("-X");
	else
		printf("%.1fX", Monm->coefficient);

	if (!IsEqual(1, Monm->exponent))
		printf("^%.1f", Monm->exponent);
	putchar(' ');
}
//-----------------------------------------
// 打印多项式的第一项以后的项
void static PrintMonmial(ListPosition pos)
{
	if (!pos) return;
	Monmial Monm = pos->ELement;
	if (Monm->coefficient > 0)
		printf("+ ");
	PrintMonmialBase(pos);
}
//----------------------------------------
// 打印多项式驱动函数
void PrintPolynomial(const Polynomial poly)
{
	if (poly.monmials)
	{
		PtrToListNode head = HeadOfList(poly.monmials);
		PrintMonmialBase(head);


		if (head->Next)
		{
			DisplayList(head->Next, PrintMonmial);
		}

		if (!IsEqual(0, poly.constant))
		{
			if (poly.constant > 0)
				printf("+ %.1f", poly.constant);
			else
				printf(" %.1f", poly.constant);
		}
	}
	else if (!IsEqual(0, poly.constant))
	{
		printf("%.1f", poly.constant);
	}


	printf("\n");
}

//-------------------------------------------------
//拷贝单项式
Monmial CopyMonmial(Monmial pMonm)
{
	return MakeMonomial(pMonm->coefficient, pMonm->exponent);
}
//----------------------------------------
//拷贝多项式
Polynomial CopyPolynomial(Polynomial poly)
{
	Polynomial polyBarkup = InitPolynomial();
	polyBarkup.constant = poly.constant;
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = poly.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		polyBarkup = PushMonmial(MonmTmp->coefficient, MonmTmp->exponent, polyBarkup);
	}
	return polyBarkup;
}
//----------------------------------------
//多项式相加
Polynomial PolynomialAdd(Polynomial polyLeft, Polynomial polyRight)
{
	Polynomial polyBarkup = CopyPolynomial(polyLeft);
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = polyRight.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		polyBarkup = PushMonmial(MonmTmp->coefficient, MonmTmp->exponent, polyBarkup);
	}
	return polyBarkup;
}
//-----------------------------------------
//多项式相减
Polynomial PolynomialSubtract(Polynomial polyLeft, Polynomial polyRight)
{
	Polynomial polyBarkup = CopyPolynomial(polyLeft);
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = polyRight.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		polyBarkup = PushMonmial(-MonmTmp->coefficient, MonmTmp->exponent, polyBarkup);
	}
	return polyBarkup;
}
//----------------------------------------
//多项式相乘
static inline void PolyMulMonm(Polynomial poly, Monmial monm)
{
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = poly.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		MonmTmp->coefficient *= monm->coefficient;
		MonmTmp->exponent += monm->exponent;
	}
}
//
Polynomial PolynomialMultiply(Polynomial polyLeft, Polynomial polyRight)
{
	Polynomial polyBarkup = CopyPolynomial(polyLeft);
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = polyRight.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		PolyMulMonm(polyBarkup, MonmTmp);
	}
	return polyBarkup;
}
//----------------------------------------
//多项式相除
static inline void PolyDivMonm(Polynomial poly, Monmial monm)
{
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = poly.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		MonmTmp->coefficient /= monm->coefficient;
		MonmTmp->exponent -= monm->exponent;
	}
}
//
Polynomial PolynomialDivide(Polynomial polyLeft, Polynomial polyRight)
{
	Polynomial polyBarkup = CopyPolynomial(polyLeft);
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = polyRight.monmials; itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		PolyDivMonm(polyBarkup, MonmTmp);
	}
	return polyBarkup;
}
//----------------------------------------
//make字符串
String MakeString(const char* cstr)
{
	int length = strlen(cstr) + 1;
	char* p = (char*)malloc(length);
	strcpy_s(p, length, cstr);
	return (String) { p };
}
//----------------------------------------
//remake字符串
String ReMakeString(String str, const char* cstr)
{
	DestoryString(str);
	return MakeString(cstr);
}
//----------------------------------------
//销毁字符串
void DestoryString(String str)
{
	free(str.pBuf);
}
//----------------------------------------
//吃掉所有空格符
void inline static EatSpace(char* str)
{
	if (str)
	{
		char* p1 = str;
		char* p2 = str;
		while (*p2)
		{
			if (*p2 == ' ')
			{
				*p1 = *p2++;
			}
			else
			{
				*p1++ = *p2++;
			}
		}
		*p1 = '\0';
	}
}
//----------------------------------------
//功能：获取多少个x或X
int GetNX(String str)
{
	if (!strlen(str.pBuf))
		return 0;

	int n = 1;
	for (int i = 0; str.pBuf[i]; ++i)
	{
		n = str.pBuf[i] == 'x' | str.pBuf[i] == 'X' ? n + 1 : n;
	}
	return n;
}
//-------------------------------------------------
//功能：字符串转多项式
//限制：1. 尝试项必须放在字符串最末尾
//		2. 最前方必须有符号

typedef struct _709394Info
{
	_Bool has_coefficient;//有系数
	_Bool has_exponent;//有指数
}Info;


Polynomial StringToPolynomial(const char* cstr)
{
	if (!strlen(cstr)) return;
	String poly_str = MakeString(cstr);

	EatSpace(poly_str.pBuf);

	const char* str = poly_str.pBuf;

	int n = GetNX(poly_str);		//子项数

	Polynomial poly = InitPolynomial();

	if (!n)	//如果一项带x的都没有
	{
		poly = PushConstant(poly, atof(cstr));
	}
	else
	{
		Info* pInfo = (Info*)calloc(n, sizeof(Info));
		if (!calloc) exit(EXIT_FAILURE);
		for (int i = 0, count = 0; str[i]; ++i)
		{
			if (str[i] == 'x' | str[i] == 'X')
			{
				if (isdigit(str[i - 1]))
					pInfo[count].has_coefficient = true;
				if (str[i + 1] == '^' && isdigit(str[i + 2]))
					pInfo[count].has_exponent= true;
				++count;
			}
		}


		const int bufsize = 256;
		char* buf = (char*)calloc(bufsize, sizeof(char));
		if (!buf) exit(EXIT_FAILURE);
		double coefficient;	//系数
		double exponent;	//指数
		char sign;
		char* pstr = str;
		char* pfind_sub = NULL;
		char* pfind_add = NULL;
		int idx = 0;

		//"+4.0X^6.0-X^4.0+2.0X^3.0"
		for (int idx = 0; n != idx; ++idx, ++pstr)
		{

			OutputDebugInfo("%s\n", pstr);
			pfind_add = strchr(pstr, '+');
			pfind_sub = strchr(pstr, '-');
			if (!pfind_add && !pfind_sub) break;
			if (pfind_add && pfind_sub)
			{
				pstr = pfind_add < pfind_sub ? pfind_add : pfind_sub;
			}
			else
			{
				pstr = pfind_add ? pfind_add : pfind_sub;
			}

			coefficient = exponent = sign = 0;
			if (pInfo[idx].has_coefficient && pInfo[idx].has_exponent)//ax^b  
			{
				OutputDebugInfo("%s\n", "%c%lf%*c%*c%lf");
				sscanf(pstr, "%c%lf%*c%*c%lf", &sign, &coefficient, &exponent);
			}
			else if (pInfo[idx].has_coefficient)//ax
			{
				OutputDebugInfo("%s\n", "%c%lf%*c");
				sscanf(pstr, "%c%lf%*c", &sign, &coefficient);
				exponent = 1;
			}
			else if (pInfo[idx].has_exponent)//x^b
			{
				OutputDebugInfo("%s\n", "%c%*c%*c%lf");
				sscanf(pstr, "%c%*c%*c%lf", &sign, &exponent);
				coefficient = 1;
			}
			else//a or x
			{
				if (pstr[1] == 'x' || pstr[1] == 'X')
				{
					OutputDebugInfo("%s\n", "%c");
					sscanf(pstr, "%c", &sign);
					exponent = 1;
					coefficient = 1;
				}
				else
				{
					OutputDebugInfo("%s\n", "%c%lf");
					sscanf(pstr, "%c%lf", &sign, &coefficient);
					exponent = 0;
				}
			}
			OutputDebugInfo("%c %f %f\n", sign, coefficient, exponent);
			if (sign == '-') coefficient *= -1;
			poly = PushMonmial(coefficient, exponent, poly);
		}
		free(buf);
		free(pInfo);
		DestoryString(poly_str);
	}

	return poly;
}