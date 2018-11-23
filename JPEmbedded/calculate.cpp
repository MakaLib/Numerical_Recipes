#include <iostream>
#include <string.h>
#include <cstdio>

//liczy przekazane wyrazenie (OK)
int makeOperation(int numberOne, char operation, int numerTwo,int &signs, int &error)
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
			error = 1;
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
	signs = numberOfSigns;

	return result;
}

//Sprawdza czy jest znak +-*/ na koncu (OK)
bool isOperatorAtTheEnd(char *&expression, int size)
{
	return (expression[size-1] == '+') || (expression[size-1] == '-') || (expression[size-1] == '*') || (expression[size-1] == '/');
}


//OK
int howManyOpeningBrackets( char *&expression)
{
	int count = 0;
	for(unsigned i = 0; i < strlen(expression); i++)
	{
		if(expression[i] == '(') count++;
	}
	return count;
}

//OK
int howManyClosingBrackets( char *&expression)
{
	int count = 0;
	for(unsigned i = 0; i < strlen(expression); i++)
	{
		if(expression[i] == ')') count++;
	}
	return count;
}

//ALe to jest glupie ale chyba dziaa choc nie tak jak chcialem TODO porpawic co sie da
bool getBracketStartAndEndIndex(char *&expression, int &startIndex, int &endIndex, int &error)
{
	//zagniezdzenie
	int count = 0;
	//najglebszy nawias
	int max = 0;
	int amountOfBrackets = howManyOpeningBrackets(expression);

	
	if(amountOfBrackets == howManyClosingBrackets(expression) && amountOfBrackets != 0)
	{
		int n = 3;
		int **inWhichInside = new int* [amountOfBrackets];

		for(int i = 0; i < amountOfBrackets; i++)
			inWhichInside[i] = new int[n];

		for(unsigned i = 0; i < strlen(expression); i++)
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
				if(count != max || amountOfBrackets == 1)
				{
					startIndex = inWhichInside[max][1];
					endIndex = inWhichInside[max][2];
					for(int i = 0; i < amountOfBrackets; i++)
					{
						delete inWhichInside[i];
					}
					delete inWhichInside;
					return true;
				}
			}
		}

		
	}
	else if(amountOfBrackets == 0 )
	{
		return false;
	}
	error = 1;
	return false;
}

//modyfikuje stringa do kolejnych obliczen (gdy sa wyrazenia w nawiasach)
void modify(char *&expression,  char *toWrite,  int startIndex,  int endIndex, int size, int miniSize)
{

	int tempsize = size + miniSize - (endIndex - startIndex) + 1;
	char *newExpression = new char[tempsize+1];
	
	if(startIndex != 0)	
	for(int i = 0; i < startIndex; i++)
	{
		newExpression[i] = expression[i];
	}
	newExpression[startIndex] = ' ';
	for(int i = 1; i <= miniSize; i++)
	{
		newExpression[startIndex + i] = toWrite[i-1];
	}
	newExpression[startIndex+miniSize+1] = ' ';
	int j = 1;
	for(int i = startIndex + miniSize + 1; i  < tempsize; i++)
	{
		newExpression[i] = expression[j+endIndex]; 
		if(newExpression[i] == 'a')
		{
			newExpression[i] = '\0';
		} 
		j++;
	}
	newExpression[tempsize] = '\0';
	delete expression;
	expression = new char[tempsize+1];
	for(int i = 0; i < tempsize; i++ )
	{
		expression[i] = newExpression[i];
		if(expression[i] == 'a')
			expression[i] = '\0';
	}
	expression[tempsize] = '\0';
	delete newExpression;
}

//modyfikuje stringa do kolejnych obliczen (gdy nie ma juz nawiasow)
void modify2(char *&expression, char *toWrite,int startIndex, int endIndex, int size, int miniSize)
{
	int newSize = size + miniSize + 1 - (endIndex - startIndex);
	char *newExpression = new char[newSize+1];
	for(int i = 0; i < newSize; i++) newExpression[i] = 'a';

	for(int i = 0; i < miniSize; i++)
	{
		newExpression[i] = toWrite[i];
	}
	int j = 1;
	for(int i = miniSize; i < newSize; i++)
	{
		newExpression[i] = expression[endIndex+j];
		j++;
	}

	newExpression[newSize] = '\0';
	delete expression;
	expression = new char[newSize+1];
	for(int i = 0; i < newSize; i++)
	{
		expression[i] = newExpression[i];
	}
	expression[newSize] = '\0';
	delete newExpression;
}

//Zwraca najblizszy operator
char getOperator(char *&expression, int startIndex, int &error)
{
	for(unsigned i = startIndex; i < strlen(expression); i++)
	{
		if((expression[i] == '+') || (expression[i] == '-') || (expression[i] == '*') || (expression[i] == '/'))
			{
				if(!(isdigit(expression[i+1])))
					return expression[i];
			}
	}
	error = 1;
	return '+';
}

//Przygotowuje liczby do obliczenia (dla nawiasow)
int getResultWithBrackets(char *& workableExpression, int startIndex, int endIndex, int &error)
{
	//char *digitOne;
	int sizeOne = 0;
	int startOne = 0;
	//char *digitTwo;
	int sizeTwo = 0;
	int startTwo = 0;
	char oper = getOperator(workableExpression,startIndex,error);
	int flag = 1;
	int i = startIndex+1;
	
	while(workableExpression[i] == ' ') i++;
	startOne = i;
	while(flag == 1)
	{
		if(workableExpression[i] == ' ')
			flag = 2;
		else
			sizeOne++;
		i++;
	}
	startTwo = i;
	while(flag == 2)
	{
		if(workableExpression[i] == ' ' || workableExpression[i] == oper)
			flag = 3;

		else
			sizeTwo++;
		i++;
	}

	char *digitOne =  new char[sizeOne];
	for(int j = 0; j < sizeOne; j++)
		digitOne[j] = workableExpression[startOne+j];
	int tempResult;
	int newSize;

	if(sizeTwo == 0)
	{
		tempResult = makeOperation(0,oper, atoi(digitOne),newSize,error);
	}
	else
	{
		char *digitTwo = new char[sizeTwo];
		for(int j = 0; j < sizeTwo; j++)
			digitTwo[j] = workableExpression[startTwo+j];
		tempResult = makeOperation(atoi(digitOne),oper, atoi(digitTwo),newSize,error);
		delete digitTwo;
	}	
	char *newExpressionToWrite = new char[newSize];
	sprintf(newExpressionToWrite,"%d", tempResult);
	modify(workableExpression,newExpressionToWrite,startIndex,endIndex,strlen(workableExpression),newSize);
	
	delete digitOne;
	delete newExpressionToWrite;
	return tempResult;
}

//Przygotowuje liczby to obliczenia (gdy nie ma nawiasow)
int getResultWithoutBrackets(char *& workableExpression, int &error)
{
	int sizeOne = 0;
	int startOne = 0;
	int sizeTwo = 0;
	int startTwo = 0;
	char oper= '.';
	int flag = 1;
	int i = 0;
	
	while(workableExpression[i] == ' ') i++;

	startOne = i;
	while(flag == 1)
	{
		if(workableExpression[i] == ' ')
		{
			flag = 2;
			break;
		}
		else
			sizeOne++;
		i++;
	}
	while(workableExpression[i] == ' ') i++;
	startTwo = i;
	oper = getOperator(workableExpression,startOne,error);
	while(flag == 2)
	{
		if(workableExpression[i] == ' ' || workableExpression[i] == oper)
		{
			flag = 3;
			break;
		}

		else
			sizeTwo++;
		i++;
	}

	if(workableExpression[i+1] == oper) i++;
	else i--;
	char *digitOne = new char[sizeOne];
	for(int j = 0; j < sizeOne; j++)
		digitOne[j] = workableExpression[startOne+j];

	int newSize;
	int tempResult;
	if(sizeTwo == 0)
	{
		i = startOne + sizeOne + 1;
		tempResult = makeOperation(0,oper, atoi(digitOne),newSize,error);
	}
	else
	{
		char *digitTwo = new char[sizeTwo];
		for(int j = 0; j < sizeTwo; j++)
			digitTwo[j] = workableExpression[startTwo+j];
		tempResult = makeOperation(atoi(digitOne),oper, atoi(digitTwo),newSize,error);
		delete digitTwo;
	}
	
	char *newExpressionToWrite = new char[newSize];
	sprintf(newExpressionToWrite,"%d", tempResult);
	modify2(workableExpression,newExpressionToWrite,startOne,i,strlen(workableExpression),newSize);

	delete digitOne;
	delete newExpressionToWrite;
	return tempResult;
}


int calculate(const char *expression, double *result)
{
	int size = strlen(expression);
	int error = 0;
	double resultToWrite = 0;


	char *workableExpression = new char[size+1];
	for(int i =0; i < size; i++)
		workableExpression[i] = expression[i];
	workableExpression[size] = '\0';

	int startIndex = 0;
	int endIndex = 0;
	while(isOperatorAtTheEnd(workableExpression,strlen(workableExpression)))
	{	
		if(getBracketStartAndEndIndex(workableExpression,startIndex,endIndex,error))
		{
			
			resultToWrite = getResultWithBrackets(workableExpression, startIndex, endIndex, error);
		}
		else
		{
			resultToWrite = getResultWithoutBrackets(workableExpression, error);

		}
	}

	delete workableExpression;
	*result = resultToWrite;

	return error;
}



int main()
{
	int retavl;
	double result;
	if(0 == (retavl = calculate("300 ((2 1 +)(9 7 -) *) /",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("PRZYPADEK 2 ");
	if(0 == (retavl = calculate("3 (1 8 -) 5 *",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("PRZYPADEK 3 ");
	if(0 == (retavl = calculate("2 2 3 * 4 5 1 +",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("PRZYPADEK 4 ");
	if(0 == (retavl = calculate("1 2 +",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("PRZYPADEK 5 ");
	if(0 == (retavl = calculate("2 2 * 3 +",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("PRZYPADEK 5 ");
	if(0 == (retavl = calculate("3 -",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("PRZYPADEK 6 ");
	if(0 == (retavl = calculate("2 (1 -) 4 5 +",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	return retavl;
}