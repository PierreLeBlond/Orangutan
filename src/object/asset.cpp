#include "object/asset.h"

Asset::Asset(const std::string &name) : _name(name)
{}

const std::string& Asset::getName() const
{
    return _name;
}

void Asset::setName(const std::string &name)
{
    _name = name;
}
