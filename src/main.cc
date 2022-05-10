#ifdef __GNUC__
    #if __GNUC__ < 9 || __GNUC_MINOR__ < 4
        #include <iostream>
        int main() { std::cout << "Compiler Not Supported. Please use GCC 9.4.0 or higher to compile StrixCC.\n"; }
    #else
        #include "Chess/Engine.hh"
        int main(){
            StrixCC::Main();
        }
    #endif
#endif

#ifndef __GNUC__
    #include <iostream>
    int main() { std::cout << "Compiler Not Supported. Please use GCC 9.4.0 or higher to compile StrixCC.\n"; }
#endif