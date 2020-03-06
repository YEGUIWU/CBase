#include "calc.h"

int main(const int argc, const char* argv[])
{
	Polynomial poly = InitPolynomial();
	poly = PushMonmial(MakeMonomial(-1, 3), poly);
	poly = PushMonmial(MakeMonomial(-2, 4), poly);
	poly = PushMonmial(MakeMonomial(1, 5), poly);
	SortPolynomial(poly);
	PrintPolynomial(poly);
	printf("hello world");


	DestoryPolynomial(poly);

	
	return 0;
}