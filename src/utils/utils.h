#include <vector>
#include <optional>

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
}
