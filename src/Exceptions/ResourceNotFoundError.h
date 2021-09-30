#ifndef THE_STATION_RESOURCE_NOT_FOUND_ERROR_H
#define THE_STATION_RESOURCE_NOT_FOUND_ERROR_H

#include <stdexcept>
#include <string_view>

class ResourceNotFoundError : public std::runtime_error {
public:
    explicit ResourceNotFoundError(std::string_view arg) : runtime_error(arg.data()) {}

    [[nodiscard]] const char* what() const noexcept override;
};


#endif //THE_STATION_RESOURCE_NOT_FOUND_ERROR_H
