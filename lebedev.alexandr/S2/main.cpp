#include <iostream>
#include <fstream>
#include "convertExpressions.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc > 2)
    {
      std::cerr << "Too much arguments!\n";
      return 1;
    }
    std::ifstream in;
    if (argc == 2)
    {
      in.open(argv[1]);
      if (!in)
      {
        throw std::logic_error("Cannot open file!\n");
      }
    }
    std::stack< std::string > res;
    if (in.is_open())
    {
      res = lebedev::inputExpressions(in);
    }
    else
    {
      res = lebedev::inputExpressions(std::cin);
    }
    std::cout << res.top();
    res.pop();
    while (!res.empty())
    {
      std::cout << ' ' << res.top();
      res.pop();
    }
    std::cout << '\n';
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
