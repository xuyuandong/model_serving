#include "manager.h"

std::shared_ptr<ModelMap> Manager::model_map_;
std::mutex Manager::mutex_;
