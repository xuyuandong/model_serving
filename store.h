#ifndef _STORE_H_
#define _STORE_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include "config.h"

class Store {
 public:
  virtual ~Store() = default;
  virtual bool GetWide(const std::shared_ptr<Config> conf,
	  const std::vector<uint64_t>& features,
	  std::unordered_map<uint64_t, float>* wide_w) = 0;
 protected:
  uint32_t version_ = 0;
};

class KVStore : public Store {
 public:
  virtual ~KVStore() = default;
  virtual bool GetWide(const std::shared_ptr<Config> conf,
	  const std::vector<uint64_t>& features,
	  std::unordered_map<uint64_t, float>* wide_w) {
    // TODO: fetch w from kv
    return true;
  }
};

class StoreFactory {
 public:
  static std::shared_ptr<Store> Create(const std::shared_ptr<Config> conf) {
    return std::shared_ptr<Store>(new KVStore());
  }
};

#endif
