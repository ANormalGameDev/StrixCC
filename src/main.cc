#if (defined(__clang__) && __clang_major__ >= 10) || (defined(__GNUC__) && __GNUC__ >= 9)
    #include "Engine/Engine.hh"
    int main(){
        StrixCC::Run();
    }
#else
    #include <iostream>
    int main(){
        printf("This version of StrixCC was not compiled with a supported compiler. Please use GCC 9.4.0+ or Clang 10.0.0+ for compiling the source code.\n");
    }
#endif