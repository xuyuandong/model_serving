#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

enum StoreType {
  MEMORY = 0,
  KV = 1,
};

enum ModelType {
  UNKNOWN = -1,
  LR = 0,
  FM = 1,
  WND = 2,
  MTL = 3,
};

class Config {
 public:
  const std::string& GetName() { return name_; }
  StoreType GetStoreType() { return store_type_; }
  ModelType GetModelType() { return model_type_; }
  
  bool Parse(const std::string& text) { return true; }

 private:
  std::string name_;
  StoreType store_type_;
  ModelType model_type_;
};

#endif
