#include "Core/Application.hpp"

int main()
{
    srand(time(nullptr));
    return Application::instance()->run();
}