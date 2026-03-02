/**
 * @file Webserver.cpp
 * @brief Implementation file for the Webserver class
 * @details Implements webserver construction, request assignment, processing,
 *          and status inspection used by the load balancer simulation.
 */

#include "Webserver.h"

/**
 * @brief Constructs a Webserver with a specific identifier
 * @param webserverID Unique identifier for this webserver
 * @details Initializes this server with the given ID and an empty/default
 *          request state.
 */
Webserver::Webserver(int webserverID) {
    this->webserverID = webserverID;
    request = Request();
}

/**
 * @brief Gets the unique identifier of this webserver
 * @return Webserver ID
 */
int Webserver::getID() {
    return webserverID;
}

/**
 * @brief Checks whether this webserver is available
 * @return true when no active request remains (`timeLeft <= 0`), false otherwise
 */
bool Webserver::getStatus() {
    return request.timeLeft <= 0;
}

/**
 * @brief Assigns a new request to this webserver
 * @param request Request to be processed
 */
void Webserver::newRequest(Request request) {
    this->request = request;
}

/**
 * @brief Processes the current request for one simulation cycle
 * @details Decrements remaining processing time by 1 when a request is active.
 */
void Webserver::processRequest() {
    if (request.timeLeft > 0) {
        request.timeLeft--;
    }
}