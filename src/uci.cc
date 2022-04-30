#include "uci.hh"

namespace StrixC {
    namespace UCI {
        std::map<std::string, void(*)(std::vector<std::string>)> func_map;
        
        void uci(std::vector<std::string> args);

        void RegisterCommand(std::string command, void(*func)(std::vector<std::string>)){
            func_map[command] = func;
        }

        void Init(){
            RegisterCommand("uci", &uci);
        }

        void uci(std::vector<std::string> args){
            std::cout << "id name StrixC\n";
            std::cout << "id author Read Contributors.txt\n";
        }

        void Loop(){
            std::string cmd;
            while (getline(std::cin, cmd) && !cmd.empty()){
                // Tokenizes the line received as input
                std::stringstream cmdstream(cmd);
                std::string arg;
                std::vector<std::string> args;
                while (getline(cmdstream, arg, ' ')){
                    args.push_back(arg);
                }

                // Checks if the command is registered
                if (func_map[args[0]] != nullptr){
                    // Runs the registered function for the command
                    func_map[args[0]](args);
                }
            }
        }
    }
}