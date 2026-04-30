#include "Scanner/Scanner.hpp"
#include "ErrorReporter/ErrorReporter.hpp"

#include <iostream>

namespace vibeCompiler {
    Scanner::Scanner(const std::string& p_source, ErrorReporter& errorReporter)
        : source(p_source), errorReporter(errorReporter) {};

    std::vector<Token> Scanner::scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        };
        Token eof(TokenType::VIBE_EOF, "", std::monostate{}, line);
        tokens.push_back(eof);
        return tokens;
    }

    void Scanner::scanToken() {
        char c = advance();
        switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        default:
            errorReporter.setError(line, "Unexpected Character.");
            break;
        }
    }

    bool Scanner::isAtEnd() {
        return current >= source.length();
    }

    char Scanner::advance() {
        return source[current++];
    }

    void Scanner::addToken(TokenType type) {
        addToken(type, std::monostate{});
    }

    void Scanner::addToken(TokenType type, Literal literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
    }
} // namespace vibeCompiler