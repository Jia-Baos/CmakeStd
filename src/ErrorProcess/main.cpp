#include <iostream>
#include <variant>
#include <system_error>

enum class LoginErrc {  // 强类型枚举
  kSuccess = 0,
  kNotValidPass,
  kNotLogin,
};

// 强类型枚举，所以构成重载
std::error_code MakeErrorCode(LoginErrc ec) {
  static const struct LoginErrorCategory : std::error_category {
    virtual std::string message(int val) const override {
      switch ((LoginErrc)val) {
        case LoginErrc::kSuccess:
          return "login success";
          break;
        case LoginErrc::kNotValidPass:
          return "not_valid_pass";
          break;
        case LoginErrc::kNotLogin:
          return "not_login";
          break;

        default:
          return "unkonow error";
          break;
      }
    }
    virtual const char *name() const noexcept override { return "login_errc"; }
  } kInstance;

  return std::error_code((int)ec, kInstance);
}

// 现代C++
std::variant<int, std::error_code> MySqrt(int x) {  // return >= 0
  if (x < 0) {
    return std::make_error_code(std::errc::argument_out_of_domain);  // error1，系统异常
  }
  if (x == 3) {
    return MakeErrorCode(LoginErrc::kNotValidPass);  // error2，自定义异常
  }
  if (x == 4) {
    return MakeErrorCode(LoginErrc::kNotLogin);  // error3，自定义异常
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

int main(int argc, char *argv[]) {
  auto res = MySqrt(4);
  if (res.index() == 1) {
    std::cout << "variant type: " << res.index() << std::endl;
    std::cout << "res: " << std::get<1>(res).message() << std::endl;
  } else {
    std::cout << "res: " << std::get<0>(res) << std::endl;
  }

  return 0;
}
