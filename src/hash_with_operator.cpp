#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

class Person {
public:
  std::string name;
  int age;

  Person(std::string n, int a) {
    name = std::move(n);
    age = a;
  }

  bool operator==(const Person &p) const {
    return name == p.name && age == p.age;
  }
};

struct hash_name {
  size_t operator()(const Person &p) const {
    return std::hash<std::string>()(p.name) ^ std::hash<int>()(p.age);
  }
};

int main() {
  std::unordered_map<Person, int, hash_name> ids; //不需要把哈希函数传入构造器
  ids[Person("Mark", 17)] = 40561;
  ids[Person("Andrew", 16)] = 40562;
  for (auto &id: ids) {
    std::cout << id.first.name << " " << id.first.age << " : " << id.second << "\n";
  }
  return 0;
}
