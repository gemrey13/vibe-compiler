#pragma once

#include "Types/Token.hpp"

#include <iostream>
#include <vector>
#include <map>

using vibeCompiler::Token;
using vibeCompiler::TokenType;

namespace vibeCompiler {

    class ErrorReporter;

    class Scanner {
      public:
        Scanner(const std::string& p_source, ErrorReporter& errorReporter);
        std::vector<Token> scanTokens();
        void scanToken();

        void addToken(TokenType type);
        void addToken(TokenType type, Literal literal);

        bool match(char expected);
        bool isDigit(char c);
        bool isAtEnd();
        bool isAlpha(char c);
        bool isAlphaNumeric(char c);

        char peek();
        char peekNext();
        char advance();

        void string();
        void number();
        void identifier();

      private:
        const std::string& source;
        std::vector<Token> tokens;

        static const std::map<std::string, TokenType> lookUpTable;

        ErrorReporter& errorReporter;
        size_t start = 0;
        size_t current = 0;
        int line = 1;
    };
} // namespace vibeCompiler