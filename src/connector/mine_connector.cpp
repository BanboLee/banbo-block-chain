/********************************************
 * Author: banbo <banbo777@163.com>
 * File: mine_connector.cpp
 * Date: 2018-08-02
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include <string>
#include "mine_connector.h"
#include "bbc_log.h"
#include "common_utils.h"
#include "rapidjson/document.h"

namespace bbc {
    
int bbc::MineConnector::get(Connection *conn, Request *request) {

    int proof = _chain_manager->proof_of_work();
    std::string previous_hash = _chain_manager->previous_hash();

    // We must receive a reward for finding the proof.
    // The sender is "0" to signify that this node has mined a new coin.
    std::string sender = "0";
    std::string receiver = "1";
    double amount = 1.0;
    struct Transaction transaction = bbc::Transaction(sender, receiver, amount);
    _chain_manager->add_transaction(transaction);
    _chain_manager->create_block(proof, previous_hash);

    // Response
    rapidjson::Document d = _chain_manager->chain_json();

    std::string succ = serialize(d);
    reply_json(conn, succ);

    return 0;
}


}   // End bbc.