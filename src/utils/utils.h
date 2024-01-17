#pragma once
#include <vector>
#include <optional>
#include <string>

namespace uc {

template<typename T>
std::optional<size_t> find(std::vector<T> objects, T object){
  for(size_t i=0; i<objects.size(); i++){
    if(objects[i] == object){
      return {i};
    }
  }
  return {}; 
}

std::vector<std::string>* splitString(const std::string& text, const char separator);

}
