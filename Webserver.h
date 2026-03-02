/**
 * @file Webserver.h
 * @brief Header file for the Webserver class
 * @details Defines the Webserver class used to represent individual web servers
 *          in the load balancer system that process incoming requests.
 */

#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include "Request.h"

/**
 * @class Webserver
 * @brief Represents a web server in the load balancer system
 * @details Manages the processing of requests assigned to it by the load balancer.
 *          Each webserver has a unique ID and can process one request at a time.
 */
class Webserver {
    private:
        int webserverID;      ///< Unique identifier for this web server
        Request request;      ///< Currently assigned request being processed

    public:
        /**
         * @brief Constructor for Webserver
         * @details Creates a new web server with the specified ID
         * @param webserverID Unique identifier for the web server
         */
        Webserver(int webserverID);
        
        /**
         * @brief Gets the web server's ID
         * @return The unique identifier of this web server
         */
        int getID();
        
        /**
         * @brief Assigns a new request to this web server
         * @details Sets the current request for this web server to process
         * @param request The request to be processed by this server
         */
        void newRequest(Request request);
        
        /**
         * @brief Processes the current request
         * @details Decrements the time remaining on the current request,
         *          simulating one clock cycle of processing
         */
        void processRequest();
        
        /**
         * @brief Checks if the web server is available
         * @return true if the server is idle/available, false if busy processing a request
         */
        bool getStatus();
};


#endif