/********************************************
 * Author: banbo <banbo777@163.com>
 * File: demo_connector.h
 * Date: 2018-07-23
 * Version: 1.0.0.0
 * Brief:
 ********************************************/
#ifndef BANBO__CHAIN_DEMO_CONNECTOR_H
#define BANBO__CHAIN_DEMO_CONNECTOR_H

#include "server.h"

namespace bbc {
    class DemoConnector : public Connector {
    public:
        const char* uri() const { return "/banbo/demo"; }
        int run(Connection *conn, Request *request);
    };
}

#endif  //BANBO__CHAIN_DEMO_CONNECTOR_H