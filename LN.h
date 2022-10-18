#pragma once
#include <string_view>

#include <string>
#include <vector>

class LN
{
  public:
	LN();
	LN(std::string number);
	LN(long long number);
	LN(const LN& num);
	bool operator>(const LN& num) const;
	bool operator<(const LN& num) const;
	bool operator>=(const LN& num) const;
	bool operator<=(const LN& num) const;
	bool operator==(const LN& num) const;
	bool operator!=(const LN& num) const;
	const LN operator-(const LN& num) const;
	const LN operator+(const LN& num) const;
	const LN operator*(const LN& num) const;
	const LN operator/(const LN& num) const;
	const LN operator%(const LN& num) const;
	LN& operator=(const LN& num);
	LN& operator+=(const LN& num);
	LN& operator-=(const LN& num);
	LN& operator/=(const LN& num);
	LN& operator*=(const LN& num);
	LN& operator%=(const LN& num);
	std::string to_string();
	LN sqrtLN() const;

  private:
	void delLeadZeros();
	std::vector< unsigned int > digits;
	LN abs() const;
	int unicomp(const LN& num) const;
	LN subst(const LN& num) const;
	LN add(const LN& num) const;
	bool sign;
};
