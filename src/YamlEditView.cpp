#include "YamlEditView.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
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

    void updateYamlText();
    ImGuiWindowFlags windowFlags;
    ImGuiInputTextFlags inputTextFlags;
    ImGuiInputTextCallback editViewCallback;
    std::unique_ptr<ImGuiInputTextCallbackData> callBackContextData;
    std::string yamlText;
};

YamlEditView::Impl::Impl() :
    windowFlags{0},
    inputTextFlags{ImGuiInputTextFlags_AllowTabInput },
    editViewCallback{},
    callBackContextData{std::make_unique<ImGuiInputTextCallbackData>()},
    yamlText{}
{
    editViewCallback = [](ImGuiInputTextCallbackData* data) ->int
    {
        //TODO put implementation here
        return 0;
    };

    if (!ImGui::Begin("Dear ImGui Demo", NULL, windowFlags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
    }
    else
    {
        //ImGui::InputTextMultiline("##source", yamlText.data(), yamlText.size(), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), inputTextFlags, editViewCallback, callBackContextData.get());
        ImGui::InputTextMultiline("##source", &yamlText, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), inputTextFlags, editViewCallback, callBackContextData.get());
        ImGui::End();
    }
}

YamlEditView::YamlEditView() : 
    p {std::make_unique<Impl>()}
{

}

YamlEditView::~YamlEditView() = default;



}