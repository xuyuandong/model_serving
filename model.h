#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include "store.h"
#include "config.h"

struct CSRMatrix {
  int row = 0;
  std::vector<int> row_offsets = {0};
  std::vector<uint64_t> cols;
  std::vector<float> values;
};

class Context {
 public:
  virtual ~Context() = default;
  virtual bool BatchGet(const std::shared_ptr<Config> conf, const std::vector<uint64_t>& features) = 0;
 protected:
  std::shared_ptr<Store> store_;
};

class Model {
 public:
  virtual ~Model() = default;
  std::shared_ptr<Config> GetConfig() { return config_; }
  virtual std::shared_ptr<Context> NewContext() = 0;
  virtual void Predict(const CSRMatrix& X, const std::shared_ptr<Context> context, std::vector<float>* result) = 0;
  virtual bool Update(const std::shared_ptr<Config> conf) { 
      // if you need params cache, override
      return true; 
  }
 protected:
  std::shared_ptr<Config> config_;
};


#endif
