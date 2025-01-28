#include "key_bind_manager.h"

#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

#include <iostream>

std::map<int, std::string> key_bind_manager::binds;

void key_bind_manager::init(std::istream& _in)
{
	int ch;
	std::vector<char> bind; size_t bind_i = 0;
	std::vector<char> key; size_t key_i = 0;
	const size_t buf_growth = 8;

	while(1)
	{
		while( (ch = _in.get()) != '=' ){
			if(ch == std::char_traits<char>::eof()) return;
			if(std::isspace(ch)) continue;
			if(bind_i >= bind.capacity())
				bind.resize(bind.size() + buf_growth);
			bind[bind_i++] = ch;
		}
		while( (ch = _in.get()) != ',' ){
			if(ch == std::char_traits<char>::eof()) break;
			if(std::isspace(ch)) continue;
			if(key_i >= key.capacity())
				key.resize(key.size() + buf_growth);
			key[key_i++] = ch;
		}

		bind[bind_i] = '\0'; key[key_i] = '\0';
		std::string _bind;
		for(auto i = bind.begin(); *i; ++i) _bind += *i;
		std::string _key;
		for(auto i = key.begin(); *i; ++i) _key += *i;

		binds.insert({key_name_to_code(_key), _bind});
		bind_i = 0; key_i = 0;
	}
}

std::string key_bind_manager::get_bind(int key)
{
	auto b = binds.find(key);
	if(b == binds.end())
		return "";
	return b->second;
}


static inline int multichar_to_int(const char* chars)
{
	int res = 0;
	for(; *chars; ++chars)
	{ res *= 256; res += *chars; }
	return res;
}
int key_bind_manager::key_name_to_code(const std::string& name)
{
	static const std::map<std::string, int> transl_map {
	{"enter", '\n'}, {"backspace", '\b'},
	{"leftarrow", multichar_to_int("\033[D")},
	{"rightarrow", multichar_to_int("\033[C")},
	{"uparrow", multichar_to_int("\033[A")},
	{"downarrow", multichar_to_int("\033[B")}
	};

	auto kcode = transl_map.find(name);
	if(kcode == transl_map.end())
		return name[0];

	return kcode->second;
}
