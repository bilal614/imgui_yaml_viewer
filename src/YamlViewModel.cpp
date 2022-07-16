#include "YamlViewModel.h"

#include <iostream>
#include "yaml-cpp/yaml.h"

#include "ErrorView.h"
#include "YamlEditView.h"

namespace YamlViewer
{

struct YamlViewModel::Impl
{
    Impl(ErrorView& errorView);
    ~Impl() = default;

    void traverseYamlNode(const YAML::Node& yamlNode);

    bool validationResult;
    std::string validationMessage;
    ErrorView& errorView;
    Event<> validationEvent;
};

YamlViewModel::Impl::Impl(ErrorView& errorView) : 
    validationResult{false},
    validationMessage{""},
    validationEvent{},
    errorView{errorView}
{
}

void YamlViewModel::Impl::traverseYamlNode(const YAML::Node& yamlNode)
{
    auto nodeType = yamlNode.Type();
    if(nodeType == YAML::NodeType::Undefined)
    {
        std::cout << "NodeType::Undefined" << std::endl;
    }
    if(nodeType ==  YAML::NodeType::Null)
    {
        std::cout << "NodeType::Null" << std::endl;
    }
    if(nodeType == YAML::NodeType::Scalar)
    {
        std::cout << yamlNode.as<std::string>() << std::endl;
    }
    if(nodeType == YAML::NodeType::Sequence)
    {
        for (YAML::const_iterator it=yamlNode.begin();it!=yamlNode.end();++it) 
        {
            traverseYamlNode(*it);
        }
    }
    if(nodeType == YAML::NodeType::Map)
    {
        for(YAML::const_iterator it=yamlNode.begin();it != yamlNode.end();++it) 
        {
            std::string key = it->first.as<std::string>();
            std::cout << key << std::endl;
            if(it->second.IsDefined())
            {
                traverseYamlNode(it->second);
            }
        }
    }
}

YamlViewModel::YamlViewModel(ErrorView& errorView) :
    p{std::make_unique<Impl>(errorView)}
{
    addValidationHandler([this](){p->errorView.openErrorPopup();});
}

YamlViewModel::~YamlViewModel() = default;

void YamlViewModel::addValidationHandler(const EventHandlerFuntion<>& func)
{
    p->validationEvent.add(func);
}

void YamlViewModel::validateYamlText(std::stringstream& ss)
{
    p->validationMessage = "Validation successful";
    p->validationResult = true;
    try
    {
        YAML::Node yamlNode = YAML::Load(ss);
        if(yamlNode == YAML::Node())
        {
            throw std::invalid_argument("Could not parse provided yaml text");
        }
        p->traverseYamlNode(std::move(yamlNode));
    }
    catch(const std::exception& e)
    {
        p->validationResult = false;
        p->validationMessage = e.what();
    }

    p->validationEvent();
}

void YamlViewModel::perpareErrorView()
{
    p->errorView.show(p->validationResult, p->validationMessage);
}

}