/********************************************
 * Author: banbo <banbo777@163.com>
 * File: chain_manager.cpp
 * Date: 2018-08-01
 * Version: 1.0.0.0
 * Brief:
 ********************************************/

#include <sys/time.h>
#include <string>
#include <sstream>
#include "rapidjson/document.h"
#include "chain_manager.h"
#include "common_utils.h"
#include "bbc_log.h"

namespace bbc {

void ChainManager::init() {
    // I have not implemented uuid generator, use a magic string here now.
    uuid = "uuid";
    
    // Hash
    std::string s = "1";
    std::string previous_hash = hash(s);
    create_block(100, previous_hash);
}

void ChainManager::create_block(int proof, std::string& previous_hash) {
    // Get timestamp now.
    struct timeval tp;
    gettimeofday(&tp, NULL);
    int64_t tm = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    // Create new block.
    Block block;
    block.index = _chain.size() + 1;
    block.timestamp = tm;
    block.transactions = _current_transactions;
    block.proof = proof;
    block.previous_hash = previous_hash;

    _chain.push_back(block);
    _current_transactions.clear();
}

/*
*   Compute a hash string that start with "0000" as proof of work.
*   Use stringstream to convert integers as hex.
*/
int ChainManager::proof_of_work() {
    
    if (_chain.empty()) {
        return -1;
    }

    int proof = 0;
    static const std::string target_str = "0000"; 
    while (1) {
        std::stringstream guess;
        guess << _chain.back().proof << proof << previous_hash();
        
        std::string guess_str = guess.str();
        std::string guess_hash_hex = hash(guess_str);
        size_t loc = guess_hash_hex.find(target_str);

        if (loc == 0) {
            return proof;
        }
        ++proof;
    }
}

rapidjson::Value Transaction::json(rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value d;
    d.SetObject();

    rapidjson::Value j_sender;
    j_sender.SetString(sender.c_str(), sender.size(), allocator);
    rapidjson::Value j_receiver;
    j_receiver.SetString(receiver.c_str(), receiver.size(), allocator);
    rapidjson::Value j_amount(amount);
    d.AddMember("sender", j_sender, allocator);
    d.AddMember("receiver", j_receiver, allocator);
    d.AddMember("amount", j_amount, allocator);
    return d;
}

rapidjson::Value Block::json(rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value d;
    d.SetObject();

    rapidjson::Value j_index;
    j_index.SetInt64(index);
    rapidjson::Value j_timestamp;
    j_timestamp.SetInt64(timestamp);
    rapidjson::Value j_proof(proof);
    rapidjson::Value j_previous_hash;
    j_previous_hash.SetString(previous_hash.c_str(), previous_hash.size(), allocator);
    d.AddMember("index", j_index, allocator);
    d.AddMember("timestamp", j_timestamp, allocator);
    d.AddMember("proof", j_proof, allocator);
    d.AddMember("previous_hash", j_previous_hash, allocator);
    
    rapidjson::Value v(rapidjson::kArrayType);   // transactions
    for(std::vector<Transaction>::iterator it = transactions.begin(); it != transactions.end(); ++it) {
        v.PushBack(it->json(allocator), allocator);
    }
    d.AddMember("transactions", v, allocator);

    return d;
}

rapidjson::Document ChainManager::chain_json() {
    rapidjson::Document d;
    d.SetArray();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
    for(std::vector<Block>::iterator it = _chain.begin(); it != _chain.end(); ++it) {
        d.PushBack(it->json(allocator), allocator);
    }
    return d;
}
}   // End bbc.