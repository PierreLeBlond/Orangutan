#ifndef OBJECT_H
#define OBJECT_H

#include <string>


class Object
{
public:
                                Object();
    std::string                 getName() const;
    void                        setName(std::string &name);

private:
    std::string                 _name;
};

#endif // OBJECT_H
