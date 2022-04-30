#ifndef UCI_HH
#define UCI_HH

#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

namespace StrixC {
    namespace UCI {
        typedef std::map<std::string, std::string> UCIOptions;
        typedef std::map<std::string, void(*)(std::vector<std::string>)> CommandRegister;

        extern UCIOptions options;
        extern CommandRegister func_map;
        void Init();
        void Loop();
    }
}

#endif