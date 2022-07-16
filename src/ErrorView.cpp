#include <memory>

#include "ErrorView.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>
#include <iostream>

namespace YamlViewer
{

struct ErrorView::Impl
{
    Impl();
    ~Impl() = default;
    std::string errorMessage;
};

ErrorView::Impl::Impl() :
    errorMessage{""}
{
}



ErrorView::ErrorView() : 
    p {std::make_unique<Impl>()}
{

}

ErrorView::~ErrorView() = default;

void ErrorView::openErrorPopup()
{
    ImGui::OpenPopup("Validate Yaml");
}

void ErrorView::show(bool yamlValidationSucceeded, const std::string& errorMessage)
{
    p->errorMessage = errorMessage;
    if (ImGui::BeginPopupModal("Validate Yaml", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImVec4 messageColor (0.75f, 0.0f, 0.0f, 1.0f);
        if(yamlValidationSucceeded)
        {
             messageColor = ImVec4(0.0f, 0.75f, 0.0f, 1.0f);
        }
        ImGui::TextColored(messageColor, p->errorMessage.c_str());

        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}

}