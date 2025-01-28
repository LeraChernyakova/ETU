#ifndef SAVE_EXCEPTIONS_H
#define SAVE_EXCEPTIONS_H

#include <exception>
#include <string>

class save_error_unexpected_eof : public std::exception
{
	private:

	size_t op_sz;
	std::string msg;


	public:

	save_error_unexpected_eof(size_t op_sz);

	virtual const char* what();
};

class save_error_unknown_class_name : public std::exception
{
	private:

	std::string class_name;
	std::string msg;


	public:

	save_error_unknown_class_name(std::string class_name);

	virtual const char* what();
};

#endif
