#ifndef _LR_MODEL_H_
#define _LR_MODEL_H_

#include "store.h"
#include "model.h"

class LRContext : public Context {
 public:
  virtual ~LRContext() = default;
  virtual bool BatchGet(const std::shared_ptr<Config> conf, const std::vector<uint64_t>& features) {
    store_ = StoreFactory::Create(conf);
    return store_->GetWide(conf, features, &wide_w);
  }

 public:
  friend class LRModel;

 private:
  std::unordered_map<uint64_t, float> wide_w;
  std::vector<float> output;
};

class LRModel : public Model {
 public:
  virtual ~LRModel() = default;
  virtual std::shared_ptr<Context> NewContext() {
    return std::shared_ptr<Context>(new LRContext());
  }
  virtual void Predict(const CSRMatrix& X, const std::shared_ptr<Context> context, std::vector<float>* result) {
    const auto ctx = std::dynamic_pointer_cast<LRContext>(context);
    //TODO: forward
    result->swap(ctx->output);
  }
};

#endif
