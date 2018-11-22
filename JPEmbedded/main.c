#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//liczy przekazane wyrazenie (OK)
int makeOperation(int numberOne, char operation, int numerTwo,int *signs, int *error)
{
	int tempResult = 0;
	switch(operation)
	{
		case '+':
			tempResult = numberOne + numerTwo;
			break;
		case '-':
			tempResult = numberOne - numerTwo;
			break;
		case '*':
			tempResult = numberOne * numerTwo;
			break;
		case '/':
			tempResult = numberOne / numerTwo;
			break;
		default:
			*error = 1;
	}

	int numberOfSigns = 0;
	int result = tempResult;
	if(tempResult < 0) 
		numberOfSigns++;
	while(tempResult)
	{
		tempResult /= 10;
		numberOfSigns++;
	}
	*signs = numberOfSigns;


	return result;

}

//Sprawdza czy jest znak +-*/ na koncu (OK)
bool isOperatorAtTheEnd(const char *expression, int size)
{
	return (expression[size-1] == '+') || (expression[size-1] == '-') || (expression[size-1] == '*') || (expression[size-1] == '/');
}

//Zwraca romziar wyrazenia (OK)
int getSize(const char *expression)
{
	int size = 0;
	while(expression[size] != '\0') size++;
	return size;
}

//OK
int howManyOpeningBrackets(const char *expression, int size)
{
	int count = 0;
	for(int i = 0; i < size; i++)
	{
		if(expression[i] == '(') count++;
	}
	return count;
}

//OK
int howManyClosingBrackets(const char *expression, int size)
{
	int count = 0;
	for(int i = 0; i < size; i++)
	{
		if(expression[i] == ')') count++;
	}
	return count;
}

//ALe to jest glupie ale chyba dziaa choc nie tak jak chcialem TODO porpawic co sie da
bool getBracketStartAndEndIndex(const char *expression, int size, int *startIndex, int *endIndex, int *error)
{
	//zagniezdzenie
	int count = 0;
	//najglebszy nawias
	int max = 0;

	int currentBracket = 0;
	int amountOfBrackets = howManyOpeningBrackets(expression,size);
	printf("Brackets: %d\n", amountOfBrackets);
	//nt inWhichInside[amountOfBrackets][amountOfBrackets] = {{0}};
	

	if(amountOfBrackets == howManyClosingBrackets(expression,size))
	{
		int n = 3;
		int **inWhichInside = (int**)calloc(amountOfBrackets, sizeof(int*));

		for(int i = 0; i < 3; i++)
			inWhichInside[i] = (int*)calloc(n,sizeof(int));

		for(int i = 0; i < size; i++)
		{
			if(expression[i] == '(')
			{
				inWhichInside[count][0] = count;
				inWhichInside[count][1] = i;
				count++;
			}
			else if(expression[i] == ')')
			{
				count--;
				if(max < count) max = count;
				inWhichInside[count][2] = i;
				if(count != max)
				{
					*startIndex = inWhichInside[max][1];
					*endIndex = inWhichInside[max][2];
					for(int i = 0; i < amountOfBrackets; i++)
					{
						for(int j = 0; j < n; j++)
						{
							printf("%d ", inWhichInside[i][j]);
						}
						printf("\n");
						free(inWhichInside[i]);
					}
					free(inWhichInside);
					return max;
				}
			}
		}

		
	}
	else
	{
		*error = 1;
		return false;
	}
}

int calculate(const char *expression, double *result)
{
	int size = getSize(expression);
	int error = 0;
	int signs = 0;


	char workableExpression[size];
	for(int i =0; i < size; i++)
		workableExpression[i] = expression[i];

	int s;
	int e;
	getBracketStartAndEndIndex(workableExpression,size,&s,&e,&error);

	while(isOperatorAtTheEnd(workableExpression,size))
	{

	}





	return 1;
}





int main()
{
	int retavl;
	double result;
	if(0 == (retavl = calculate("300 ((2 1 +) |9 7 -| *) /",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}
	int *temp;
	int signs;
	int res = makeOperation(-100,'*',100,&signs,temp);
	printf("%d %d\n",res, signs );



	return retavl;
}