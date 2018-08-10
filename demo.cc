#include "manager.h"
#include "model.h"

int main(void) {
  CSRMatrix input;
  std::vector<uint64_t> features;
  std::vector<float> result;

  std::string name = "my_lr_model";
  auto model = Manager::GetModel(name);
  if (model == nullptr)
    return -1;
  auto context = model->NewContext();
  if (!context->BatchGet(model->GetConfig(), features))
    return -1;
  model->Predict(input, context, &result);
  return 0;
}
