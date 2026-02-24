#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include "Request.h"

class Webserver {
    private:
        int webserverID;
        Request request;
        bool requestProcessed;
};


#endif