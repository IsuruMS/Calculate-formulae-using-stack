/*****************************************************************
Course				:		CO2210 Programming Quest
Year				:		2019
Name				:		I. M. Samaranayake
Index no.			:		17_ENG_095
Assignment no.		:		1
Date				:		26-08-2019
*******************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<vector>
#include<sstream>

char * expression;	//global variable to hold the expression, Array implementation of a stack

using namespace std;

//peek function for stack
char peek()
{
	return *expression;
}
//pop function
char get()
{
	return *expression++;
}

float CalculateExpression();

//getting a number with multiple digits
float number()
{
	float result = get() - '0';	//get the top most digit
	while (peek() >= '0' && peek() <= '9')		//the function gathers numbers until all the digits are placed in the correct decimal place
	{
		result = 10 * result + get() - '0';
	}
	return result;
}

//solving the brackets
float Factorize()
{
	if (peek() >= '0' && peek() <= '9') //check for double digit and thripple digit numbers
		return number(); 
	else if (peek() == '(' || peek() == '[' || peek() == '{')
	{
		get(); // pop '('
		float result = CalculateExpression();
		get(); // pop ')' after calculation
		return result;
	}
	else if (peek() == '-') //check for a negative number
	{
		get();
		return -Factorize();  //convert the number to be substracted to a negative value
	}
	return 0;
}

//do the multiplication and division
float Seperation()
{
	float result = Factorize();
	while (peek() == '*' || peek() == '/')
		if (get() == '*')
			result *= Factorize();
		else
			result /= Factorize();
	return result;
}

//first this function is called
//seperate the + and - signs from the expression and calculate
float CalculateExpression()
{
	float result = Seperation();  //recursively call the function to seperate the terms with * and /
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += Seperation(); //calculate the addition
		else
			result -= Seperation(); //calculate the substraction
	return result;
}

bool IsParanthesisBalanced(string str)
{
	stack<char>s;
	vector<char> expression; //expression to hold the equation
	stringstream ss(str); //string stream to break the string and get each element
	char input;
	while (ss >> input)  //pushing each element to a vector separately
	{
		expression.push_back(input);
	}
	for (int i = 0; i < expression.size(); i++)  //loop until end of the equation
	{
		/*if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
			return false;*/
		if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')  //if there is either a (, [, { we pop it to the stack
		{
			s.push(expression[i]);
		}
		char x;
		switch (expression[i]) //check the next element for a closing bracket
		{
		case ')': //if it is this 

			// Store the top element in x and pops it
			x = s.top();
			s.pop();
			if (x == '{' || x == '[') //check the paranthesis popped is the same
				return false;  //return false if the found one is not this
			break;

		case '}':

			// Store the top element in x
			x = s.top();
			s.pop();
			if (x == '(' || x == '[')
				return false;
			break;

		case ']':

			// Store the top element in x 
			x = s.top();
			s.pop();
			if (x == '(' || x == '{')
				return false;
			break;
		}
	}
	if (!s.empty())
		return false;
	if (s.empty())
		return true;
}

//driver code to perform the task
int main()
{
	//getting input from file
	ifstream file("formulas.txt");
	//creating the output text file
	ofstream output("result.txt");
	string input;
	if (file.good())	//parsing the file
	{
		while (getline(file, input))
		{
			if (input[input.length() - 1] != '=')
			{
				cout << "E" << endl << endl;
				output << "E" << endl << endl;
			}
			else if (IsParanthesisBalanced(input))
			{
				expression = &input[0];
				float result = CalculateExpression();
				result = roundf(result * 100) / 100;
				cout << input << " " << result << endl << endl;
				output << input << " " << result << endl << endl;
			}
			else
			{	
				cout << "E" << endl << endl;
				output << "E" << endl << endl;
			}
		}
	}

	system("pause");
	return 0;
}