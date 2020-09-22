#ifndef STUDENT_H_
#define STUDENT_H_

#include<iostream>
#include<string>
#include<valarray>

class Student
{
private:
	typedef std::valarray<double> ArrayDb;
	std::string _name;
	ArrayDb _scores;
	// for scores output
	//std::ostream& arr_out(std::ostream& os) const;

public:
	Student()
		:_name("Null Student")
		,_scores()
	{}
	Student(const std::string& s)
		:_name(s)
		,_scores()
	{}
	Student(int n)
		:_name("Nully")
		,_scores(n)
	{}
	Student(const std::string& s, int n)
		:_name(s)
		,_scores(n)
	{}
	
	~Student()
	{}

	double Average() const;
	const std::string& Name() const;
	double& operator[](int i);
	double operator[](int i) const;
	
	friend std::istream& operator>>(std::istream& is, Student& s);
	friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif 
