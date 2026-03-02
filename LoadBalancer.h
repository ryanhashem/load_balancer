/**
 * @file LoadBalancer.h
 * @brief Header file for the LoadBalancer class
 * @details Defines the LoadBalancer class which manages incoming requests
 *          and distributes them to available web servers for processing.
 */

#ifndef _LOAD_BALANCER_H
#define _LOAD_BALANCER_H

#include <queue>
#include "Request.h"
#include <vector>
#include "Webserver.h"
#include <fstream>

/**
 * @class LoadBalancer
 * @brief Manages request distribution and processing across multiple web servers
 * @details The LoadBalancer simulates a load balancing system that creates requests,
 *          queues them, distributes them to available web servers, and tracks
 *          processing statistics. Logs all activities to a file.
 */
class LoadBalancer {
    private:
        int loadBalancerID;                    ///< Unique identifier for this load balancer
        std::queue<Request> requestQueue;       ///< Queue of pending requests awaiting processing
        std::vector<Webserver> webservers;      ///< Collection of web servers managed by this load balancer
        int currTime;                           ///< Current clock cycle in the simulation
        int currRequestID;                      ///< Counter for generating unique request IDs
        std::ofstream file;                     ///< Output file stream for logging activities
        int numRequestsProcessed;               ///< Total count of completed requests
        int startingQSize;                      ///< Initial size of the request queue

        /**
         * @brief Creates a new request and adds it to the queue
         * @details Generates a request with random IP addresses, processing time (1-20 cycles),
         *          and job type ('P' for time < 10, 'S' otherwise). Logs the creation event.
         */
        void makeRequest();
        
        /**
         * @brief Distributes queued requests to available web servers
         * @details Iterates through all web servers and assigns the front request from
         *          the queue to any available server. Logs each assignment.
         */
        void distributeRequests();
        
        /**
         * @brief Processes requests on all web servers for one clock cycle
         * @details Calls processRequest() on each server, tracks completed requests,
         *          and logs when servers finish processing.
         */
        void processRequests();
        
        /**
         * @brief Generates and returns the next unique request ID
         * @return The next request ID (post-incremented)
         */
        int getNextRequestID();

    public:
        /**
         * @brief Constructor for LoadBalancer
         * @details Initializes the load balancer with specified parameters, creates
         *          initial requests (numWebservers * 100), initializes web servers,
         *          and opens the log file.
         * @param loadBalancerID Unique identifier for this load balancer
         * @param numWebservers Number of web servers to manage
         */
        LoadBalancer(int loadBalancerID, int numWebservers);
        
        /**
         * @brief Runs the load balancer simulation
         * @details Executes the simulation for the specified number of clock cycles.
         *          Each cycle creates new requests, distributes queued requests to
         *          available servers, and processes them. After completion, prints
         *          and logs simulation statistics.
         * @param numClockCycles Number of clock cycles to run the simulation
         */
        void run(int numClockCycles);

        
};


#endif