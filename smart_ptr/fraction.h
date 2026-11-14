class fraction {
	private:
		int numerator;
		int denumerator;

	public:
		fraction(int,int);
		fraction operator+(const fraction& otherfraction) const;
		fraction operator-(const fraction& otherfraction) const;
		fraction operator*(const fraction& otherfraction) const;
		fraction operator/(const fraction& otherfraction) const;
		fraction& operator+=(const fraction& otherfraction); // Notice the missing const at the end like the ones above. This is intentional. declaring a const at the end of a member function entails that the programmer intends to not change the object.

		bool operator==(const fraction& otherfraction) const;
		int getnum() const;
		int getdenum();
};	
