#ifndef TESTS_H
#define TESTS_H

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
  void test_c(string s, double r) { test_c_x(s, "0", r); }
  //  incorrect input without x
  void test_i(string s) { test_i_x(s, "0"); }
  // correct graphic
  template <class T>
  void test_g_f(string s, string xmin, string xmax, string ymin, string ymax,
                string grids, const T &func) {
    contr.setHW(100, 100);
    contr.setExpression(s);
    contr.setPointCenter(false);
    contr.graph(xmax, xmin, ymax, ymin);
    contr.setGridStep(grids);
    for (auto p : contr.getPoints()) {
      ASSERT_DOUBLE_EQ(p.yval, func(p.xval));
    }
  }
  //  correct graph with x y min max grids auto
  template <class T>
  void test_g_c(string s, const T &func) {
    test_g_f(s, "auto", "auto", "auto", "auto", "auto", func);
  }
  // incorrect graphic input
  void test_g_i(string s, string xmin, string xmax, string ymin, string ymax,
                string grids) {
    contr.setHW(100, 100);
    try {
      contr.setExpression(s);
      contr.graph(xmax, xmin, ymax, ymin);
      contr.setGridStep(grids);
      ASSERT_EQ(true, false);
    } catch (...) {
      ASSERT_EQ(true, true);
    }
  }
};

#endif
