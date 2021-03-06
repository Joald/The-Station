#ifndef THE_STATION_RESOURCE_NOT_FOUND_ERROR_H
#define THE_STATION_RESOURCE_NOT_FOUND_ERROR_H

class ResourceNotFoundError : public std::runtime_error {
public:
    explicit ResourceNotFoundError(const std::string &__arg) : runtime_error(__arg) {}

    const char *what() const noexcept override {
        return std::runtime_error::what();
    }
};


#endif //THE_STATION_RESOURCE_NOT_FOUND_ERROR_H
