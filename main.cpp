#include "LN.h"
#include "return_codes.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "wrong number of parameters");
		return ERROR_INVALID_PARAMETER;
	}
	ifstream in;
	in.open(argv[1]);
	if (!in)
	{
		fprintf(stderr, "you try to open the file that doesn't exist");
		return ERROR_FILE_NOT_FOUND;
	}

	ofstream out;
	out.open(argv[2]);
	if (!out)
	{
		remove(argv[2]);
		fprintf(stderr, "error while trying to open/create the file");
		in.close();
		return ERROR_FILE_NOT_FOUND;
	}
	vector< LN > stack;
	string a;
	string oper[14] = { "+", "-", "*", "/", "~", "==", "_", "%", "<=", ">=", "<", ">", "!=", "false" };
	while (in >> a)
	{
		if (a == "\n")
			break;
		string* p = find(oper, oper + 14, a);
		LN res = 0;
		if (p != oper + 14)
		{
			if (stack.size() > 1)
			{
				if (*p == (string) "+")
					res = stack[stack.size() - 2] + stack[stack.size() - 1];
				if (*p == (string) "*")
					res = stack[stack.size() - 2] * stack[stack.size() - 1];
				if (*p == (string) "-")
					res = stack[stack.size() - 2] - stack[stack.size() - 1];
				if (*p == (string) "/")
				{
					try
					{
						res = stack[stack.size() - 2] / stack[stack.size() - 1];
					} catch (overflow_error e)
					{
						res = LN("NaN");
					}
				}
				if (*p == (string) "==")
					res = stack[stack.size() - 2] == stack[stack.size() - 1];
				if (*p == (string) "%")
				{
					try
					{
						res = stack[stack.size() - 2] % stack[stack.size() - 1];
					} catch (overflow_error e)
					{
						res = LN("NaN");
					}
				}
				if (*p == (string) "!=")
					res = stack[stack.size() - 2] != stack[stack.size() - 1];
				if (*p == (string) "<=")
					res = stack[stack.size() - 2] <= stack[stack.size() - 1];
				if (*p == (string) ">=")
					res = stack[stack.size() - 2] >= stack[stack.size() - 1];
				if (*p == (string) "<")
					res = stack[stack.size() - 2] < stack[stack.size() - 1];
				if (*p == (string) ">")
					res = stack[stack.size() - 2] > stack[stack.size() - 1];
			}
			if (*p == (string) "_" && stack.size() > 0)
				res = stack[stack.size() - 1] * -1;
			if (*p == (string) "~")
			{
				try
				{
					res = stack[stack.size() - 1].sqrtLN();
				} catch (overflow_error e)
				{
					res = LN("NaN");
				}
			}

			if (stack.size() > 0)
				stack.pop_back();
			if ((*p != (string) "_" && *p != (string) "~") && stack.size() > 0)
				stack.pop_back();
			stack.push_back(res);
		}
		else
			stack.push_back(a);
	}
	for (size_t i = stack.size() - 1; i >= 0; i--)
		out << stack[i].to_string() << endl;

	in.close();
	out.close();
}
