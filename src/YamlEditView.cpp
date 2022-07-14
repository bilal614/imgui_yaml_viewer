#include "YamlEditView.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <iostream>

namespace YamlViewer
{
void onUserInputRecieved(std::vector<char>& yamlText, char* textBuffer, int bufTextLen)
{
    yamlText.clear();
    yamlText.insert(yamlText.begin(), textBuffer, textBuffer + bufTextLen);
}

struct YamlEditView::Impl
{
    Impl(unsigned short width, unsigned short height);
    ~Impl() = default;

    void traverseYamlNode(const YAML::Node& yamlNode);

    unsigned short viewWidth, viewHeight;
    ImGuiWindowFlags windowFlags;
    ImGuiInputTextFlags inputTextFlags;
    ImGuiInputTextCallback editViewCallback;
    std::unique_ptr<ImGuiInputTextCallbackData> callBackContextData;
    std::string yamlTextBuffer;
};

YamlEditView::Impl::Impl(unsigned short width, unsigned short height) :
    viewWidth{width},
    viewHeight{height},
    windowFlags{ImGuiWindowFlags_NoMove },
    inputTextFlags{ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackEdit },
    editViewCallback{},
    callBackContextData{std::make_unique<ImGuiInputTextCallbackData>()},
    yamlTextBuffer{}
{
    callBackContextData->UserData = this;
    editViewCallback = [](ImGuiInputTextCallbackData* data) ->int
    {
        //TODO put implementation here
        
        return 0;
    };

}

void YamlEditView::Impl::traverseYamlNode(const YAML::Node& yamlNode)
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

YamlEditView::YamlEditView(unsigned short width, unsigned short height) : 
    p {std::make_unique<Impl>(width, height)}
{

}

YamlEditView::~YamlEditView() = default;

void YamlEditView::show()
{
    if (!ImGui::Begin("Yaml Editor", NULL, p->windowFlags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
    }
    else
    {
        ImGui::InputTextMultiline("##source", &p->yamlTextBuffer, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 32), p->inputTextFlags, p->editViewCallback, p->callBackContextData.get());
        auto clicked = ImGui::Button("Validate");
        if(clicked)
        {
            std::cout << "Button clicked" << std::endl;
            std::stringstream ss{p->yamlTextBuffer};
            YAML::Node yamlNode = YAML::Load(ss);
            p->traverseYamlNode(std::move(yamlNode));
        }
        ImGui::End();
    }
}


}