#include <functional>
#include <list>
#include <memory>

namespace YamlViewer
{
class ErrorView;

template <typename... Args>
using EventHandlerFuntion = std::function<void(Args ...)>;

template <typename... Args> class Event
{
private:
    std::list<EventHandlerFuntion<Args...>> m_functionHandles;
public:
    Event() = default;
    Event(const Event& ) = delete;
    Event& operator=(const Event&) = delete;

    Event(Event&& ) = default;
    Event& operator=(Event&&) = default;

    void add(const EventHandlerFuntion<Args...>& handlerFunction)
    {
        m_functionHandles.push_back(handlerFunction);
    }

    void operator()(Args... params) const
    {
        for (const auto& handler : m_functionHandles)
        {
            handler(std::forward<Args>(params)...);
        }
    }

};

class YamlViewModel
{
public:
    YamlViewModel(ErrorView& errorView);
    ~YamlViewModel();

    void perpareErrorView();

    void addValidationHandler(const EventHandlerFuntion<>& func);
    void validateYamlText(std::stringstream& ss);
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}