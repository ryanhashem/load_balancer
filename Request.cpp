/**
 * @file Request.cpp
 * @brief Implementation file for the Request struct constructors
 * @details Defines default and parameterized construction behavior for request
 *          objects used by the load balancer simulation.
 */

#include "Request.h"

/**
 * @brief Default constructor for Request
 * @details Initializes a request to a neutral/empty state:
 *          requestID = -1, empty IP strings, time = 0,
 *          timeLeft = 0, and jobType = 'N'.
 */
Request::Request() {
    this->requestID = -1;
    this->ipIn = "";
    this->ipOut = "";
    this->time = 0;
    this->timeLeft = 0;
    this->jobType = 'N';
}

/**
 * @brief Parameterized constructor for Request
 * @param requestID Unique identifier for the request
 * @param ipIn Source IP address
 * @param ipOut Destination IP address
 * @param time Total processing time required for this request
 * @param jobType Request type/category
 * @details Initializes all request fields and sets `timeLeft` to the initial
 *          `time` value so processing can decrement remaining work over time.
 */
Request::Request(int requestID, std::string ipIn, std::string ipOut, int time, char jobType){

    this->requestID = requestID;

    this->ipIn = ipIn;
    this->ipOut = ipOut;

    this->time = time;
    this->timeLeft = time;

    this->jobType = jobType;
}