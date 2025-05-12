#ifndef CONVERTEXPRESSIONS_HPP
#define CONVERTEXPRESSIONS_HPP
#include <string>
#include <istream>
#include <stack>
#include <queue>
#include <stdexcept>
#include "operations.hpp"

namespace lebedev
{
  std::queue< std::string > convertInfToPost(const std::string& expr);
  long long calculatePost(std::queue< std::string >& post);
  std::stack< std::string > inputExpressions(std::istream& input);
}
#endif
