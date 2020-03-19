#include "calc.h"
#include <string.h>
#include <conio.h>
#include <stdlib.h>
//--------------------------------------------------------
//打印头
void static inline Output_Header(const char* head)
{
	printf("[%s]: ", head);
}
//--------------------------------------------------------
//打印分隔线
void static inline Output_Cutoff_Rule()
{
	printf("\n------------------------------------------------------------\n");
}
//--------------------------------------------------------
//打印测试结果
void static inline TestPolynomial(Polynomial polyA, Polynomial polyB)
{
	Output_Cutoff_Rule();
	Output_Header("A原式  ");
	PrintPolynomial(polyA);
	SortPolynomial(polyA);
	Output_Header("A排序后");
	PrintPolynomial(polyA);
	Output_Header("B原式  ");
	PrintPolynomial(polyB);
	SortPolynomial(polyB);
	Output_Header("B排序后");
	PrintPolynomial(polyB);

	Polynomial polyAdd = PolynomialAdd(polyA, polyB);
	SortPolynomial(polyAdd);
	Output_Header("AB相加 ");
	PrintPolynomial(polyAdd);

	Polynomial polySub = PolynomialSubtract(polyA, polyB);
	SortPolynomial(polySub);
	Output_Header("AB相减 ");
	PrintPolynomial(polySub);

	Polynomial polyMul = PolynomialMultiply(polyA, polyB);
	SortPolynomial(polyMul);
	Output_Header("AB相乘 ");
	PrintPolynomial(polyMul);

	Polynomial polyDiv = PolynomialDivide(polyA, polyB);
	SortPolynomial(polyDiv);
	Output_Header("AB相除 ");
	PrintPolynomial(polyDiv);

	DestoryPolynomial(polyAdd);
	DestoryPolynomial(polySub);
	DestoryPolynomial(polyMul);
	DestoryPolynomial(polyDiv);
	Output_Cutoff_Rule();
}

//---------------------------------------------------------------------------
//测试数据
//(1) A = 2x + 5x ^ 8 - 3.1x ^ 11;  B = 7 - 5x ^ 8 + 11x ^ 9
//(2) A = 6x - 3 - x + 4.4x ^ 2 - 1.2x ^ 9;  B = -6x - 3 + 5.4x ^ 2 + 7.8x ^ 15
//(3) A = x + x ^ 2 + x ^ 3;  B = 2
//(4) A = x + x ^ 3;  B = -x - x - 3
//(5) A = x + x ^ 3 + x ^ 5;  B = x + x ^ 2 + x ^ 4
void TestAll()
{
	//1. 调用多项式API来建立多项式
	Polynomial polyA1 = InitPolynomial();
	polyA1 = PushMonmial(2, 1, polyA1);
	polyA1 = PushMonmial(5, 8, polyA1);
	polyA1 = PushMonmial(-3.1, 11, polyA1);
	Polynomial polyB1 = InitPolynomial();
	polyB1 = PushMonmial(7, 0, polyB1);
	polyB1 = PushMonmial(-5, 8, polyB1);
	polyB1 = PushMonmial(11, 9, polyB1);
	TestPolynomial(polyA1, polyB1);

	//2. 通过字符串转多项式建立多项式
	Polynomial polyA2 = StringToPolynomial("+6x -x+4.4x^2-1.2x^9-3");
	Polynomial polyB2 = StringToPolynomial("-6x+5.4x^2+7.8x^15-3");
	TestPolynomial(polyA2, polyB2);

	Polynomial polyA3 = StringToPolynomial("+x + x ^ 2 + x ^ 3");
	Polynomial polyB3 = StringToPolynomial("+2");
	TestPolynomial(polyA3, polyB3);

	Polynomial polyA4 = StringToPolynomial("+x + x ^ 3");
	Polynomial polyB4 = StringToPolynomial("-x - x - 3");
	TestPolynomial(polyA4, polyB4);

	Polynomial polyA5 = StringToPolynomial("+x + x ^ 3 + x ^ 5");
	Polynomial polyB5 = StringToPolynomial(" +x + x ^ 2 + x ^ 4");
	TestPolynomial(polyA5, polyB5);
}

static void inline Tips()
{
	system("cls");
	Output_Cutoff_Rule();
	printf("多项式建立规则: "
		"\n(1) 空格可以随便加，但是第一项如果是正数需要加+"
		"\n(2) 常数项需要放在最后一项\n\n");
	printf("[输入0] 直接输出测试要求的所有结果\n");
	printf("[输入1] 输入建立多项式\n");
	printf("[输入2] 通过编辑input文件并读取来建立多项式\n");
	printf("[输入3] 进行各种运算\n");
	printf("[输入4] 清屏\n");
	printf("[输入5] 退出\n");
	Output_Cutoff_Rule();
}

int main()
{
	char ch;//用户选择
	Polynomial polyA = InitPolynomial();
	Polynomial polyB = InitPolynomial();
	char buf[BUFSIZ];

	while (true)
	{

		Tips();
		ch = _getch();
		switch (ch)
		{
		case '0': 
			TestAll();
			break;
		case '1': 
			polyA = DestoryPolynomial(polyA);
			polyB = DestoryPolynomial(polyB);
			printf("[请输入多项式A]：");
			fgets(buf, BUFSIZ, stdin);
			polyA = StringToPolynomial(buf);
			printf("[请输入多项式B]：");
			fgets(buf, BUFSIZ, stdin);
			polyB = StringToPolynomial(buf);
			break;
		case '2': 
			polyA = DestoryPolynomial(polyA);
			polyB = DestoryPolynomial(polyB);
			printf("[请编辑当前目录下的input.txt文件]\n");
			system("pause");
			FILE* pf;
			fopen_s(&pf, "./input.txt", "r");
			if (pf)
			{
				fgets(buf, BUFSIZ, pf);
				polyA = StringToPolynomial(buf);
				fgets(buf, BUFSIZ, pf);
				polyB = StringToPolynomial(buf);
				fclose(pf);
			}
			break;
		case '3': 
			TestPolynomial(polyA, polyB);
			system("pause");
			break;
		case '4': 
			system("cls");
			break;
		case '5': 
			exit(EXIT_SUCCESS);
			break;
		}
	}
}