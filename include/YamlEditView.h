
#include "IYamlEditView.h"
#include <memory>

namespace YamlViewer
{

class YamlEditView : public IYamlEditView
{
public:
    YamlEditView();
    ~YamlEditView();

private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}