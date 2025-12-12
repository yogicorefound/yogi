//
// Created by Brayhan De Aza on 11/29/25.
//

#ifndef CROMIO_ERROR_H
#define CROMIO_ERROR_H

#include <visitor/nodes/nodes.h>
#include <any>
#include <string>
// #include "AntlrErrorListener.h"

namespace cromio::utils {

    struct NodePosition; // Forward declaration

    class Error {
       public:
        static void throwError(const std::string& errorType, const std::string& message, const std::any& node, const std::string& source);
        static void throwRangeError(const std::string& message, const std::any& node, const std::string& source);
        static void throwScopeError(const std::string& message, const std::string& identifier, const std::any& node, const std::string& source);
        static void throwTypeError(const std::string& identifier, const std::string& dataType, const std::any& node, const std::string& source);
        static void throwTypeMismatchError(const std::string& identifier, const std::string& expectedType, const std::string& actualType, const std::any& node, const std::string& source);

        static std::string getTypeMessage(const std::string& dataType);

       private:
        static void printContext(const NodePosition& pos, const std::string& source, const std::string& hint);
    };

} // namespace cromio::utils

#endif // CROMIO_ERROR_H