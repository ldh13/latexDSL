#pragma once

#include <stdexcept>
#include <string>


// ### CLASS DEFINITIONS ###

// ## ParseError CLASS ##
class ParseError : public std::runtime_error {
    public:
        explicit ParseError(const std::string &message)
            : std::runtime_error(message) {}
};