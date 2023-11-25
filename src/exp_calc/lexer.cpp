#include <cctype>
#include <iostream>
#include "lexer.h"
#include "../utils/utils.h"

std::string Token::typeString(const size_t token_type){
  std::string s_types[] = {
    "TOKEN_INT",
    "TOKEN_FLOAT",
    "TOKEN_STRING",
    "TOKEN_OPERATOR",
    "TOKEN_WORD",
    "TOKEN_COMMA",
    "TOKEN_L_BRACKET",
    "TOKEN_R_BRACKET"
  };
  return s_types[token_type]; 
}

std::string Token::string(){
  std::string s = "";
  s += std::string("{type: ");
  s += this->typeString(this->type);
  if(this->value){
    s += std::string(",value: ");
    s += *(this->value);
  }
  s += "}";
  return s;
}

Lexer::Lexer(){
  this->tokens = {};
  this->buffor = "";
  this->idx = 0;
  this->line = "";
  this->error_message = "";
}

Lexer::Lexer(const std::string line): Lexer(){
  this->line = line;
}

std::vector<Token> Lexer::getTokens() const {
  return this->tokens;
}

std::string Lexer::getErrorMessage() const {
  return this->error_message;
}

char Lexer::at() const {
  if(this->idx < size_t(this->line.length())){
    return this->line[this->idx];
  }
  return 0;
}

bool Lexer::isEOL() const {
  if(this->idx < this->line.length())
    return false;
  return true;
}

void Lexer::eat(){
  if(this->at()){
    this->buffor += this->at();
    idx+=1;
  }
}

void Lexer::clearBuffor(){
  this->buffor = "";
}

void Lexer::createToken(const size_t token_type){
  Token t = Token();
  t.type = token_type;
  if(this->buffor != "")
    t.value = this->buffor;
  this->tokens.push_back(t);
  this->clearBuffor();
}

void Lexer::eatWord(){
  this->eat();
  while(!this->isEOL() && isalnum(this->at()))
    this->eat();
  this->createToken(TOKEN_WORD);
}

void Lexer::eatNumber(){
  this->eat();
  while(!this->isEOL() && isdigit(this->at())){
    this->eat();
  }
  if(!this->isEOL() && this->at() == '.')
    this->eat();
  else {
    this->createToken(TOKEN_INT);
    return;
  }
  while(!this->isEOL() && isdigit(this->at())){
    this->eat();
  }
  this->createToken(TOKEN_FLOAT);
}

void Lexer::eatString(){
  this->eat();
  while(!this->isEOL() && isprint(this->at()) && this->at() != '"'){
    this->eat();
  }
  if(this->isEOL() || this->at() != '"'){
    this->error_message = "Not ending string!";
    return;
  }
  this->eat();
  this->createToken(TOKEN_STRING);
}

void Lexer::eatOperator(){
  this->eat();
  while(!this->isEOL() && std::string("+-*/").find(this->at()) != -1)
    this->eat();
  std::vector<std::string> operators = {"+", "-", "*", "/"};
  if(uc::find(operators, this->buffor))
    this->createToken(TOKEN_OPERATOR);
  else{
    this->error_message = "There is no operator ";
    this->error_message += this->buffor;
  }
}

void Lexer::eatBracket(const bool left){
  this->idx += 1;
  if(left){
    this->createToken(TOKEN_L_BRACKET);
    return;
  }
  this->createToken(TOKEN_R_BRACKET);
}

void Lexer::tokenize(){
  while(!this->isEOL() && this->error_message == ""){
    if(isalpha(this->at()))
      this->eatWord();
    else if(isdigit(this->at()))
      this->eatNumber();
    else if(this->at() == '"')
      this->eatString();
    else if(std::string("+-*/").find(this->at()) != -1)
      this->eatOperator();
    else if(this->at() == '(')
      this->eatBracket(true);
    else if(this->at() == ')')
      this->eatBracket(false);
    else if(this->at() == ','){
      this->idx += 1;
      this->createToken(TOKEN_COMMA);
    }
    else if(this->at() == ' ')
      idx += 1;
  }
}

bool Lexer::good(){
  if(this->error_message != "")
    return false;
  return true;
}


