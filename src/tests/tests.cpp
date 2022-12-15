
#include <gtest/gtest.h>

#include "../controller/controller.h"

using namespace std;

class calc : public testing::Test {
 protected:
  s21::Model model;
  s21::Controller contr = s21::Controller(&model);

 public:
  //  correct input with x
  void test_c_x(string s, string x, double r) {
    contr.setExpression(s);
    if (isnan(r))
      ASSERT_EQ(1, isnan(contr.count(x)));
    else
      ASSERT_DOUBLE_EQ(contr.count(x), r);
  }
  //  incorrect input with x
  void test_i_x(string s, string x) {
    contr.setExpression(s);
    ASSERT_ANY_THROW(contr.count(x));
  }
  //  correct input without x
  void test_c(string s, double r) {
    contr.setExpression(s);
    if (isnan(r))
      ASSERT_EQ(1, isnan(contr.count("0")));
    else
      ASSERT_DOUBLE_EQ(contr.count("0"), r);
  }
  //  incorrect input without x
  void test_i(string s) {
    contr.setExpression(s);
    ASSERT_ANY_THROW(contr.count("0"));
  }
};

TEST_F(calc, correct_1) {
  test_c("-1", -1);
  test_c("+0", 0);
  test_c("-0", 0);
  test_c(" p ", M_PI);
  test_c("- p ", -M_PI);
  test_c("+pi", M_PI);
  test_c(" pI ", M_PI);
  test_c(" Pi ", M_PI);
  test_c("-E", -M_E);
  test_c("+e", M_E);
  test_c("+inf", INFINITY);
  test_c("-inf", -INFINITY);
  test_c("inf", INFINITY);
  test_c("1e15", 1e15);
  test_c("+1.44E15", 1.44e15);
  test_c("-1000000000", -1000000000.0);
  test_c("-1.2e300", -1.2e300);
  test_c("44e-299", 44e-299);
}

TEST_F(calc, correct_2) {
  test_c("1+2", 3);
  test_c("-7 / 5", -7.0 / 5.0);
  test_c("1 / inf", 1 / INFINITY);
  test_c("acos5", NAN);
  test_c("sin44", sin(44));
  test_c("3sqrt2", 3.0 * sqrt(2.0));
  test_c("1%4.4", fmod(1, 4.4));
  test_c("cos(sinp)", cos(std::sin(M_PI)));
  test_c("tg(pi/3)", tan(M_PI / 3.0));
  test_c("ln(e-1e2)", log(M_E - 1e2));
  test_c("SIN(3e55)", sin(3e55));
  test_c("E-P^pi", M_E - pow(M_PI, M_PI));
  test_c("-3pe", -3 * M_PI * M_E);
  test_c("-sin5", -sin(5.0));
  test_c("-(1+2)", -3);
}

TEST_F(calc, correct_3) {
  test_c("+3.00-(+2.2)/(-0.77e-22)", 3.0 - 2.2 / (-0.77e-22));
  test_c("3 * (-4 ^ 2)", 48);
  test_c("(1+2)(-3/0.5)", -18);
  test_c("1-2-3-4-5-6", 1 - 2 - 3 - 4 - 5 - 6);
  test_c("1-(-2-(3-4/(-7))(5-6/(7-8)))",
         1 - (-2 - (3 - 4.0 / (-7.0)) * (5 - 6 / (7 - 8))));
  test_c("1-(2-(3-(4/8)(-1-7))-3) ",
         1.0 - (2.0 - (3.0 - (4.0 / 8.0) * (-1.0 - 7.0)) - 3.0));
  test_c("sin(1/(3ln5.5))^(sqrt(234p)-cos(3^(atan5modasin0.5)))",
         pow(sin(1.0 / (3.0 * log(5.5))),
             sqrt(234.0 * M_PI) - cos(pow(3, fmod(atan(5.0), asin(0.5))))));
}

TEST_F(calc, correct_x) {
  test_c_x("3-x", "-7", 10);
  test_c_x("2xp", "-1", -2.0 * M_PI);
  test_c_x("arcsin(x)", "sin(3)", asin(sin(3)));
  test_c_x("asin(1 / LN(x^x))", "-1*2", asin(1 / log(pow(-2, -2))));
  test_c_x("log(ln(x))", "sqrt(e)", log10(log(sqrt(M_E))));
  test_c_x("sin(X^(cos(x)))", "-(3modln(-5.5))",
           sin(pow(-fmod(3.0, log(-5.5)), cos(-fmod(3.0, log(-5.5))))));
  test_c_x("1+2", "qwerty", 3);
  test_c_x("(5 * 2 / p) * atanx", "77.7", (5.0 * 2.0 / M_PI) * atan(77.7));
}

TEST_F(calc, incorrect) {
  test_i("(1+2");
  test_i("13 13");
  test_i("sin(x) - f");
  test_i("(1+2)2");
  test_i("s i n (x)");
  test_i("12+3)");
  test_i("1+(2+(-3)");
  test_i("asin-1");
  test_i("cossinp");
  test_i("1-(2-(3())-4)");
  test_i("3mod-3");
  test_i("sin(X^(cos(x))");
  test_i("1e3.4");
}

TEST_F(calc, incorrect_x) {
  test_i_x("3-x3", "-7");
  test_i_x("sinx", "x");
  test_i_x("sinx", "r");
}

TEST_F(calc, test_graph) {}

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}