#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <variant>

namespace vibeCompiler {

    using Literal = std::variant<std::monostate, std::string, double, bool>;

    enum class TokenType {
        // Single-character tokens.
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COLON,
        COMMA,
        DOT,
        QUESTION,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character tokens.
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,
        MINUS,
        MINUS_MINUS,
        PLUS,
        PLUS_PLUS,

        // Literals.
        IDENTIFIER,
        STRING,
        NUMBER,

        // Keywords.
        AMEN,       // AND
        LOWKEY,     // OR
        VIBECHECK,  // IF
        BRUH,       // ELSE
        CAP,        // FALSE
        NO_CAP,     // TRUE
        FINNA,      // FUN
        LOOPIN,     // FOR
        MID,        // NULL
        FLEX,       // PRINT
        ITS_GIVING, // RETURN
        BLUEPRINT,  // CLASS
        GOAT,       // SUPER
        ME,         // THIS
        LET,        // VAR
        COOKIN,     // WHILE

        VIBE_EOF // End of file
    };

    class Token {
      public:
        Token(TokenType p_type, std::string p_lexeme, Literal p_literal, int p_line);
           

        std::string toString() const;

      private:
        const TokenType type;
        const std::string lexeme;
        const Literal literal;
        const int line;
    };
} // namespace vibeCompiler