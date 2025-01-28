#ifndef KEY_BIND_MANAGER_H
#define KEY_BIND_MANAGER_H

#include <istream>
#include <map>

class key_bind_manager
{
	private:

	static std::map<int, std::string> binds;


	public:

	static void init(std::istream& _in);

	// возвращает пустую строку в случае отсутствия назначения клавиши
	static std::string get_bind(int key);

	// преобразует имя клавиши в код клавиши.
	static int key_name_to_code(const std::string& name);
};

#endif
