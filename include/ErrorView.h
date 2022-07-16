
#include <memory>
#include <string>

namespace YamlViewer
{

class ErrorView
{
public:
    ErrorView();
    ~ErrorView();
    void openErrorPopup();
    void show(bool yamlValidationSucceeded, const std::string& errorMessage = std::string());
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};
}