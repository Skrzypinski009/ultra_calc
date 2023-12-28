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
    "TOKEN_R_BRACKET",
    "TOKEN_RELATION"
  };
  return s_types[token_type]; 
}

std::string Token::toString(){
  std::string s = "";
  s += std::string("{type: ");
  s += this->typeString(this->type);
  if(this->value){
    s += std::string(",value: ");
    s += *(this->value);
  }
  s += std::string(", col: ");
  s += std::to_string(this->col);
  s += "}";
  return s;
}

Lexer::Lexer(){
  this->tokens = {};
  this->buffor = "";
  this->idx = 0;
  this->line = "";
  this->error_message = "";
  this->token_start = 0;
}

void Lexer::setLine(const std::string line){
  this->line = line;
  this->tokens.clear();
  this->buffor = "";
  this->idx = 0;
  this->error_message = "";
  this->token_start = 0;
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
  t.col = this->token_start;
  if(this->buffor != "")
    t.value = this->buffor;
  this->tokens.push_back(t);
  this->clearBuffor();
  this->token_start = this->idx;
}

void Lexer::eatWord(){
  this->eat();
  while(!this->isEOL() && isalpha(this->at()))
    this->eat();
  this->createToken(TOKEN_WORD);
}

void Lexer::eatRel(){
  this->eat();
    // eating operator
  if(!this->isEOL() && std::string("+-").find(this->at()) != -1){
    this->eat();
  }
  // eating number
  if(!this->isEOL() && isdigit(this->at())){
    this->eat();
    while(!this->isEOL() && isdigit(this->at())){
      this->eat();
    }
  }
  this->createToken(TOKEN_RELATION);
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
  this->idx+=1;
  while(!this->isEOL() && isprint(this->at()) && this->at() != '"'){
    this->eat();
  }
  if(this->isEOL() || this->at() != '"'){
    this->error_message = "Not ending string!";
    return;
  }
  this->idx+=1;
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
  char c;
  while(!this->isEOL() && this->error_message == ""){
    c = this->at();
    if(isalpha(c)){
      if(c=='T' || c=='R' || c=='C'){
        this->eatRel();
      }
      else
        this->eatWord();
    }
    else if(isdigit(c))
      this->eatNumber();
    else if(c == '"')
      this->eatString();
    else if(std::string("+-*/").find(c) != -1)
      this->eatOperator();
    else if(c == '(')
      this->eatBracket(true);
    else if(c == ')')
      this->eatBracket(false);
    else if(c == ','){
      this->idx += 1;
      this->createToken(TOKEN_COMMA);
    }
    else if(c == ' ')
      this->idx += 1;
      this->token_start = this->idx;
  }
}

bool Lexer::good(){
  if(this->error_message != "")
    return false;
  return true;
}

size_t getRelationFlags(std::string text){
  size_t flags = 0;
  for(char c: text){
    switch(c){
      case 'T':
        if((1 & flags)){
          return 0;
        }
        flags += 1;
        break;
      case 'R':
        if((2 & flags)){
          return 0;
        }
        flags += 2;
        break;
      case 'C':
        if((4 & flags)){
          return 0;
        }
        flags += 4;
        break;
    }
  }
  return flags;
}

