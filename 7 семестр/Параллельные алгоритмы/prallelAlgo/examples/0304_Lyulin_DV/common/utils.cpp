#include <utils.h>

bool str_to_size( const std::string& str, std::size_t& num )
{
     try
     {
          num = std::stoul( str );
     }
     catch ( ... )
     {
          return false;
     }
     return true;
}
