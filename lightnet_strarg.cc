#include "lightnet_strarg.h"

using lightnet::StringArg;

StringArg::StringArg(const char *arg)
{
    __arg = new char[std::strlen(arg) + 1];
    std::strcpy(__arg, arg);
}

StringArg::~StringArg()
{
    if (__arg == nullptr)
    {
        return;
    }
    delete[] __arg;
}

StringArg::StringArg(const StringArg &that)
{
    __arg = new char[std::strlen(that.__arg) + 1];
    std::strcpy(__arg, that.__arg);
}

StringArg &StringArg::operator=(const StringArg &that)
{
    if (this != &that)
    {
        delete[] __arg;
        __arg = new char[std::strlen(that.__arg) + 1];
        std::strcpy(__arg, that.__arg);
    }

    return *this;
}

StringArg &StringArg::operator=(const char *arg)
{
    if (__arg == nullptr)
    {
        __arg = new char[std::strlen(arg) + 1];
        std::strcpy(__arg, arg);
        return *this;
    }

    if (strcmp(arg, __arg) == 0)
    {
        return *this;
    }

    delete[] __arg;
    __arg = new char[std::strlen(arg) + 1];
    std::strcpy(__arg, arg);
    return *this;
}

StringArg::StringArg(StringArg &&that)
{
    __arg = that.__arg;
}

StringArg &StringArg::operator=(StringArg &&that)
{
    if (&that != this)
    {
        __arg = that.__arg;
    }

    return *this;
}

int StringArg::toi()
{
    return std::atoi(__arg);
}

const char *StringArg::c_str() const
{
    return __arg;
}

bool StringArg::empty() const
{
    return __arg[0] == '\0' ? true : false;
}