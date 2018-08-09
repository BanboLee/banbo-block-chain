/********************************************
 * Author: banbo <banbo777@163.com>
 * File: chain_manager.h
 * Date: 2018-07-27
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#ifndef BANBO_BLOCK_CHAIN_MANAGER_H
#define BANBO_BLOCK_CHAIN_MANAGER_H

#include <vector>               
#include <string>
#include <set>
#include <stdint.h>
#include <sstream>
#include "rapidjson/document.h"
#include "common_utils.h"

namespace bbc {

    struct Transaction {
        Transaction(std::string &_sender, std::string &_receiver, double& _amount)
                    : sender(_sender), receiver(_receiver), amount(_amount) {}

        inline std::string str() {
            std::stringstream ss;
            ss << sender << receiver << amount;
            return ss.str();
        }

        rapidjson::Value json(rapidjson::Document::AllocatorType& allocator);

        std::string sender;
        std::string receiver;
        double amount;
    };

    struct Block {
        inline std::string str() {
            std::stringstream ss;
            ss << index << timestamp << proof << previous_hash;
            for (std::vector<Transaction>::iterator it = transactions.begin(); it != transactions.end(); ++it) {
                ss << it->str();
            }
            return ss.str();
        }

        rapidjson::Value json(rapidjson::Document::AllocatorType& allocator);

        int64_t index;
        int64_t timestamp;
        std::vector<Transaction> transactions;
        int proof;
        std::string previous_hash;
    };

    class ChainManager {
    public:
        ~ChainManager(){}

        void init();
        int register_node(std::string node);
        void create_block(int proof, std::string& previous_hash);
        void add_transaction(const Transaction& transaction) { _current_transactions.push_back(transaction); }
        inline std::string previous_hash() {
            std::string block_str = _chain.back().str();
            return bbc::hash(block_str); 
        };
        int proof_of_work();
        rapidjson::Document chain_json();


    private:
        std::vector<Transaction> _current_transactions;
        std::vector<Block> _chain;
        std::set<std::string> _nodes;
        std::string uuid;
    };


}

#endif    // BANBO_BLOCK_CHAIN_MANAGER_H