#include "scanner.h"
#include <string.h>

Scanner scanner;

static bool isAtEnd() { return *scanner.current == '\0'; }

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

static char peek() { return *scanner.current; }

static bool match(const char target) {
  if (isAtEnd()) {
    return false;
  }
  if (*scanner.current != target) {
    return false;
  }
  scanner.current++;
  return true;
}

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (uint32_t)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

static Token errorToken(const char* message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (uint32_t)strlen(message);
  token.line = scanner.line;
  return token;
}

static void skipWhitespace() {
  for (;;) {
    char next = peek();
    switch (next) {
      case ' ':
      case '\t':
      case '\r':
        advance();
        break;
      case '\n':
        scanner.line += 1;
        advance();
      default:
        return;
    }
  }
}

void initScanner(const char* source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}

Token scanToken() {
  skipWhitespace();
  scanner.start = scanner.current;

  if (isAtEnd()) {
    return makeToken(TOKEN_EOF);
  }

  switch (*scanner.current) {
    case '(':
      return makeToken(TOKEN_LEFT_PAREN);
    case ')':
      return makeToken(TOKEN_RIGHT_PAREN);
    case '{':
      return makeToken(TOKEN_LEFT_BRACE);
    case '}':
      return makeToken(TOKEN_RIGHT_BRACE);
    case ',':
      return makeToken(TOKEN_COMMA);
    case '.':
      return makeToken(TOKEN_DOT);
    case '-':
      return makeToken(TOKEN_MINUS);
    case '+':
      return makeToken(TOKEN_PLUS);
    case ';':
      return makeToken(TOKEN_SEMICOLON);
    case '/':
      return makeToken(TOKEN_SLASH);
    case '*':
      return makeToken(TOKEN_STAR);
    case '!':
      return match('=') ? makeToken(TOKEN_BANG_EQUAL) : makeToken(TOKEN_BANG);
    case '=':
      return match('=') ? makeToken(TOKEN_EQUAL_EQUAL) : makeToken(TOKEN_EQUAL);
    case '>':
      return match('=') ? makeToken(TOKEN_GREATER_EQUAL)
                        : makeToken(TOKEN_GREATER);
    case '<':
      return match('=') ? makeToken(TOKEN_LESS_EQUAL) : makeToken(TOKEN_LESS);
  }

  return errorToken("Unexpected character");
}
