#ifndef LIGHTNET_STRARG_H
#define LIGHTNET_STRARG_H
#include "lightnet_copyable.h"
#include <cstring>
#include <cstdlib>

namespace lightnet
{
class StringArg : copyable
{
public:
    StringArg() : __arg(nullptr){};

    explicit StringArg(const char *arg);

    ~StringArg();

    StringArg(const StringArg &that);

    StringArg &operator=(const StringArg &that);

    StringArg &operator=(const char *arg);

    StringArg(StringArg &&that);

    StringArg &operator=(StringArg &&that);

    inline bool empty() const;

    inline const char *c_str() const;

    int toi();

private:
    char *__arg;
};
} // namespace lightnet

#endif /*LIGHTNET_STRARG_H&*/