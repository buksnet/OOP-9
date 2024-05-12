#pragma once
#include <iostream>

class BaseException : public std::exception {
public:
	virtual const char* what() = 0;
};

class ListEmptyException : public BaseException
{
protected:
	std::string msg;
public:
	ListEmptyException() { this->msg = "Empty list error! You are probably trying to delete an element from empty list!\n"; }
	virtual const char* what(){
	std::cout << msg;
	return "runtime_error";
	}
};

class ListIndexException : public BaseException
{
protected:
	std::string msg;
public:
	ListIndexException() { this->msg = "List index is bigger than its size, or less than 0."; }
	virtual const char* what() {
		std::cout << msg;
		return "runtime_error";
	}
};
