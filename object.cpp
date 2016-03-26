#include "object.h"

Object::Object()
{

}

std::string Object::getName() const{
    return _name;
}

void Object::setName(std::string &name){
    _name = name;
}
