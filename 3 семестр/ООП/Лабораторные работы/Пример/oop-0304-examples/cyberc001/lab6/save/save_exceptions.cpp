#include "save_exceptions.h"

#include <sstream>

save_error_unexpected_eof::save_error_unexpected_eof(size_t op_sz) : op_sz(op_sz)
{
	std::stringstream ss;
	ss << "Unexpected EOF on operation of size " << op_sz;
	msg = ss.str();
}

const char* save_error_unexpected_eof::what()
{
	return msg.c_str();
}


save_error_unknown_class_name::save_error_unknown_class_name(std::string class_name) : class_name(class_name)
{
	std::stringstream ss;
	ss << "Unknown class name " << class_name;
	msg = ss.str();
}

const char* save_error_unknown_class_name::what()
{
	return msg.c_str();
}
