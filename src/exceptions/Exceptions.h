#pragma once
#include <exception>
#include <string>

class Exceptions: public std::exception {
public:
  Exceptions(std::string what);
  ~Exceptions();

  // Getters
  virtual const char* what() const throw();
  virtual const int errNo() const throw(); // 1
  
private:
  std::string _what;
};
