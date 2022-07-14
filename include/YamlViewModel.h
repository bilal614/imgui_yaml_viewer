#include <memory>

namespace YamlViewer
{
class YamlViewModel
{
public:
    YamlViewModel();
    ~YamlViewModel();
    void validateYamlText();

private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}