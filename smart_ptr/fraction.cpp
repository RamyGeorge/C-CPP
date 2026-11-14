#include "fraction.h"

int gcd(int x, int y){
	if (y == 0) return x;
	else return gcd(y,x%y);

};
fraction::fraction(int x, int y){
	this->numerator = x;
	this->denumerator = y;
};
fraction fraction::operator+(const fraction& other) const{
	int fraction_gcd = gcd(this->denumerator, other.denumerator);
	int lcm = (this->denumerator * other.denumerator) / fraction_gcd;
	int orignum = this->numerator *  lcm / this->denumerator;
	int othernum = other.numerator * lcm / other.denumerator;
	fraction x(orignum + othernum, lcm);
	return x;
};

fraction fraction::operator-(const fraction& other) const {
	int fraction_gcd = gcd(this->denumerator, other.denumerator);
          int lcm = (this->denumerator * other.denumerator) / fraction_gcd;
          int orignum = this->numerator *  lcm / this->denumerator;
          int othernum = other.numerator * lcm / other.denumerator;
          fraction x(orignum - othernum, lcm);
          return x;
};

fraction fraction::operator*(const fraction& other) const{
	fraction res(this->numerator * other.numerator,this->denumerator * other.denumerator);
	return res;
};

fraction fraction::operator/(const fraction& other) const {
	fraction res(this->numerator * other.denumerator,other.numerator* this->denumerator);
	return res;
};

bool	fraction::operator==(const fraction& other) const {
       int gcdfirst = gcd(this->numerator,this->denumerator);
	int gcdsecond = gcd(other.numerator,other.denumerator);
 	fraction first(this->numerator/gcdfirst,this->denumerator/gcdfirst);
	fraction second(other.numerator/gcdsecond,other.denumerator/gcdsecond);
	return ((first.numerator == second.numerator) && (first.denumerator == second.denumerator));	
};

fraction& fraction::operator+=(const fraction& other){
	
	int fraction_gcd = gcd(this->denumerator, other.denumerator);
	int lcm = (this->denumerator * other.denumerator) / fraction_gcd;
	int orignum = this->numerator *  lcm / this->denumerator;
	int othernum = other.numerator * lcm / other.denumerator;
	this->numerator = (orignum + othernum);
	this->denumerator = lcm;
	int finalgcd = gcd(this->numerator,this->denumerator);
	this->numerator/=finalgcd;
	this->denumerator/= finalgcd;

	return *this;

};



int fraction::getnum() const { return this->numerator;};
int fraction::getdenum() { return this->denumerator;};
