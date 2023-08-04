#pragma once

#include <string_view>
#include <memory>
#include <stdexcept>

namespace Calculator
{
  std::string Calculate(std::string_view expression);
}