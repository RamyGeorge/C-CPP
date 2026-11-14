#include "fraction.h"
#include <iostream>

int main(){
	fraction a(1,2);
	fraction b(1,3);

	fraction c = a+b;

	fraction d(1,2);
	fraction e(2,4);

	d+= e;


	std::cout << c.getnum() << "/" << c.getdenum() << "\n";
	std::cout << d.getnum() << "/" << d.getdenum() << "\n";
	return 0;

};
