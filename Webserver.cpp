#include "Webserver.h"

Webserver::Webserver(int webserverID) {
    this->webserverID = webserverID;
    request = Request();
}

int Webserver::getID() {
    return webserverID;
}

bool Webserver::getStatus() {
    return request.timeLeft <= 0;
}

void Webserver::newRequest(Request request) {
    this->request = request;
}

void Webserver::processRequest() {
    if (request.timeLeft > 0) {
        request.timeLeft--;
    }
}