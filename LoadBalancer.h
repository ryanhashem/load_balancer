#ifndef _LOAD_BALANCER_H
#define _LOAD_BALANCER_H

#include <queue>
#include "Request.h"
#include <vector>
#include "Webserver.h"
#include <fstream>


class LoadBalancer {
    private:
        int loadBalancerID;
        std::queue<Request> requestQueue;
        std::vector<Webserver> webservers;
        int currTime;
        int currRequestID;
        std::ofstream file;
        int numRequestsProcessed;
        int startingQSize;

        void makeRequest();
        void distributeRequests();
        void processRequests();
        int getNextRequestID();

    public:
        LoadBalancer(int loadBalancerID, int numWebservers);
        void run(int numClockCycles);

        
};


#endif