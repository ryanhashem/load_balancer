/**
 * @file Request.h
 * @brief Header file for the Request struct
 * @details Defines the Request structure used to represent incoming web requests
 *          in the load balancer system.
 */

#ifndef _REQUEST_H
#define _REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a web request in the load balancer system
 * @details Contains information about a request including its ID, IP addresses,
 *          processing time, and job type.
 */
struct Request {
    public:
        int requestID;        ///< Unique identifier for the request
        std::string ipIn;     ///< Incoming IP address of the request
        std::string ipOut;    ///< Outgoing IP address for the response
        int time;             ///< Total time required to process the request
        int timeLeft;         ///< Remaining time needed to complete the request
        char jobType;         ///< Type of job/request (e.g., 'P' for processing, 'S' for streaming)
        
        /**
         * @brief Default constructor
         * @details Creates a Request object with default values
         */
        Request();
        
        /**
         * @brief Parameterized constructor
         * @details Creates a Request object with specified values
         * @param requestID Unique identifier for the request
         * @param ipIn Incoming IP address
         * @param ipOut Outgoing IP address
         * @param time Total processing time required
         * @param jobType Type of job/request
         */
        Request(int requestID, std::string ipIn, std::string ipOut, int time, char jobType);
};

#endif