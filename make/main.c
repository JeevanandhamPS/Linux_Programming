/***************************************/
/* Author	: Jeevanandham P S     */
/* Date		: 14-mar-2019          */
/* Filename	: main.c               */
/* Description	: sample make file     */
/***************************************/

/* Included header file */
#include "make.h"

/* Global variable definitions */


/* function definitions */

int main()
{
	int a=10,b=5,addition,subtraction,multiplication,division,modulo,sum;

	addition = add(a,b);
	subtraction = sub(a,b);
	multiplication = mul(a,b);
	division = div(a,b);
	modulo = mod(a,b);
	sum = sm(1,2,3,4,5);

	printf("addition	= %d\n",addition);
	printf("Subtraction	= %d\n",subtraction);
	printf("Multiplication	= %d\n",multiplication);
	printf("Division	= %d\n",division);
	printf("Modulo		= %d\n",modulo);
	printf("SUM		= %d\n",sum);
}
