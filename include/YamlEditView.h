
#include "IYamlEditView.h"
#include <memory>

namespace YamlViewer
{

class YamlEditView : public IYamlEditView
{
public:
    YamlEditView(unsigned short width, unsigned short height);
    ~YamlEditView();
    void show();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}