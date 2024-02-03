#include <iostream>
#include <unordered_map>
#include <string>

typedef std::pair<std::string, std::string> Name;

namespace std {
 template<> // function-template-specialization
 class hash<Name> {
 public :
   size_t operator()(const Name &name) const {
     return hash<string>()(name.first) ^ hash<string>()(name.second);
   }
 };
};

int main() {
  std::unordered_map<Name, int> ids;
  ids[Name("Mark", "Nelson")] = 40561;
  ids[Name("Andrew", "Binstock")] = 40562;
  for (auto &id: ids) {
    std::cout << id.first.first << " " << id.first.second << " : " << id.second << "\n";
  }
  return 0;
}
