#include "LoadBalancer.h"
#include <string>
#include <random>
#include <iostream>
#include <fstream>

//I used AI to write this small function to generate a random number between 1 - 20
//Prompt: make a small c++ function that returns a random number from 1 - 20
int randomNum() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 20);
    return dist(gen);
}

//I used AI to write this small function to make a random IP address.
//Prompt: make a small c++ function that returns a random ip address as an std::string
std::string randomIP() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 255);

    return std::to_string(dist(gen)) + "." +
           std::to_string(dist(gen)) + "." +
           std::to_string(dist(gen)) + "." +
           std::to_string(dist(gen));
}


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
}

void LoadBalancer::run(int numClockCycles) {

    currTime = 0;

    while (currTime < numClockCycles) {
        makeRequest();
        distributeRequests();
        processRequests();
        currTime++;
    }

    std::cout << "Simulation is done. Number of requests processed: " << numRequestsProcessed << std::endl;

    file << "Simulation is done. Number of requests processed: " << numRequestsProcessed << std::endl;

    file.close();
}

int LoadBalancer::getNextRequestID() {
    return currRequestID++;
}

void LoadBalancer::distributeRequests() {
    for (int i = 0; i < webservers.size(); i++) {
        if (webservers[i].getStatus() && (requestQueue.size() > 0)){

            webservers[i].newRequest(requestQueue.front());

            file << "Time: " << currTime << ", request " << requestQueue.front().requestID << " is now being processed on webserver " << webservers[i].getID() << std::endl;

            requestQueue.pop();

        }
    }
}

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
