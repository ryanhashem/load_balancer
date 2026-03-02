#ifndef _REQUEST_H
#define _REQUEST_H

#include <string>

struct Request {
    public:
        int requestID; 
        std::string ipIn; 
        std::string ipOut;
        int time;
        int timeLeft; 
        char jobType; 
        Request();
        Request(int requestID, std::string ipIn, std::string ipOut, int time, char jobType);
};

#endif