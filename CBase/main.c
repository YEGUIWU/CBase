#include "calc.h"
#include <string.h>
#include <conio.h>
#include <stdlib.h>
//--------------------------------------------------------
//��ӡͷ
void static inline Output_Header(const char* head)
{
	printf("[%s]: ", head);
}
//--------------------------------------------------------
//��ӡ�ָ���
void static inline Output_Cutoff_Rule()
{
	printf("\n------------------------------------------------------------\n");
}
//--------------------------------------------------------
//��ӡ���Խ��
void static inline TestPolynomial(Polynomial polyA, Polynomial polyB)
{
	Output_Cutoff_Rule();
	Output_Header("Aԭʽ  ");
	PrintPolynomial(polyA);
	SortPolynomial(polyA);
	Output_Header("A�����");
	PrintPolynomial(polyA);
	Output_Header("Bԭʽ  ");
	PrintPolynomial(polyB);
	SortPolynomial(polyB);
	Output_Header("B�����");
	PrintPolynomial(polyB);

	Polynomial polyAdd = PolynomialAdd(polyA, polyB);
	SortPolynomial(polyAdd);
	Output_Header("AB��� ");
	PrintPolynomial(polyAdd);

	Polynomial polySub = PolynomialSubtract(polyA, polyB);
	SortPolynomial(polySub);
	Output_Header("AB��� ");
	PrintPolynomial(polySub);

	Polynomial polyMul = PolynomialMultiply(polyA, polyB);
	SortPolynomial(polyMul);
	Output_Header("AB��� ");
	PrintPolynomial(polyMul);

	Polynomial polyDiv = PolynomialDivide(polyA, polyB);
	SortPolynomial(polyDiv);
	Output_Header("AB��� ");
	PrintPolynomial(polyDiv);

	DestoryPolynomial(polyAdd);
	DestoryPolynomial(polySub);
	DestoryPolynomial(polyMul);
	DestoryPolynomial(polyDiv);
	Output_Cutoff_Rule();
}

//---------------------------------------------------------------------------
//��������
//(1) A = 2x + 5x ^ 8 - 3.1x ^ 11;  B = 7 - 5x ^ 8 + 11x ^ 9
//(2) A = 6x - 3 - x + 4.4x ^ 2 - 1.2x ^ 9;  B = -6x - 3 + 5.4x ^ 2 + 7.8x ^ 15
//(3) A = x + x ^ 2 + x ^ 3;  B = 2
//(4) A = x + x ^ 3;  B = -x - x - 3
//(5) A = x + x ^ 3 + x ^ 5;  B = x + x ^ 2 + x ^ 4
void TestAll()
{
	//1. ���ö���ʽAPI����������ʽ
	Polynomial polyA1 = InitPolynomial();
	polyA1 = PushMonmial(2, 1, polyA1);
	polyA1 = PushMonmial(5, 8, polyA1);
	polyA1 = PushMonmial(-3.1, 11, polyA1);
	Polynomial polyB1 = InitPolynomial();
	polyB1 = PushMonmial(7, 0, polyB1);
	polyB1 = PushMonmial(-5, 8, polyB1);
	polyB1 = PushMonmial(11, 9, polyB1);
	TestPolynomial(polyA1, polyB1);

	//2. ͨ���ַ���ת����ʽ��������ʽ
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
	printf("����ʽ��������: "
		"\n(1) �ո�������ӣ����ǵ�һ�������������Ҫ��+"
		"\n(2) ��������Ҫ�������һ��\n\n");
	printf("[����0] ֱ���������Ҫ������н��\n");
	printf("[����1] ���뽨������ʽ\n");
	printf("[����2] ͨ���༭input�ļ�����ȡ����������ʽ\n");
	printf("[����3] ���и�������\n");
	printf("[����4] ����\n");
	printf("[����5] �˳�\n");
	Output_Cutoff_Rule();
}

int main()
{
	char ch;//�û�ѡ��
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
			printf("[���������ʽA]��");
			fgets(buf, BUFSIZ, stdin);
			polyA = StringToPolynomial(buf);
			printf("[���������ʽB]��");
			fgets(buf, BUFSIZ, stdin);
			polyB = StringToPolynomial(buf);
			break;
		case '2': 
			polyA = DestoryPolynomial(polyA);
			polyB = DestoryPolynomial(polyB);
			printf("[��༭��ǰĿ¼�µ�input.txt�ļ�]\n");
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