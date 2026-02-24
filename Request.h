#ifndef _REQUEST_H
#define _REQUEST_H

#include <string>

struct Request {
    private:
        int requestID;
        std::string ipIn;
        std::string ipOut;
        int time;
        char jobType;
};

#endif