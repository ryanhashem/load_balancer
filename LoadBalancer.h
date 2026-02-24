#ifndef _LOAD_BALANCER_H
#define _LOAD_BALANCER_H

#include <queue>
#include "Request.h"
#include <vector>
#include "Webserver.h"

class LoadBalancer {
    private:
        int loadBalancerID;
        std::queue<Request> requestQueue;
        std::vector<Webserver> webservers;
        int time;
};


#endif