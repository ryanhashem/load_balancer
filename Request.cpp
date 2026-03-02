#include "Request.h"

Request::Request() {
    this->requestID = -1;
    this->ipIn = "";
    this->ipOut = "";
    this->time = 0;
    this->timeLeft = 0;
    this->jobType = 'N';
}

Request::Request(int requestID, std::string ipIn, std::string ipOut, int time, char jobType){

    this->requestID = requestID;

    this->ipIn = ipIn;
    this->ipOut = ipOut;

    this->time = time;
    this->timeLeft = time;

    this->jobType = jobType;
}