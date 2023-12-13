#pragma once
#include <vector>
#include <string>
#include <optional>

enum{
  TOKEN_INT,
  TOKEN_FLOAT,
  TOKEN_STRING,
  TOKEN_OPERATOR,
  TOKEN_WORD,
  TOKEN_COMMA,
  TOKEN_L_BRACKET,
  TOKEN_R_BRACKET
};

struct Token{
  size_t type;
  size_t col;
  std::optional<std::string> value;

  static std::string typeString(const size_t token_type);
  std::string toString();
};

class Lexer{
  std::vector<Token> tokens;
  std::string buffor;
  size_t idx;
  std::string line;
  std::string error_message;
  size_t token_start;
public:

  Lexer();
  void setLine(const std::string line);
  void tokenize();
  std::vector<Token> getTokens() const;
  std::string getErrorMessage() const;
  bool good();
private:
  char at() const;
  bool isEOL() const;
  void eat(); 
  void clearBuffor();
  void eatWord();
  void eatNumber();
  void eatString();
  void eatOperator();
  void eatBracket(const bool left);
  void createToken(const size_t token_type);

};
