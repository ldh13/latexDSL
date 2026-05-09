#pragma once

#include <stdexcept>
#include <string>


// ### CLASS DEFINITIONS ###

// ## LexicalError CLASS ##
class LexicalError : public std::runtime_error {
    public:
        explicit LexicalError(const std::string & message)
            : std::runtime_error(message) {}
};