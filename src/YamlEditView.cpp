#include "YamlEditView.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include <string>

#include <iostream>
#include <sstream>
#include <vector>

#include "ErrorView.h"
#include "YamlViewModel.h"
#include <exception>

namespace YamlViewer
{

struct YamlEditView::Impl
{
    Impl(YamlViewModel& viewModel, unsigned short width, unsigned short height);
    ~Impl() = default;

    YamlViewModel& yamlViewModel;
    unsigned short viewWidth, viewHeight;
    ImGuiWindowFlags windowFlags;
    ImGuiInputTextFlags inputTextFlags;
    ImGuiInputTextCallback editViewCallback;
    ImGuiInputTextCallbackData callBackContextData;
    std::string yamlTextBuffer;
};

YamlEditView::Impl::Impl(YamlViewModel& viewModel, unsigned short width, unsigned short height) :
    yamlViewModel{viewModel},
    viewWidth{width},
    viewHeight{height},
    windowFlags{ImGuiWindowFlags_NoMove },
    inputTextFlags{ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackEdit },
    editViewCallback{},
    callBackContextData{},
    yamlTextBuffer{}
{
}


YamlEditView::YamlEditView(YamlViewModel& yamlViewModel, unsigned short width, unsigned short height) : 
    p {std::make_unique<Impl>(yamlViewModel, width, height)}
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
        ImGui::InputTextMultiline("##source", &p->yamlTextBuffer, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 32), p->inputTextFlags, p->editViewCallback, &p->callBackContextData);

        auto clicked = ImGui::Button("Validate");
        if(clicked)
        {
            std::cout << "Button clicked" << std::endl;
            std::stringstream ss{p->yamlTextBuffer};

            p->yamlViewModel.validateYamlText(ss);
        }

        p->yamlViewModel.perpareErrorView();
        ImGui::End();
    }
}

}