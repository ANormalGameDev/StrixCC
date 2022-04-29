#include "uci.hh"

namespace StrixC {
    namespace UCI {
        std::map<std::string, void(*)(std::vector<std::string>)> func_map;

        void RegisterCommand(std::string command, void(*func)(std::vector<std::string>)){
            func_map[command] = func;
        }

        void Loop(){
            std::string cmd;
            while (getline(std::cin, cmd) && !cmd.empty()){
                std::cout << cmd << "\n";
            }
        }
    }
}