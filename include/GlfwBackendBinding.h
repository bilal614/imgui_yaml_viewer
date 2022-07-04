#pragma once
#include <memory>


namespace SimpleImageViewer
{
class GlfwBackendBinding
{
    public:
        GlfwBackendBinding();
        ~GlfwBackendBinding();

    private:
        struct Impl;
        std::unique_ptr<Impl> p;
};

}