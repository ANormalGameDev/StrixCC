#ifndef UCI_HH
#define UCI_HH

#include <map>
#include <string>
#include <vector>
#include <iostream>

namespace StrixC {
    namespace UCI {
        extern std::map<std::string, void(*)(std::vector<std::string>)> func_map;
        void Loop();
    }
}

#endif