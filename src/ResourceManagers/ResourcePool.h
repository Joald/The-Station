#ifndef THE_STATION_RESOURCE_POOL_H
#define THE_STATION_RESOURCE_POOL_H

#include <memory>
#include <unordered_map>

template <class T>
class ResourcePool {
public:
    typedef std::shared_ptr<T> ptr;
    typedef std::unordered_map<std::string, ptr> storage_t;
protected:
    virtual typename storage_t::iterator loadResource(const std::string& id) = 0;

};


#endif //THE_STATION_RESOURCE_POOL_H
