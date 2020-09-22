#ifndef STUDENT_H_
#define STUDENT_H_

#include<iostream>
#include<string>
#include<valarray>

class Student : private std::string,private std::valarray<double>
{
private:
	typedef std::valarray<double> ArrayDb;
	// for scores output
	//std::ostream& arr_out(std::ostream& os) const;

public:
	Student()
		:std::string()
		,ArrayDb()
	{}
	Student(const std::string& s)
		:std::string(s)
		,ArrayDb()
	{}
	Student(int n)
		:std::string("Nully")
		,ArrayDb(n)
	{}
	Student(const std::string& s, int n)
		:std::string("Nully")
		,ArrayDb(n)
	{}
	
	~Student()
	{}

	double Average() const;
	const std::string& Name() const;
	double& operator[](int i);
	double operator[](int i) const;
	int size() const { return ArrayDb::size(); }
	
	friend std::istream& operator>>(std::istream& is, Student& s);
	friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif 
