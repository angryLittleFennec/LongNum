#include "LN.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

LN::LN()
{
	digits.push_back(0);
	sign = true;
}
LN::LN(std::string number)
{
	sign = 0;
	if (number == "NaN")
	{
		digits.push_back('N');
		digits.push_back('a');
		digits.push_back('N');
	}
	else
	{
		int pos;
		if (isdigit(number[0]))
			pos = 0;
		else
			pos = 1;
		if (number[0] == '-')
			sign = 0;
		else
			sign = 1;

		for (int i = pos; i < number.length(); i++)
			digits.push_back(number[i] - '0');
		delLeadZeros();
	}
}
LN::LN(long long number) : LN(std::to_string(number)) {}

LN::LN(const LN& num)
{
	sign = num.sign;
	digits = num.digits;
}

void LN::delLeadZeros()
{
	while (digits.size() > 1 && digits[0] == 0)
		digits.erase(digits.begin(), digits.begin() + 1);
}

std::string LN::to_string()
{
	std::string str;
	if (digits[0] == 78 && digits[1] == 97 && digits[2] == 78)
	{
		return (string) "NaN";
	}
	else
	{
		if (!sign)
			str += "-";
		for (unsigned int i = 0; i < digits.size(); i++)
			str += std::to_string(digits.at(i));
		return str;
	}
}

LN& LN::operator=(const LN& num)
{
	if (this == &num)
		return *this;
	sign = num.sign;
	digits = num.digits;
	return *this;
}
int LN::unicomp(const LN& num) const
{
	if (sign == num.sign && digits == num.digits)
		return 0;
	else
	{
		if (sign == true && num.sign == false)
			return 1;
		if (sign == false && num.sign == true)
			return -1;
		if (digits.size() > num.digits.size())
		{
			if (sign == 0)
				return -1;
			return 1;
		}
		if (digits.size() < num.digits.size())
		{
			if (sign == 0)
				return 1;
			return -1;
		}
		for (int i = 0; i < digits.size(); i++)
		{
			if (digits.at(i) > num.digits[i])
			{
				if (sign == 0)
					return -1;
				return 1;
			}
			if (digits.at(i) < num.digits[i])
			{
				if (sign == 0)
					return 1;
				return -1;
			}
		}
		return -1;
	}
}

bool LN::operator==(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return false;
	if (unicomp(num) == 0)
		return true;
	return false;
}

bool LN::operator!=(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return 1;
	if (unicomp(num) != 0)
		return true;
	return false;
}

bool LN::operator>(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return false;
	if (unicomp(num) == 1)
		return true;
	return false;
}

bool LN::operator<(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return false;
	if (unicomp(num) == -1)
		return true;
	return false;
}

bool LN::operator<=(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return false;
	return (*this < num) || (*this == num);
}

bool LN::operator>=(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return false;
	return (*this > num) || (*this == num);
}

LN LN::abs() const
{
	LN a(*this);
	a.sign = true;
	return a;
}

LN LN::subst(const LN& num) const
{
	LN sub;
	if (this->abs() >= num.abs())
	{
		sub.digits.clear();
		int index1 = digits.size() - 1;
		int index2 = num.digits.size() - 1;
		int carry = 0;
		sub.sign = sign;
		int k1, k2;
		while (index1 >= 0 || index2 >= 0)
		{
			if (index1 >= 0)
				k1 = digits[index1];
			else
				k1 = 0;
			if (index2 >= 0)
				k2 = num.digits[index2];
			else
				k2 = 0;
			auto digitsub = k1 - k2 - carry;
			if (digitsub < 0)
			{
				carry = 1;
				digitsub += 10;
			}
			else
				carry = 0;
			sub.digits.push_back(digitsub);
			index1--;
			index2--;
		}
		std::reverse(sub.digits.begin(), sub.digits.end());
		sub.delLeadZeros();
	}
	else
	{
		sub = (num - (*this));
		sub.sign = !sub.sign;
	}
	return sub;
}

LN LN::add(const LN& num) const
{
	LN sum;
	sum.digits.clear();
	sum.sign = sign;
	unsigned int carry = 0;
	int index1 = digits.size() - 1;
	int index2 = num.digits.size() - 1;
	int k1, k2;
	while (index1 >= 0 || index2 >= 0)
	{
		if (index1 >= 0)
			k1 = digits[index1];
		else
			k1 = 0;
		if (index2 >= 0)
			k2 = num.digits[index2];
		else
			k2 = 0;
		auto digitsum = k1 + k2 + carry;

		carry = digitsum / 10;
		digitsum %= 10;

		sum.digits.push_back(digitsum);
		index1--;
		index2--;
	}
	if (carry != 0)
		sum.digits.push_back(carry);
	std::reverse(sum.digits.begin(), sum.digits.end());

	return sum;
}

const LN LN::operator-(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return LN("NaN");
	LN sub;
	if ((digits.at(0) == 0 && num.digits[0] == 0))
		return sub;
	if (sign == num.sign)
	{
		sub = subst(num);
	}
	else
	{
		sub = add(num);
	}
	if (sub.digits[0] == 0 && sub.sign == false)
	{
		sub.sign = true;
	}
	return sub;
}

LN& LN::operator-=(const LN& num)
{
	*this = *this - num;
	return *this;
}

const LN LN::operator+(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return LN("NaN");
	LN sum;
	if (digits[0] == 0 && num.digits[0] == 0)
		return sum;
	if (sign == num.sign)
	{
		sum = add(num);
	}
	else
	{
		if (this->abs() > num.abs())
		{
			sum = subst(num);
		}
		else
		{
			sum = num.abs() - this->abs();
			sum.sign = num.sign;
		}
	}
	if (sum.digits[0] == 0 && sum.sign == false)
	{
		sum.sign = true;
	}
	return sum;
}

LN& LN::operator+=(const LN& num)
{
	*this = *this + num;
	return *this;
}

const LN LN::operator/(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return LN("NaN");
	LN buff;
	LN res;
	res.digits.clear();
	buff.digits.clear();
	if (num == LN(0))
		throw std::overflow_error("Division by zero exception");
	int cnt = 0;
	vector< int > ost;
	for (int i = 0; i < digits.size(); i++)
	{
		buff.digits.push_back(digits[i]);
		buff.delLeadZeros();
		if (buff < num.abs())
		{
			res.digits.push_back(0);
			continue;
		}
		int cnt;
		for (cnt = 0; buff > num.abs() || buff == num.abs(); cnt++)
		{
			buff = buff - num.abs();
		}
		res.digits.push_back(cnt);
	}
	res.delLeadZeros();
	res.sign = true;
	if (sign != num.sign && res.digits[0] != 0)
		res.sign = false;
	return res;
}

LN& LN::operator/=(const LN& num)
{
	*this = *this / num;
	return *this;
}

const LN LN::operator*(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return LN("NaN");
	size_t len = digits.size() + num.digits.size();
	LN res;

	res.sign = sign == num.sign;
	res.digits = vector< unsigned int >(len, 0);

	for (size_t i = 0; i < digits.size(); i++)
		for (size_t j = 0; j < num.digits.size(); j++)
			res.digits[i + j + 1] += digits[i] * num.digits[j];

	for (size_t i = len - 1; i > 0; i--)
	{
		res.digits[i - 1] += res.digits[i] / 10;
		res.digits[i] %= 10;
	}

	res.delLeadZeros();
	if (res.digits[0] == 0 && res.sign == false)
	{
		res.sign = true;
	}

	return res;
}

LN& LN::operator*=(const LN& num)
{
	*this = *this * num;
	return *this;
}

const LN LN::operator%(const LN& num) const
{
	if ((digits[0] == 78 && digits[1] == 97 && digits[2] == 78) || (num.digits[0] == 78 && num.digits[1] == 97 && num.digits[2] == 78))
		return LN("NaN");
	if (num == LN(0))
		throw std::overflow_error("Division by zero exception");
	LN res = (*this / num);
	res = res * num;
	res = *this - res;
	if (res.digits[0] == 0 && res.sign == false)
	{
		res.sign = true;
	}

	return res;
}

LN& LN::operator%=(const LN& num)
{
	*this = *this % num;
	return *this;
}

LN LN::sqrtLN() const
{
	if (digits[0] == 78 && digits[1] == 97 && digits[2] == 78)
		return LN("NaN");
	if (!sign)
	{
		throw std::overflow_error("negative num for sqrt");
	}
	if (*this == 0)
	{
		return *this;
	}
	LN left = 1;
	LN right = *this / 2 + 1;
	LN middle;
	LN sqr;
	while (left <= right)
	{
		middle = left + (right - left) / 2;
		sqr = middle * middle;
		if (sqr <= *this)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}
	return right;
}
