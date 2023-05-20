#include <string>
#include <functional>

struct RenderMode
{
    std::string name;
    std::function<void()> setRenderMode;
};