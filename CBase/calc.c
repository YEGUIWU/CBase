#define _CRT_SECURE_NO_WARNINGS
#include "calc.h"
#include <math.h>
#include <string.h>
#include <varargs.h>
#include <ctype.h>

//#define MY_DEBUG //�Զ������������Ϣ����

//----------------------------------------
//���������Ϣ����
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
//�жϸ������Ƿ����
_Bool static inline IsEqual(const double db1, const double db2)
{
	return fabs(db1 - db2) < 1e-14;
}


//----------------------------------------
//���쵥��ʽ
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
//���ٵ���ʽ
void DestroyMonmial(Monmial p)
{
	free(p);
}


//----------------------------------------
//��ʼ������ʽ
Polynomial InitPolynomial()
{
	return (Polynomial) { NULL, 0 };
}


//----------------------------------------
//���ٶ���ʽ
Polynomial DestoryPolynomial(Polynomial poly)
{
	if (!ListIsEmpty(poly.monmials))
	{
		Monmial MonmTmp = NULL;
		for (PtrToListNode itr = HeadOfList(poly.monmials); itr; itr = itr->Next)
		{
			DestroyMonmial(itr->ELement);
		}
		poly.monmials = DestroyList(poly.monmials);
	}
	return poly;
}


//----------------------------------------
// g_Number SetFunc Func  �������ڸ���PushMonial
static double g_Number = 0.0;			//g_Number���ڱ���ָ��ָ��
void inline SetFunc(double exponent)	//�趨ָ��ָ��
{
	g_Number = exponent;
}

//----------------------------------------
//�жϸõ���ʽ��ָ���Ƿ����g_Number
_Bool static Func(Monmial pMonm)
{
	if (IsEqual(pMonm->exponent, g_Number))
		return true;
	else
		return false;
}

//----------------------------------------
//׷�ӵ���ʽ
Polynomial PushMonmial(double coefficient, double exponent, Polynomial poly)
{
	if (IsEqual(0, coefficient)) //���ϵ��Ϊ0�Ͳ��üӽ�ȥ��
		return poly;
	if (IsEqual(0, exponent))	//���ָ��Ϊ0�����ǳ�������
	{
		poly.constant += coefficient;
		return poly;
	}

	SetFunc(exponent);
	//���Ҷ���ʽ���Ƿ���ָ����ͬ����
	ListPosition pFind = FindIf(Func, poly.monmials);
	if (pFind)	//����ҵ�����
	{
		Monmial pTmp = pFind->ELement;
		pTmp->coefficient += coefficient;
		//�����Ӻ�ϵ��Ϊ0��Ҳ��ɾ�������ö���ɾ����
		//ϵ��Ϊ0���Ͳ���ӡ
	}
	else
	{//û�ҵ���ֱ��׷��
		poly.monmials = PushBack(MakeMonomial(coefficient, exponent), poly.monmials);
	}
	return poly;
}

//----------------------------------------
//׷�ӳ�����
Polynomial PushConstant(Polynomial poly, const double constant)
{
	return (Polynomial) { poly.monmials, poly.constant + constant };
}

//----------------------------------------
//�������ʽ
int static MonmialCompare(Monmial p1, Monmial p2)
{
	double res = p1->exponent - p2->exponent;
	if (res > 0) return 1;
	else if (res < 0) return -1;
	else return 0;
}
void SortPolynomial(Polynomial poly)
{
	SortList(poly.monmials, MonmialCompare);
}

//----------------------------------------
//	��ӡ����ʽ���ĺ���
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
// ��ӡ����ʽ�ĵ�һ���Ժ����
void static PrintMonmial(ListPosition pos)
{
	if (!pos) return;
	Monmial Monm = pos->ELement;
	if (Monm->coefficient > 0)
		printf("+ ");
	PrintMonmialBase(pos);
}
//----------------------------------------
// ��ӡ����ʽ��������
void PrintPolynomial(const Polynomial poly)
{
	if (!ListIsEmpty(poly.monmials))
	{
		PtrToListNode head = HeadOfList(poly.monmials);
		PrintMonmialBase(head);


		if (head->Next)
		{
			for (ListPosition p = head->Next; p; p = p->Next)
				PrintMonmial(p);
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
//��������ʽ
Monmial CopyMonmial(Monmial pMonm)
{
	return MakeMonomial(pMonm->coefficient, pMonm->exponent);
}
//----------------------------------------
//��������ʽ
Polynomial CopyPolynomial(Polynomial poly)
{
	Polynomial polyBarkup = InitPolynomial();
	polyBarkup.constant = poly.constant;
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = HeadOfList(poly.monmials); itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		polyBarkup = PushMonmial(MonmTmp->coefficient, MonmTmp->exponent, polyBarkup);
	}
	return polyBarkup;
}
//----------------------------------------
//����ʽ���
Polynomial PolynomialAdd(Polynomial polyLeft, Polynomial polyRight)
{
	Polynomial polyBarkup = CopyPolynomial(polyLeft);
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = HeadOfList(polyRight.monmials); itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		polyBarkup = PushMonmial(MonmTmp->coefficient, MonmTmp->exponent, polyBarkup);
	}
	return polyBarkup;
}
//-----------------------------------------
//����ʽ���
Polynomial PolynomialSubtract(Polynomial polyLeft, Polynomial polyRight)
{
	Polynomial polyBarkup = CopyPolynomial(polyLeft);
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = HeadOfList(polyRight.monmials); itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		polyBarkup = PushMonmial(-MonmTmp->coefficient, MonmTmp->exponent, polyBarkup);
	}
	return polyBarkup;
}
//----------------------------------------
//����ʽ���
static inline void PolyMulMonm(Polynomial poly, Monmial monm)
{
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = HeadOfList(poly.monmials); itr; itr = itr->Next)
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
	for (PtrToListNode itr = HeadOfList(polyRight.monmials); itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		PolyMulMonm(polyBarkup, MonmTmp);
	}
	return polyBarkup;
}
//----------------------------------------
//����ʽ���
static inline void PolyDivMonm(Polynomial poly, Monmial monm)
{
	Monmial MonmTmp = NULL;
	for (PtrToListNode itr = HeadOfList(poly.monmials); itr; itr = itr->Next)
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
	for (PtrToListNode itr = HeadOfList(polyRight.monmials); itr; itr = itr->Next)
	{
		MonmTmp = itr->ELement;
		PolyDivMonm(polyBarkup, MonmTmp);
	}
	return polyBarkup;
}
//----------------------------------------
//make�ַ���
String MakeString(const char* cstr)
{
	size_t length = strlen(cstr) + 1;
	char* p = (char*)malloc(length);
	if (p)
	{
		strcpy_s(p, length, cstr);
	}
	return (String) { p };
}
//----------------------------------------
//remake�ַ���
String ReMakeString(String str, const char* cstr)
{
	DestoryString(str);
	return MakeString(cstr);
}
//----------------------------------------
//�����ַ���
void DestoryString(String str)
{
	free(str.pBuf);
}
//----------------------------------------
//�Ե����пո��
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
//���ܣ���ȡ���ٸ�x��X
int GetNX(String str)
{
	if (!strlen(str.pBuf))
		return 0;

	int n = 1;
	for (int i = 0; str.pBuf[i]; ++i)
	{
		n = ((str.pBuf[i] == 'x') | (str.pBuf[i] == 'X')) ? n + 1 : n;
	}
	return n;
}
//-------------------------------------------------
//���ܣ��ַ���ת����ʽ
//���ƣ�1. �������������ַ�����ĩβ
//		2. ��ǰ�������з���

typedef struct _709394Info
{
	_Bool has_coefficient;//��ϵ��
	_Bool has_exponent;//��ָ��
}Info;


Polynomial StringToPolynomial(const char* cstr)
{
	Polynomial poly = InitPolynomial();
	if (!strlen(cstr)) return poly;
	String poly_str = MakeString(cstr);

	EatSpace(poly_str.pBuf);

	const char* str = poly_str.pBuf;

	int n = GetNX(poly_str);		//������


	if (!n)	//���һ���x�Ķ�û��
	{
		poly = PushConstant(poly, atof(cstr));
	}
	else
	{
		Info* pInfo = (Info*)calloc(n, sizeof(Info));
		if (!pInfo) exit(EXIT_FAILURE);
		for (int i = 0, count = 0; str[i]; ++i)
		{
			if ((str[i] == 'x') | (str[i] == 'X'))
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
		double coefficient;	//ϵ��
		double exponent;	//ָ��
		char sign;
		const char* pstr = str;
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