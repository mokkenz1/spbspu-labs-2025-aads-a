#include "convertExpressions.hpp"
#include <cctype>

bool isOperator(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int getPriority(char op)
{
  if (op == '+' || op == '-')
  {
    return 1;
  }
  else if (op == '*' || op == '/' || op == '%')
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

std::queue< std::string > lebedev::convertInfToPost(const std::string& expr)
{
  std::stack< char > ops;
  std::queue< std::string > output;
  std::string temp;

  for (size_t i = 0; i < expr.size(); i++)
  {
    char c = expr[i];
    if (isspace(c))
    {
      continue;
    }

    if (isdigit(c))
    {
      temp += c;
      while (i + 1 < expr.size() && isdigit(expr[i+1]))
      {
        temp += expr[++i];
      }
      output.push(temp);
      temp.clear();
      continue;
    }

    if (c == '(')
    {
      ops.push(c);
      continue;
    }

    if (c == ')')
    {
      while (!ops.empty() && ops.top() != '(')
      {
        output.push(std::string(1, ops.top()));
        ops.pop();
      }
      if (ops.empty())
      {
        throw std::runtime_error("Mismatched parentheses!\n");
      }
      ops.pop();
      continue;
    }

    if (isOperator(c))
    {
      while (!ops.empty() && ops.top() != '(' && getPriority(ops.top()) >= getPriority(c))
      {
        output.push(std::string(1, ops.top()));
        ops.pop();
      }
      ops.push(c);
      continue;
    }
    throw std::runtime_error("Invalid symbol!\n");
  }

  if (!temp.empty())
  {
    throw std::runtime_error("Invalid number!\n");
  }

  while (!ops.empty())
  {
    if (ops.top() == '(')
    {
      throw std::runtime_error("Mismatched parentheses!\n");
    }
    output.push(std::string(1, ops.top()));
    ops.pop();
  }
  return output;
}

long long lebedev::calculatePost(std::queue< std::string >& post)
{
  std::stack< long long > ops;
  while (!post.empty())
  {
    std::string token = post.front();
    post.pop();

    if (isdigit(token[0]))
    {
      ops.push(std::stoll(token));
    }
    else if (isOperator(token[0]))
    {
      if (ops.size() < 2)
      {
        throw std::runtime_error("Invalid expression!\n");
      }
      long long b = ops.top();
      ops.pop();
      long long a = ops.top();
      ops.pop();
      ops.push(lebedev::calculate(a, b, token[0]));
    }
    else
    {
      throw std::runtime_error("Invalid token!\n");
    }
  }
  if (ops.size() != 1)
  {
    throw std::runtime_error("Invalid expression!\n");
  }
  return ops.top();
}

std::stack< std::string > lebedev::inputExpressions(std::istream& input)
{
  std::stack< std::string > res;
  std::string line;

  while (input)
  {
    std::getline(input, line);
    if (line.empty())
    {
      continue;
    }
    auto post = convertInfToPost(line);
    res.push(std::to_string(calculatePost(post)));
  }
  return res;
}
