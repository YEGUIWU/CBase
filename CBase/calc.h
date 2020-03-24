#ifndef _YGW_TYPE_8848_
#define _YGW_TYPE_8848_
#include "link_list.h"

//单项式类型
typedef struct Monomial
{
	double coefficient;	//系数
	double exponent;	//指数
}MonomialBase;

typedef MonomialBase* Monmial;

//多项式类型
typedef struct Polynomial
{
	List monmials;		//带未知数的项
	//double constant;	//常数项
}Polynomial;

//字符串类型
#define STRING_BUF_SIZE 128
typedef struct StringBase
{
	char* pBuf;
}String;

//构造单项式
Monmial MakeMonomial(double coefficient,double exponent);
//销毁单项式
void DestroyMonmial(Monmial p);
//初始化多项式
Polynomial InitPolynomial();
//销毁多项式
Polynomial DestoryPolynomial(Polynomial poly);
//追加常数项
//Polynomial PushConstant(Polynomial poly, const double constant);
//追加单项式
Polynomial PushMonmial(double coefficient, double exponent, Polynomial poly);
//打印多项式
void PrintPolynomial(const Polynomial poly);
//排序多项式
void SortPolynomial(Polynomial poly);
//拷贝单项式
Monmial CopyMonmial(Monmial pMonm);
//拷贝多项式
Polynomial CopyPolynomial(Polynomial poly);
//多项式乘除法
Polynomial PolynomialMultiply(Polynomial polyLeft, Polynomial polyRight);
Polynomial PolynomialDivide(Polynomial polyLeft, Polynomial polyRight);
//多项式加减法
Polynomial PolynomialAdd(Polynomial polyLeft, Polynomial polyRight);
Polynomial PolynomialSubtract(Polynomial polyLeft, Polynomial polyRight);
//make字符串
String MakeString(const char* cstr);
//remake字符串
String ReMakeString (String str, const char* cstr);
//销毁字符串
void DestoryString(String str);
//字符串转多项式
//限制：1. 尝试项必须放在字符串最末尾
//	2. 最前方必须有符号
Polynomial StringToPolynomial(const char* cstr);

#endif // !_YGW_TYPE_8848_