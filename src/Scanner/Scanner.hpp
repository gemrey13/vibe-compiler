#pragma once

#include "Types/Token.hpp"

#include <iostream>
#include <vector>

using vibeCompiler::Token;
using vibeCompiler::TokenType;

namespace vibeCompiler {
    class Scanner {
      public:
        Scanner(const std::string& p_source);
        std::vector<Token> scanTokens();
        void scanToken();
        bool isAtEnd() {};

        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, Literal literal);

      private:
        const std::string& source;
        std::vector<Token> tokens;

        int start = 0;
        int current = 0;
        int line = 1;
    };
} // namespace vibeCompiler