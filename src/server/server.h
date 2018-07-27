/********************************************
 * Author: banbo <banbo777@163.com>
 * File: server.h
 * Date: 2018-07-19
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#ifndef BANBO_CHAIN_SERVER_H
#define BANBO_CHAIN_SERVER_H

#include <string>
#include <map>
#include "connector.h"

namespace bbc {
    
    typedef std::map<std::string, Connector*> Url2Connector;
    static Url2Connector _connectors;
    
    enum HttpStatusCode {
        HTTP_STATUS_OK = 200,
        HTTP_STATUS_URI_NOT_FOUND = 404
    };

    static const std::string DEFAULT_PORT = "8080";
    class HttpServer {
    public:
        HttpServer() : _port(DEFAULT_PORT) {}
        HttpServer(std::string &port) : _port(port) {}
        ~HttpServer() {}

        int start(bool &g_signal_quit);
        static void ev_handler(Connection *c, int ev, void *p);
        int connector_registor(Connector *connector);
        int reply_text(Connection *conn, std::string &response);
    private:
        const std::string _port;
    };
}

#endif   //BANBO_CHAIN_SERVER_H
