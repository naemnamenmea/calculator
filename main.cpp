#include "calculator.hpp"
#include "my_testing_tools.hpp"
#include <string>

using namespace Calculator;
using namespace std;

TEST(Calc, TestArabicNumerals)
{
  ASSERT_THROW(Calculator::Calculate("2 + V"));
  ASSERT_THROW(Calculator::Calculate("V + 2"));
  ASSERT_THROW(Calculator::Calculate("1 0/ 5"));

  ASSERT_THROW(Calculator::Calculate("1"));
  ASSERT_THROW(Calculator::Calculate("1 + 2 + 3"));
  ASSERT_THROW(Calculator::Calculate("1 ^ 1"));
  ASSERT_THROW(Calculator::Calculate("1.4 - 1"));
  ASSERT_THROW(Calculator::Calculate("1\n+\n1"));
  ASSERT_EQUAL(Calculator::Calculate("4+3"), "7");
  ASSERT_EQUAL(Calculator::Calculate("  1  +  4  "), "5");
  ASSERT_EQUAL(Calculator::Calculate("3 /2"), "1");
  ASSERT_EQUAL(Calculator::Calculate("1-1"), "0");
  ASSERT_EQUAL(Calculator::Calculate("2-3"), "-1");
  ASSERT_THROW(Calculator::Calculate("  1  /  0  "));
}

TEST(Calc, TestRomanNumerals)
{
  ASSERT_EQUAL(Calculator::Calculate("MMCDXIX / XXXVII"), "LXV"); // 2419 / 37 = 65
  ASSERT_THROW(Calculator::Calculate("A / V"));
  ASSERT_THROW(Calculator::Calculate("V / B"));

  ASSERT_EQUAL(Calculator::Calculate("VI / III"), "II");
  ASSERT_THROW(Calculator::Calculate("  I  -  I  "));
  ASSERT_THROW(Calculator::Calculate("I-V"));
}

int main()
{
  RUN_ALL_TESTS();

  string input;
  while (getline(cin, input) && !input.empty())
  {
    try
    {
      cout << Calculator::Calculate(input) << endl;
    }
    catch (exception& e)
    {
      cerr << e.what() << endl;
    }
    catch (...)
    {
      cerr << "Bad input" << endl;
    }
  }

  return 0;
}