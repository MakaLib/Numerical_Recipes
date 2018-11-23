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

//Zwraca romziar wyrazenia (OK) wywalic
int getSize( char *expression)
{
	int size = 0;
	while(expression[size] != '\0') size++;
	return size;
}

//OK
int howManyOpeningBrackets( char *&expression)
{
	int count = 0;
	for(int i = 0; i < strlen(expression); i++)
	{
		if(expression[i] == '(') count++;
	}
	return count;
}

//OK
int howManyClosingBrackets( char *&expression)
{
	int count = 0;
	for(int i = 0; i < strlen(expression); i++)
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
	std::cout<<"Brackets: "<< amountOfBrackets << std::endl;
	//nt inWhichInside[amountOfBrackets][amountOfBrackets] = {{0}};
	
	if(amountOfBrackets == howManyClosingBrackets(expression) && amountOfBrackets != 0)
	{
		int n = 3;
		int **inWhichInside = new int* [amountOfBrackets];

		for(int i = 0; i < amountOfBrackets; i++)
			inWhichInside[i] = new int[n];

		for(int i = 0; i < strlen(expression); i++)
		{
			if(expression[i] == '(')
			{
				inWhichInside[count][0] = count;
				inWhichInside[count][1] = i;
				count++;
			}
			else if(expression[i] == ')')
			{
				std::cout<<"ENDBRACKET\n";
				count--;
				if(max < count) max = count;
				inWhichInside[count][2] = i;
				if(count != max || amountOfBrackets == 1)
				{
					startIndex = inWhichInside[max][1];
					endIndex = inWhichInside[max][2];
					for(int i = 0; i < amountOfBrackets; i++)
					{
						for(int j = 0; j < n; j++)
						{	
							std::cout<<inWhichInside[i][j]<<" ";
						}
						std::cout<<std::endl;
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
	else
	{
		error = 1;
		return false;
	}
}

//tu jest problem
int modify(char *&expression,  char *toWrite,  int startIndex,  int endIndex, int size, int miniSize)
{
	std::cout<<"BEFORE: " << expression << std::endl;
	int tempsize = size + miniSize - (endIndex - startIndex) + 1;
	std::cout <<"TEMPSIZE: " << tempsize <<" STARTINDEX: " <<startIndex<<" ENDINDEX: " <<endIndex<<"MINISIZE: " << miniSize << std::endl;
	//nie moge sie dostac po przekazaniu podwojnego wskaznika
	char *newExpression = new char[tempsize+1];
	//for(int i = 0; i < tempsize; i++) newExpression[i] = 'a';
	
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
	std::cout << "TABLICAZMODYFIKOWANA: " <<newExpression<<" SIZE: " << strlen(newExpression) <<"\n";
	delete expression;
	expression = new char[tempsize+1];
	//expression = (char*)malloc((tempsize+1) * sizeof(char));
	for(int i = 0; i < tempsize; i++ )
	{
		expression[i] = newExpression[i];
		if(expression[i] == 'a')
			expression[i] = '\0';
	}
	expression[tempsize] = '\0';
	//expression = newExpression;
	//strcpy(expression,newExpression);
	//expression[tempsize] = '\0';
	delete newExpression;
	return strlen(expression);
}


int modify2(char *&expression, char *toWrite,int startIndex, int endIndex, int size, int miniSize)
{
	int newSize = size + miniSize + 1 - (endIndex - startIndex);
	char *newExpression = new char[newSize+1];
	for(int i = 0; i < newSize; i++) newExpression[i] = 'a';
	std::cout<<"SDSD: " << strlen(newExpression) <<std::endl;
	for(int i = 0; i < miniSize; i++)
	{
		newExpression[i] = toWrite[i];
	}
	//newExpression[miniSize] = ' ';
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
	return strlen(expression);

}

//Zwraca najblizszy operoator
char getOperator(char *&expression, int startIndex, int &error)
{
	for(int i = startIndex; i < strlen(expression); i++)
	{
		if((expression[i] == '+') || (expression[i] == '-') || (expression[i] == '*') || (expression[i] == '/'))
			{
				if(!(isdigit(expression[i+1])))
					return expression[i];
			}
	}
	error = 1;
}

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
			//while(workableExpression[i] == ' ') i++;
			startTwo = i;
			while(flag == 2)
			{
				if(workableExpression[i] == ' ')
					flag = 3;

				else
					sizeTwo++;
				i++;
			}

			char *digitOne =  new char[sizeOne];
			for(int j = 0; j < sizeOne; j++)
				digitOne[j] = workableExpression[startOne+j];
			std::cout<<"TABLICA: " << atoi(digitOne) << " SIZE: " <<sizeOne<<" OPERATOR: " << oper <<std::endl;

			char *digitTwo = new char[sizeTwo];
			for(int j = 0; j < sizeTwo; j++)
				digitTwo[j] = workableExpression[startTwo+j];
			std::cout<<"TABLICA2: " << atoi(digitTwo) << " SIZE2: " <<sizeTwo<<" OPERATOR: " << oper <<std::endl;
			
			int newSize;
			int tempResult = makeOperation(atoi(digitOne),oper, atoi(digitTwo),newSize,error);
			std::cout<<"RESULT: "<<tempResult <<" SIZENEW: " <<newSize <<std::endl;
			char *newExpressionToWrite = new char[newSize];
			sprintf(newExpressionToWrite,"%d", tempResult);
			int size = modify(workableExpression,newExpressionToWrite,startIndex,endIndex,strlen(workableExpression),newSize);
			printf("AFTER MOD %s SIZEAFET %d\n",workableExpression,strlen(workableExpression) );
			
			delete digitOne;
			delete digitTwo;
			delete newExpressionToWrite;
			return tempResult;
}

int getResultWithoutBrackets(char *& workableExpression, int &error)
{
	//char *digitOne;
	int sizeOne = 0;
	int startOne = 0;
	//char *digitTwo;
	int sizeTwo = 0;
	int startTwo = 0;
	char oper= '.';
	int flag = 1;
	int i = 0;
	
	while(workableExpression[i] == ' ') i++;

	startOne = i;
	std::cout<<"START One " << workableExpression[startTwo] << std::endl;
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
	std::cout<<"START TWO: " << workableExpression[startTwo] << std::endl;
	while(flag == 2)
	{
		if(workableExpression[i] == ' ')
		{
			flag = 3;
			break;
		}

		else
			sizeTwo++;
		i++;
	}

	oper = getOperator(workableExpression,startOne,error);
	if(workableExpression[i+1] == oper) i++;
	else i--;
	char *digitOne = new char[sizeOne];
	for(int j = 0; j < sizeOne; j++)
		digitOne[j] = workableExpression[startOne+j];
	std::cout<<"DTABLICA: " << atoi(digitOne) << " SIZE: " <<sizeOne<<" OPERATOR: " << oper <<std::endl;

	char *digitTwo = new char[sizeTwo];
	for(int j = 0; j < sizeTwo; j++)
		digitTwo[j] = workableExpression[startTwo+j];
	std::cout<<"TABLICA2: " << atoi(digitTwo) << " SIZE2: " <<sizeTwo<<" OPERATOR: " << oper <<std::endl;
	
	int newSize;
	int tempResult = makeOperation(atoi(digitOne),oper, atoi(digitTwo),newSize,error);
	std::cout<<"RESULT: "<<tempResult <<" SIZENEW: " <<newSize <<" I: "<< i << std::endl;
	char *newExpressionToWrite = new char[newSize];
	sprintf(newExpressionToWrite,"%d", tempResult);
	int size = modify2(workableExpression,newExpressionToWrite,startOne,i,strlen(workableExpression),newSize);
	printf("AFTER MOD %s SIZEAFET %d\n",workableExpression,strlen(workableExpression) );

	delete digitOne;
	delete digitTwo;
	delete newExpressionToWrite;
	return tempResult;
}

int calculate(const char *expression, double *result)
{
	int size = strlen(expression);
	std::cout << "ORIGINALSIZE: " << size <<" EXPRESSION: " << expression << std::endl;
	int error = 0;
	int signs = 0;
	double resultToWrite = 0;


	char *workableExpression = new char[size+1];
	for(int i =0; i < size; i++)
		workableExpression[i] = expression[i];
	workableExpression[size] = '\0';

	std::cout<<"WORKABLEEXP: " << workableExpression <<" SIZE: " <<strlen(workableExpression) << std::endl;

	int startIndex;
	int endIndex;
	//getBracketStartAndEndIndex(workableExpression,startIndex,endIndex,error);

	int test = 0;
	while(isOperatorAtTheEnd(workableExpression,strlen(workableExpression)))
	{	
		printf("\n\n\n");
		if(getBracketStartAndEndIndex(workableExpression,startIndex,endIndex,error))
		{
			
			resultToWrite = getResultWithBrackets(workableExpression, startIndex, endIndex, error);
		}
		//nie ma nawiasow
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

	printf("\n\nPRZYPADEK 2\n\n");
	if(0 == (retavl = calculate("3 (1 8 -) 5 *",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}

	printf("\n\nPRZYPADEK 3\n\n");
	if(0 == (retavl = calculate("2 2 3 * 4 5 1 +",&result)))
	{
		printf("Result: %g\n", result);
	}
	else
	{
		printf("Error: %d\n", retavl);
	}


	return retavl;
}