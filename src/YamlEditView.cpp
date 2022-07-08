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
    Impl();
    ~Impl() = default;

    ImGuiWindowFlags windowFlags;
    ImGuiInputTextFlags inputTextFlags;
    ImGuiInputTextCallback editViewCallback;
    std::unique_ptr<ImGuiInputTextCallbackData> callBackContextData;
    std::string yamlTextBuffer;
};

YamlEditView::Impl::Impl() :
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
        std::stringstream ss{data->Buf};
        static_cast<YamlEditView::Impl*>(data->UserData)->yamlTextBuffer = ss.str();
        YAML::Parser yamlParser;
        yamlParser.Load(ss);
        yamlParser.PrintTokens(std::cout);
        return 0;
    };

}

YamlEditView::YamlEditView() : 
    p {std::make_unique<Impl>()}
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
        ImGui::End();
    }
}


}