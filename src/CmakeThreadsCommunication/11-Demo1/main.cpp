#include "./base.hpp"

int main(int argc, char* argv[]) {
  Base* ptr_base = new Base();
  ptr_base->Run();
  delete ptr_base;
}
