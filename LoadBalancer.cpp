/**
 * @file LoadBalancer.cpp
 * @brief Implementation for the LoadBalancer simulation logic
 * @details Contains helper utilities for random request generation and
 *          implementations of request creation, distribution, processing,
 *          and simulation reporting.
 */

#include "LoadBalancer.h"
#include <string>
#include <random>
#include <iostream>
#include <fstream>

/**
 * @brief Generates a random processing time. I used AI to write this small function to generate a random number between 1 - 20. Prompt: make a small c++ function that returns a random number from 1 - 20.
 * @return Random integer in the inclusive range [1, 20]
 */
int randomNum() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 20);
    return dist(gen);
}

/**
 * @brief Generates a random IPv4 address string. I used AI to write this small function to make a random IP address.Prompt: make a small c++ function that returns a random ip address as an std::string.
 * @return IPv4 address in dotted-decimal format
 */
std::string randomIP() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 255);

    return std::to_string(dist(gen)) + "." +
           std::to_string(dist(gen)) + "." +
           std::to_string(dist(gen)) + "." +
           std::to_string(dist(gen));
}


/**
 * @brief Constructs a load balancer instance
 * @param loadBalancerID Unique identifier for this load balancer
 * @param numWebservers Number of webservers to initialize
 * @details Opens `log.txt`, initializes counters and time state, pre-fills
 *          the request queue with numWebservers * 100 requests, creates
 *          the configured number of webservers, and stores starting queue size.
 */
LoadBalancer::LoadBalancer(int loadBalancerID, int numWebservers) {

    file.open("log.txt");

    numRequestsProcessed = 0;

    this->loadBalancerID = loadBalancerID;
    currTime = 0;

    this->currRequestID = 0;

    for (int i = 0; i < (numWebservers * 100); i++) {
        makeRequest();
    }

    for (int i = 0; i < numWebservers; i++) {
        webservers.push_back(Webserver(i));
    }   

    startingQSize = requestQueue.size();
}

/**
 * @brief Runs the load balancer simulation
 * @param numClockCycles Number of clock cycles to simulate
 * @details For each cycle: creates one request, distributes queued requests,
 *          and processes active requests. When complete, prints and logs
 *          summary statistics and closes the log file.
 */
void LoadBalancer::run(int numClockCycles) {

    currTime = 0;

    while (currTime < numClockCycles) {
        makeRequest();
        distributeRequests();
        processRequests();
        currTime++;
    }

    int activeWebservers = 0;
    int inactiveWebservers = 0;


    for (int i = 0; i < webservers.size(); i++) {

        if (webservers[i].getStatus()) {
            inactiveWebservers++;
        } else {
            activeWebservers++;
        }
    }

    std::cout << "Simulation is done." << std::endl;
    std::cout << "Number of requests processed: " << numRequestsProcessed << std::endl;
    std::cout << "Starting queue size: " << startingQSize << std::endl;
    std::cout << "Ending queue size: " << requestQueue.size() << std::endl;
    std::cout << "Range for task times: 1 - 20 clock cycles" << std::endl;
    std::cout << "Active webservers: " << activeWebservers << std::endl;
    std::cout << "Inactive webservers: " << inactiveWebservers << std::endl;

    file << "Simulation is done." << std::endl;
    file << "Number of requests processed: " << numRequestsProcessed << std::endl;
    file << "Starting queue size: " << startingQSize << std::endl;
    file << "Ending queue size: " << requestQueue.size() << std::endl;
    file << "Range for task times: 1 - 20 clock cycles" << std::endl;
    file << "Active webservers: " << activeWebservers << std::endl;
    file << "Inactive webservers: " << inactiveWebservers << std::endl;

    file.close();
}

/**
 * @brief Produces the next unique request ID
 * @return Next request ID (counter is post-incremented)
 */
int LoadBalancer::getNextRequestID() {
    return currRequestID++;
}

/**
 * @brief Assigns queued requests to available webservers
 * @details Iterates through all webservers and, for each available server,
 *          assigns the front request from the queue, logs the assignment,
 *          and pops that request from the queue.
 */
void LoadBalancer::distributeRequests() {
    for (int i = 0; i < webservers.size(); i++) {
        if (webservers[i].getStatus() && (requestQueue.size() > 0)){

            webservers[i].newRequest(requestQueue.front());

            file << "Time: " << currTime << ", request " << requestQueue.front().requestID << " is now being processed on webserver " << webservers[i].getID() << std::endl;

            requestQueue.pop();

        }
    }
}

/**
 * @brief Processes one simulation cycle on all webservers
 * @details Calls `processRequest()` on every webserver, detects request
 *          completion transitions, logs completion events, and increments
 *          the processed request count.
 */
void LoadBalancer::processRequests() {

    for (int i = 0; i < webservers.size(); i++) {

        bool hadRequest = !webservers[i].getStatus();

        webservers[i].processRequest();

        if (hadRequest && webservers[i].getStatus()) {

            file << "Time: " << currTime << ", webserver "<< webservers[i].getID() << " finished processing its request" << std::endl;

            numRequestsProcessed++;
        }
    }
}

/**
 * @brief Creates and enqueues a new request
 * @details Generates a unique request ID, random processing time, random input
 *          and output IP addresses, and assigns a job type (`'P'` for times
 *          less than 10, otherwise `'S'`). Logs the request creation event.
 */
void LoadBalancer::makeRequest() {

    int requestID = getNextRequestID();

    int time = randomNum();
    std::string ipIn = randomIP();
    std::string ipOut = randomIP();

    char jobType = 0;

    if (time < 10) {
        jobType = 'P';
    } else {
        jobType = 'S';
    }

    Request request(requestID, ipIn, ipOut, time, jobType);

    requestQueue.push(request);

    file << "Time: " << currTime << ", request " << requestID << " created" << std::endl;

}
