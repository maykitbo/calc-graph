#include "../controller/controller.h"

int main() {
  s21::Model model;
  s21::Controller contr = s21::Controller(&model);
  std::string s = "1+2";
  contr.setExpression(s);
  std::cout << contr.count("0+2") << "\n";
}