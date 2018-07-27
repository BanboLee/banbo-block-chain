/********************************************
 * Author: banbo <banbo777@163.com>
 * File: connector.h
 * Date: 2018-07-23
 * Version: 1.0.0.0
 * Brief:
 ********************************************/
#ifndef BANBO__CHAIN_CONNECTOR_H
#define BANBO__CHAIN_CONNECTOR_H

#include "mongoose.h"

namespace bbc{

    typedef http_message Request;
    typedef mg_connection Connection;

    class Connector {
    public:
        virtual ~Connector() {}
        virtual int init() { return 0; }
        virtual const char* uri() const = 0;
        virtual int run(Connection *conn, Request *request) = 0;
    };
}

#endif  //BANBO__CHAIN_CONNECTOR_H