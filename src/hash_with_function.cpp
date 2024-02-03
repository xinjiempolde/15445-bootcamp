#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>

class Person {
public:
  std::string name;
  int age;

  Person(std::string n, int a) {
    name = std::move(n);
    age = a;
  }

  // 重载等比函数==
  bool operator==(const Person &p) const {
    return name == p.name && age == p.age;
  }
};

size_t person_hash(const Person &p) {
  return std::hash<std::string>()(p.name) ^ std::hash<int>()(p.age);
}

int main() {
//  It's OK: std::unordered_map<Person, int, decltype(&person_hash)> ids(100, person_hash );
  std::unordered_map<Person, int, std::function<size_t(const Person &p)>> ids(100, person_hash); //需要把person_hash传入构造函数
  ids[Person("Mark", 17)] = 40561;
  ids[Person("Andrew", 16)] = 40562;
  for (const auto &id: ids) {
    std::cout << id.first.name << " " << id.first.age << " : " << id.second << "\n";
  }
  return 0;
}