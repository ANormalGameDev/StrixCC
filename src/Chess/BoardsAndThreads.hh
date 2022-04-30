#pragma once

#include <thread>
#include <vector>
#include <iostream>
#include <stdlib.h>

class Board {
    private:
        char pieces[64];
};

class BoardThreadManager {
    private:
        std::vector<Board> boards;
        std::vector<std::thread> threads;
        int maxThreads;
        int maxDepth;

        const int maxThreadsSupported = std::thread::hardware_concurrency();
        const int maxDepthAllowed = 26;
    public:
        void Go(Board board); // This Function will be called when the UCI Manager recieves the "go"
                              // command. This function will start all the threads and tell them all
                              // to start calculating.
        void SetMaxThreadsAmount(int amount){
            if (amount > 0 && amount < maxThreadsSupported){
                maxThreads = amount;
            }
        }
        void SetMaxDepth(int depth){
            if (depth > 0 && depth < maxDepthAllowed){
                maxDepth = depth;
            }
        }
};