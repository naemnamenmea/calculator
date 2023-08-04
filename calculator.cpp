#include "calculator.hpp"
#include "romanNumbers.hpp"
#include <string>
#include <unordered_map>
#include <cmath>
#include <charconv>

using namespace std;
using namespace Calculator;

namespace
{
  int Calc(int a, int b, char op)
  {
    switch (op)
    {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '/':
    {
      if (b == 0)
        throw runtime_error("division by zero");
      return a / b;
    }
    case '*':
      return a * b;
    default:
      throw runtime_error("Wrong operation");
    }
  }
}

string Calculator::Calculate(const string_view expression)
{
  auto nonEmptySymbol = expression.find_first_not_of(' ');
  if (nonEmptySymbol == string::npos)
    nonEmptySymbol = expression.size();
  int a;
  auto [ptr1, ec1] = from_chars(expression.data() + nonEmptySymbol, expression.data() + expression.size(), a);
  if (ec1 == errc()) // arabic format
  {
    const auto opPos = expression.find_first_not_of(' ', ptr1 - expression.data());
    auto secondNumStartPos = opPos;

    if (secondNumStartPos != string::npos)
      ++secondNumStartPos;
    while (secondNumStartPos < expression.size() && expression[secondNumStartPos] == ' ')
      ++secondNumStartPos;

    int b;
    auto [ptr2, ec2] = from_chars(expression.data() + secondNumStartPos, expression.data() + expression.size(), b);
    if (ec2 != errc() || expression.substr(ptr2 - expression.data()).find_first_not_of(' ') != string::npos)
      throw runtime_error("Wrong second operand - non arab number");

    int res = Calc(a, b, expression[opPos]);
    return to_string(res);
  }
  else // try read roman format
  {
    auto endFirstNumber = nonEmptySymbol;
    while (endFirstNumber < expression.size() && (expression[endFirstNumber] >= 'A' && expression[endFirstNumber] <= 'Z'))
    {
      ++endFirstNumber;
    }
    string_view firstNumber = expression.substr(nonEmptySymbol, endFirstNumber - nonEmptySymbol);
    const auto opPos = expression.find_first_not_of(' ', endFirstNumber);
    auto secondNumStartPos = opPos;

    if (secondNumStartPos != string::npos)
      ++secondNumStartPos;
    while (secondNumStartPos < expression.size() && expression[secondNumStartPos] == ' ')
      ++secondNumStartPos;

    auto endSecondNumber = secondNumStartPos;
    while (endSecondNumber < expression.size() && (expression[endSecondNumber] >= 'A' && expression[endSecondNumber] <= 'Z'))
    {
      ++endSecondNumber;
    }
    string_view secondNumber = expression.substr(secondNumStartPos, endSecondNumber - secondNumStartPos);

    int res = Calc(Converter::RomanToArabic(firstNumber), Converter::RomanToArabic(secondNumber), expression[opPos]);
    return Converter::ArabicToRoman(res);
  }
}

