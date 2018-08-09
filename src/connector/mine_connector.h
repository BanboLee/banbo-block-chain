/********************************************
 * Author: banbo <banbo777@163.com>
 * File: mine_connector.h
 * Date: 2018-08-02
 * Version: 1.0.0.0
 * Brief:
 ********************************************/
#ifndef BANBO__CHAIN_MINE_CONNECTOR_H
#define BANBO__CHAIN_MINE_CONNECTOR_H

#include "server.h"
#include "chain_manager.h"

namespace bbc {
    class MineConnector : public Connector {
    public:
        MineConnector(ChainManager *chain_manager) : _chain_manager(chain_manager) {}
        ~MineConnector() {}

        const char* uri() const { return "/banbo/mine"; }
        int get(Connection *conn, Request *request);
    private:
        ChainManager *_chain_manager;
    };
}

#endif  //BANBO__CHAIN_MINE_CONNECTOR_H