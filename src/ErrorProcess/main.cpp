#include <iostream>
#include <utility>
#include <optional>
#include <variant>
#include <system_error>

#include <string.h>
#include <errno.h>

#include "./utils.hpp"

enum class login_errc {  // 强类型枚举
  success = 0,
  not_valid_pass,
  not_login,
};

// 强类型枚举，所以构成重载
std::error_code makeErrorCode(login_errc ec) {
  static const struct LoginErrorCategory : std::error_category {
    virtual std::string message(int val) const override {
      switch ((login_errc)val) {
        case login_errc::success:
          return "login success";
          break;
        case login_errc::not_valid_pass:
          return "not_valid_pass";
          break;
        case login_errc::not_login:
          return "not_login";
          break;

        default:
          return "unkonow error";
          break;
      }
    }
    virtual const char *name() const noexcept override { return "login_errc"; }
  } instance;

  return std::error_code((int)ec, instance);
}

// 现代C++
std::variant<int, std::error_code> sqrt(int x) {  // return >= 0
  if (x < 0) {
    return std::make_error_code(std::errc::argument_out_of_domain);  // error1，系统异常
  }
  if (x == 3) {
    return makeErrorCode(login_errc::not_valid_pass);  // error2，自定义异常
  }
  if (x == 4) {
    return makeErrorCode(login_errc::not_login);  // error3，自定义异常
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

int main(int argc, char *argv[]) {
  auto res = sqrt(8);
  if (res.index() == 1) {
    std::cout << "variant type: " << res.index() << std::endl;
    std::cout << "res: " << std::get<1>(res).message() << std::endl;
  } else {
    std::cout << "res: " << std::get<0>(res) << std::endl;
  }

  return 0;
}
