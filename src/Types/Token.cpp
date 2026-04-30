#include "Types/Token.hpp"

#include <iostream>
#include <sstream>

namespace vibeCompiler {
    Token::Token(TokenType p_type, std::string p_lexeme, Literal p_literal, int p_line)
        : type(p_type), lexeme(std::move(p_lexeme)), literal(p_literal), line(p_line) {}

    std::string Token::toString() const {
        // 1. Convert the Literal "Object" to a string
        // std::visit looks inside the variant and picks the right version
        std::string literalString = std::visit(
            [](auto&& arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::monostate>)
                    return "null";
                else if constexpr (std::is_same_v<T, std::string>)
                    return arg;
                else if constexpr (std::is_same_v<T, double>)
                    return std::to_string(arg);
                else if constexpr (std::is_same_v<T, bool>)
                    return arg ? "true" : "false";
                return "";
            },
            literal);

        // 2. Build the final string
        // We use a stringstream to "glue" everything together
        std::stringstream ss;
        ss << static_cast<int>(type) << " " << lexeme << " " << literalString;
        return ss.str();
    }
} // namespace vibeCompiler