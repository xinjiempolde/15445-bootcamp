#include <iostream>
#include <functional>

// C-style normal function
int Add(int a, int b) {
  return a + b;
}

// Template function
template <typename T>
T Minus(T a, T b) {
  return a - b;
}

// Lambda expression
auto lambda_multiple = [](int a, int b){ return a * b; };

// Function object
struct Div {
  auto operator() (double a, double b) -> double {
    return a / b;
  }
};

// template function object
template <class T>
struct Increment {
  T operator() (T a) {
    return ++a;
  }
};

// static member function without templates
class Math {
 public:
  static int Add(int a, int b) {
    return a + b;
  }
};

// static member function with templates
template <class T>
class MathWithTemplate {
 public:
  static T Add(T a, T b) {
    return a + b;
  }
};

// Normal member function without templates
class NormalMath {
 public:
  int Add(int a, int b) {
    return a + b + c_;
  }
 private:
  int c_{2};
};

// Normal member function with templates
class NormaMathWithTemplates {
 public:
  template <class T>
  T Add(T a, T b) {
    return a + b;
  }
private:
};

int main() {
  // Using c-style function pointer
  typedef int (*Func)(int, int);
  Func f1 = Add;
  std::cout << f1(1, 2) << "\n";

  // std::function with normal function
  std::function<int(int, int)> f2 = Add;
  std::cout << f2(1, 2) << "\n";

  // std::function with template function
  std::function<double(double, double)> f3 = Minus<double>;
  std::cout << f3(5.8, 1.2) << "\n";

  // std::function with lambda expression
  std::function<int(int, int)> f4 = lambda_multiple;
  std::cout << f4(2, 4) << "\n";

  // std::function with function object
  std::function<double(double, double)> f5 = Div();
  std::cout << f5(3.6, 1.2) << "\n";

  // std::function with template function object
  std::function<int(int)> f6 = Increment<int>();
  std::cout << f6(6) << "\n";

  // std::function with static member function without template
  std::function<int(int, int)> f7 = Math::Add;
  std::cout << f7(5, 4) << "\n";

  // std::function with static member function with template
  std::function<int(int, int)> f8 = MathWithTemplate<int>::Add;
  std::cout << f8(5, 4) << "\n";

  // std::function with normal member function without templates
  NormalMath normal_math;
  std::function<int(int, int)> f9 = std::bind(&NormalMath::Add, &normal_math, std::placeholders::_1, std::placeholders::_2);
  std::cout << f9(1, 2) << "\n";

  // std::function with normal member function with templates
  NormaMathWithTemplates normal_math_with_template;
  std::function<int(int, int)> f10 = std::bind(&NormaMathWithTemplates::Add<int>, &normal_math_with_template, std::placeholders::_1, std::placeholders::_2);
  return 0;
}