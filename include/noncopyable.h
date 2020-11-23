#ifndef  _NONCOPYABLE_H_
#define  _NONCOPYABLE_H

class noncopyable
{
public:
    noncopyable( noncopyable const& ) = delete;
    noncopyable& operator=(noncopyable const& ) = delete;

protected:
    constexpr noncopyable() = default;
    ~noncopyable() = default;
};

#endif