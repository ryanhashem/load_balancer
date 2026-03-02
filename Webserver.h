#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include "Request.h"

class Webserver {
    private:
        int webserverID; 
        Request request;

    public:
        Webserver(int webserverID);
        int getID();
        void newRequest(Request request);
        void processRequest();
        bool getStatus();
};


#endif