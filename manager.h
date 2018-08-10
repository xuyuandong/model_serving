#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <mutex>
#include <chrono>
#include <memory>
#include <thread>
#include <string>
#include <unordered_map>
#include "config.h"
#include "model.h"
#include "lr_model.h"

class ModelFactory {
 public:
  static std::shared_ptr<Model> Create(const std::shared_ptr<Config> conf) {
    auto type = conf->GetModelType();
    if (type == LR) return std::shared_ptr<Model>(new LRModel());
    else return nullptr;
  }
};

typedef std::unordered_map<std::string, std::shared_ptr<Model>> ModelMap;
class Manager {
 public:
  static bool Init() { 
      static pthread_once_t once;
      pthread_once(&once, &Manager::StartDetach);
      std::lock_guard<std::mutex> lock(mutex_);
      return model_map_ != nullptr; 
  }
  static std::shared_ptr<Model> GetModel(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = model_map_->find(name);
    if (it != model_map_->end())
	return it->second;
    return nullptr;
  }

 private:
  static void StartDetach() {
    Build();
    std::thread t(&Manager::AsyncUpdate);
    t.detach();
  }
  static void Build() {
    auto new_map = std::shared_ptr<ModelMap>(new ModelMap());
    // TODO: read file and parse config object
    // TODO: create model according to config, put to new_map
    std::lock_guard<std::mutex> lock(mutex_);
    model_map_ = new_map;
  }
  static void AsyncUpdate() {
    //auto tid = std::this_thread::get_id();
    while (1) {
      std::this_thread::sleep_for(std::chrono::seconds(10));
      Build();
    }
  }

 private:
  static std::shared_ptr<ModelMap> model_map_;
  static std::mutex mutex_;
};


#endif
