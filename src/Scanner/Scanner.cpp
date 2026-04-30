#include "Scanner/Scanner.hpp"
#include "ErrorReporter/ErrorReporter.hpp"

#include <iostream>
#include <map>

namespace vibeCompiler {
    Scanner::Scanner(const std::string& p_source, ErrorReporter& p_errorReporter)
        : source(p_source), errorReporter(p_errorReporter) {};

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
                while (peek() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
        case '\0':
            break;

        case '\n':
            line++;
            break;

        // Literals
        case '"':
            string();
            break;

            // Reserved Words and Identifiers
        case 'o':
            if (match('r')) {
                addToken(TokenType::LOWKEY);
            }
            break;

        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                std::string msg = "Unexpected Main Character Vibes '";
                msg += c;
                msg += "' is mid.";
                errorReporter.setError(line, msg);
            }
            break;
        }
    }

    void Scanner::addToken(TokenType type) {
        addToken(type, std::monostate{});
    }

    void Scanner::addToken(TokenType type, Literal literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
    }

    bool Scanner::match(char expected) {
        if (isAtEnd())
            return false;
        if (source[current] != expected)
            return false;

        current++;
        return true;
    }

    bool Scanner::isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    bool Scanner::isAtEnd() {
        return current >= source.length();
    }

    bool Scanner::isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
    }

    bool Scanner::isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    char Scanner::peek() {
        if (isAtEnd())
            return '\0';
        return source[current];
    }

    char Scanner::peekNext() {
        if (current + 1 >= source.length())
            return '\0';
        return source[current + 1];
    }

    char Scanner::advance() {
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

    void Scanner::number() {

        // Consume all digit
        while (isDigit(peek()))
            advance();

        // Look for a fractional part
        if (peek() == '.' && isDigit(peekNext())) {
            // Consume the "." and digits after that
            advance();

            while (isDigit(peek()))
                advance();
        }

        // add the token
        double value = std::stod(source.substr(start, current - start));
        addToken(TokenType::NUMBER, value);
    }

    void Scanner::identifier() {
        while (isAlphaNumeric(peek()))
            advance();

        std::string text = source.substr(start, current - start);
        auto it = lookUpTable.find(text);

        TokenType type;
        if (it != lookUpTable.end()) {
            // It's a keyword (like "VIBECHECK" or "AMEN")
            type = it->second;
        } else {
            // It's just a user-defined variable name
            type = TokenType::IDENTIFIER;
        }
        addToken(type);
    }

    const std::map<std::string, TokenType> Scanner::lookUpTable = {
        {"amen", TokenType::AMEN},             // "and"
        {"blueprint", TokenType::BLUEPRINT},   // "class"
        {"bruh", TokenType::BRUH},             // "else"
        {"cap", TokenType::CAP},               // "false"
        {"finna", TokenType::FINNA},           // "fun"
        {"loopin", TokenType::LOOPIN},         // "for"
        {"vibecheck", TokenType::VIBECHECK},   // "if"
        {"mid", TokenType::MID},               // "nil"
        {"lowkey", TokenType::LOWKEY},         // "or"
        {"flex", TokenType::FLEX},             // "print"
        {"its_giving", TokenType::ITS_GIVING}, // "return"
        {"goat", TokenType::GOAT},             // "super"
        {"me", TokenType::ME},                 // "this"
        {"no_cap", TokenType::NO_CAP},         // "true"
        {"let", TokenType::LET},               // "var"
        {"cookin", TokenType::COOKIN}          // "while"
    };

} // namespace vibeCompiler