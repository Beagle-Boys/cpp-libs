#include <iostream>

using namespace std;

class DSAException : public exception
{
    string msg_;

public:
    virtual const char* what() const throw()
    { return msg_.c_str(); }

    explicit DSAException(const string& msg) throw()
    : msg_(msg)
    {}

    virtual ~DSAException() throw()
    {}
};

enum What {
    INVALID_INDEX,
    EMPTY_LIST
};

template <typename T>
struct NODE
{
    T data;
    bool equals(T nodedata, int (*comparator)(T, T))
    {
        if (((*comparator)(data, nodedata)) == 0) return true;
        else return false;
    };
    bool lessthan(T nodedata, int (*comparator)(T, T))
    {
        if (((*comparator)(data, nodedata)) < 0) return true;
        else return false;
    };
    bool greaterthan(T nodedata, int (*comparator)(T, T))
    {
        if (((*comparator)(data, nodedata)) > 0) return true;
        else return false;
    };
    bool lessthanorequal(T nodedata, int (*comparator)(T, T))
    {
        if (lessthan(nodedata, comparator) || equals(nodedata, comparator)) return true;
        else return false;
    };
    bool greaterthanorequal(T nodedata, int (*comparator)(T, T))
    {
        if (greaterthan(nodedata, comparator) || equals(nodedata, comparator)) return true;
        else return false;
    };
    NODE<T> *next;
    NODE<T> *prev;
};

