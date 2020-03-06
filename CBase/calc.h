#ifndef _YGW_TYPE_8848_
#define _YGW_TYPE_8848_
#include "link_list.h"

//单项式类型
typedef struct Monomial
{
	double coefficient;	//系数
	double exponent;	//指数
}Monomial;

typedef Monomial* PtrToMonmial;

//多项式类型
typedef struct Polynomial
{
	List monmials;		//带未知数的项
	double constant;	//常数项
}Polynomial;


//构造单项式
PtrToMonmial MakeMonomial(double coefficient,double exponent);
//销毁单项式
void DestroyMonmial(PtrToMonmial p);
//初始化多项式
Polynomial InitPolynomial();
//销毁多项式
void DestoryPolynomial(Polynomial poly);
//追加常数项
Polynomial PushConstant(Polynomial poly, const double constant);
//追加单项式
Polynomial PushMonmial(PtrToMonmial pMonm, Polynomial poly);
//打印多项式
void PrintPolynomial(const Polynomial poly);
//排序多项式
void SortPolynomial(Polynomial poly);
#endif // !_YGW_TYPE_8848_