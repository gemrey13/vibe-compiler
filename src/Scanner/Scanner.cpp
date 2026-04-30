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
        // Single-character tokens.
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

        // One or two character tokens.
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;

        case '/':
            if (match('/')) {
                while (peek() != '\n' && isAtEnd())
                    advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        // Literals
        case '"':
            string();
            break;
        default:
            if (isDigit(c)) {
                number();
            } else {
                errorReporter.setError(line, "Unexpected Character.");
            }
            break;
        }
    }

    bool Scanner::isAtEnd() {
        return current >= source.length();
    }

    char Scanner::advance() {
        return source[current++];
    }

    bool Scanner::isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    void Scanner::number() {
        while (isDigit(peek()))
            advance();

        if (peek() == '.' && isDigit(peekNext())) {
            advance();

            while (isDigit(peek()))
                advance();
        }

        double value = std::stod(source.substr(start, current - start));
        addToken(TokenType::NUMBER, value);
    }

    char Scanner::peekNext() {
        if (current + 1 >= source.length())
            return '\0';
        return source[current++];
    }

    void Scanner::string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n')
                line++;
            advance();
        }

        if (isAtEnd()) {
            errorReporter.setError(line, "Unterminated string.");
            return;
        }

        advance();
        std::string value = source.substr(start + 1, current - start - 2);
        addToken(TokenType::STRING, value);
    }

    char Scanner::peek() {
        if (isAtEnd())
            return '\0';
        return source[current];
    }

    bool Scanner::match(char expected) {
        if (isAtEnd())
            return false;
        if (source[current] != expected)
            return false;

        current++;
        return true;
    }

    void Scanner::addToken(TokenType type) {
        addToken(type, std::monostate{});
    }

    void Scanner::addToken(TokenType type, Literal literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
    }
} // namespace vibeCompiler