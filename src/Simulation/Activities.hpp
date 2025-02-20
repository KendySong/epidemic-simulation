#pragma once
#include <string>

enum class Activities
{
    Sleep = 0,
    Home = 1,
    Work = 2,
    Entertainment = 3,
    Undefined = 4
};

std::string getString(Activities a);