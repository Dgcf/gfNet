#ifndef GFNET_EXCEPTION_H_
#define GFNET_EXCEPTION_H_

#include <exception>
#include <string>
using namespace std;

namespace gNet
{

class Exception: public std::exception
{
public:
    Exception(const string& _s);
    Exception(const Exception& _t);

private:
    string msg_;
};

} // namespace gNet



#endif