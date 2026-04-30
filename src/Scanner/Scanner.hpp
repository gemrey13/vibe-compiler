#pragma once

#include "Token/Token.hpp"

#include <iostream>
#include <map>
#include <vector>

using vibeCompiler::Token;
using vibeCompiler::TokenType;

namespace vibeCompiler {

    class ErrorReporter;

    class Scanner {
      public:
        Scanner(const std::string& p_source, ErrorReporter& errorReporter);

        /**
         * @brief Performs Lexical Analysis (Tokenization).
         *
         * This process consumes the raw 'source' string and breaks it down into "lexemes"—
         * the smallest meaningful sequences of characters (blobs).
         *
         * Example:
         * 
         *   Code: var language = "vibe";
         * 
         *   Lexemes: [var], [language], [=], ["vibe"], [;]
         *
         * @return std::vector<Token> A collection of identified tokens ending with VIBE_EOF.
         */
        std::vector<Token> scanTokens();

        /**
         * @brief Scans a single lexeme and categorizes it as a Token.
         *
         * This method acts as the "vibe check" for individual characters. It advances
         * through the source and uses a switch-case to identify single-character tokens,
         * operators, literals, and keywords.
         */
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