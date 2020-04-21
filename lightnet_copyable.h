
#ifndef LIGHTNET_COPYABLE
#define LIGHTNET_COPYABLE
class nocopyable
{
protected:
    nocopyable() = default;
    ~nocopyable() = default;

private:
    nocopyable(const nocopyable &) = delete;
    nocopyable &operator=(const nocopyable &) = delete;
};

struct copyable
{
};

#endif /*LIGHTNET_COPYABLE*/
