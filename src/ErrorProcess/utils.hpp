#pragma once

#include <cmath>
#include <iostream>
#include <utility>
#include <optional>
#include <variant>
#include <system_error>

#include <string.h>
#include <errno.h>

namespace error_code1 {
int MySqrt1(int x) {  // return >= 0
  if (x < 0) {
    return -1;
    // exit(-1); // 不可取
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;
    }
  }
}

std::pair<int, bool> MySqrt2(int x) {  // return >= 0
  if (x < 0) {
    return {-1, false};
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return {i, true};
    }
  }
}

// int: [INT_MIN, INT_MAX]
// optional: [INT_MIN, INT_MAX] | {nullopt}
std::optional<int> MySqrt3(int x) {
  if (x < 0) {
    return std::nullopt;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [INT_MIN, INT_MAX]
    }
  }
}

// C、CUDA常用
int MySqrt4(int x, int *pret) {  // return >= 0
  if (x < 0) {
    return 1;  // error1
  }
  if (x == 4) {
    return 2;  // error2
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      *pret = i;
      return 0;  // [0, INT_MAX]
    }
  }
}

thread_local int errorno_own{};  // 错误码全局变量，posix标准错误处理，返回值不能包括-1
int MySqrt5(int x) {             // return >= 0
  if (x < 0) {
    errorno_own = 1;  // error1
    return -1;
  }
  if (x == 4) {
    errorno_own = 2;  // error2
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

// posix标准错误处理示例
int MySqrt6(int x) {  // return >= 0
  if (x < 0) {
    errno = EDOM;  // error1
    return -1;
  }
  if (x == 4) {
    errno = EINVAL;  // error2
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

// 现代C++
int MySqrt7(int x, int &ec) {  // return >= 0
  if (x < 0) {
    ec = EDOM;  // error1
    return -1;
  }
  if (x == 4) {
    ec = EINVAL;  // error2
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void TestErrorCode() {
  auto res1 = MySqrt1(-1);
  if (res1 == -1) {
    std::cout << "res1: x can't be less 0" << std::endl;
  }

  auto res2 = MySqrt2(-1);
  if (res2.second == false) {
    std::cout << "res2: x can't be less 0" << std::endl;
  }

  auto res3 = MySqrt3(-1);
  if (res3.has_value() == false) {
    std::cout << "res3: x can't be less 0" << std::endl;
  }

  int pret{};
  auto res4 = MySqrt4(-1, &pret);
  if (res4 == 1) {
    std::cout << "res4: x can't be less 0" << std::endl;
  } else if (res4 == 2) {
    std::cout << "res4: x can't be 4" << std::endl;
  }

  auto res5 = MySqrt5(-1);
  if (res5 == -1) {  // 此时检查错误原因，利用errorno_own
    if (errorno_own == 1) {
      std::cout << "res5: x can't be less 0" << std::endl;
    } else if (errorno_own == 2) {
      std::cout << "res5: x can't be 4" << std::endl;
    }
  }

  setlocale(LC_ALL, "zh_CN.UTF-8");  // 设置错误为中文显示
  auto res6 = MySqrt6(4);
  if (res6 == -1) {  // 此时检查错误原因，利用errno
    const char *str = strerror(errno);
    std::cout << "res6: " << str << std::endl;
    perror("res6: ");  // 自动添加错误原因
  }

  int ec{};
  auto res7 = MySqrt7(4, ec);
  if (res7 == -1) {  // 此时检查错误原因，利用ec
    const char *str = strerror(ec);
    std::cout << "res7: " << str << std::endl;
    perror("res7: ");  // 自动添加错误原因
  }
}
}  // namespace error_code1

namespace error_code2 {
enum class LoginErrc {  // 强类型枚举
  kSuccess = 0,
  kNotValidPass,
  kNotLogin,

};

const char *LoginStrError(LoginErrc ec) {
  switch (ec) {
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

// 现代C++
int MySqrt(int x, LoginErrc &ec) {  // return >= 0
  if (x < 0) {
    ec = LoginErrc::kNotValidPass;  // error1
    return -1;
  }
  if (x == 4) {
    ec = LoginErrc::kNotLogin;  // error2
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void TestSqrt() {
  LoginErrc ec = LoginErrc::kSuccess;
  auto res = MySqrt(4, ec);
  if (ec != LoginErrc::kSuccess) {  // 此时检查错误原因，利用ec
    const char *str = LoginStrError(ec);
    std::cout << "res: " << str << std::endl;
  }
}

}  // namespace error_code2

namespace error_code3 {
enum class LoginErrc {  // 强类型枚举
  kSuccess = 0,
  kNotValidPass,
  kNotLogin,

};

struct ErrorCode {
  int val;
  const char *(*category)(int val);

  bool operator==(const ErrorCode &ec) const { return ec.val == this->val; }
};

const char *LoginStrError(LoginErrc val) {
  switch (val) {
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

// 现代C++
int MySqrt(int x, ErrorCode &ec) {  // return >= 0
  if (x < 0) {
    ec = {(int)std::errc::argument_out_of_domain, (const char *(*)(int val))strerror};  // error1，系统异常
    return -1;
  }
  if (x == 3) {
    ec = {(int)LoginErrc::kNotValidPass, (const char *(*)(int val))LoginStrError};  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = {(int)LoginErrc::kNotLogin, (const char *(*)(int val))LoginStrError};  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void TestSqrt() {
  ErrorCode ec = ErrorCode();
  auto res = MySqrt(4, ec);
  if (ec.val != 0) {  // 此时检查错误原因，利用ec
    const char *str = ec.category(ec.val);
    std::cout << "res: " << str << std::endl;
    if (ec == ErrorCode{(int)LoginErrc::kNotLogin, (const char *(*)(int val))LoginStrError}) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code3

namespace error_code4 {
enum class LoginErrc {  // 强类型枚举
  kSuccess = 0,
  kNotValidPass,
  kNotLogin,
};

const char *LoginStrError(LoginErrc val) {
  switch (val) {
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

struct ErrorCategory {
  virtual const char *Message(int val) = 0;
};

struct ErrorCode {
  int val;
  ErrorCategory *category;

  bool operator==(const ErrorCode &ec) const { return ec.val == this->val; }
};

auto *StdErrorCategory() {  // 防止实例被外部构造
  struct StdErrorCategory : ErrorCategory {
    virtual const char *Message(int val) override { return strerror(val); }
  };

  static StdErrorCategory instance;
  return &instance;
}

auto *LoginErrorCategory() {  // 防止实例被外部构造
  struct LoginErrorCategory : ErrorCategory {
    virtual const char *Message(int val) override { return LoginStrError((LoginErrc)val); }
  };

  static LoginErrorCategory instance;
  return &instance;
}

// 强类型枚举，所以构成重载
ErrorCode MakeErrorCode(std::errc ec) { return {(int)ec, StdErrorCategory()}; }
ErrorCode MakeErrorCode(LoginErrc ec) { return {(int)ec, LoginErrorCategory()}; }

// 现代C++
int MySqrt(int x, ErrorCode &ec) {  // return >= 0
  if (x < 0) {
    ec = {(int)std::errc::argument_out_of_domain, StdErrorCategory()};  // error1，系统异常
    return -1;
  }
  if (x == 3) {
    ec = {(int)LoginErrc::kNotValidPass, LoginErrorCategory()};  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = MakeErrorCode(LoginErrc::kNotLogin);  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void TestSqrt() {
  ErrorCode ec = ErrorCode();
  auto res = MySqrt(4, ec);
  if (ec.val != 0) {  // 此时检查错误原因，利用ec
    const char *str = ec.category->Message(ec.val);
    std::cout << "res: " << str << std::endl;
    if (ec == ErrorCode{(int)LoginErrc::kNotLogin, LoginErrorCategory()}) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code4

namespace error_code5 {
enum class LoginErrc {  // 强类型枚举
  kSuccess = 0,
  kNotValidPass,
  kNotLogin,
};

const char *LoginStrError(LoginErrc val) {
  switch (val) {
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

auto const &LoginErrorCategory() {  // 防止实例被外部构造
  struct LoginErrorCategory : std::error_category {
    virtual std::string message(int val) const override { return LoginStrError((LoginErrc)val); }
    virtual const char *name() const noexcept override { return "LoginErrc"; }
  };

  static const LoginErrorCategory kInstance;
  return kInstance;
}

// 强类型枚举，所以构成重载
std::error_code MakeErrorCode(LoginErrc ec) { return std::error_code((int)ec, LoginErrorCategory()); }

// 现代C++
int MySqrt(int x, std::error_code &ec) {  // return >= 0
  if (x < 0) {
    ec = std::make_error_code(std::errc::argument_out_of_domain);  // error1，系统异常
    // ec = make_error_code(std::errc::argument_out_of_domain); // OK，重载决议时会从根据std::errc进行推导
    return -1;
  }
  if (x == 3) {
    ec = MakeErrorCode(LoginErrc::kNotValidPass);  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = MakeErrorCode(LoginErrc::kNotLogin);  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void TestSqrt() {
  std::error_code ec = std::error_code();
  auto res = MySqrt(4, ec);
  if (ec) {  // 此时检查错误原因，利用ec
    const std::string kStr = ec.category().message(ec.value());
    std::cout << "res: " << kStr << std::endl;
    if (ec == MakeErrorCode(LoginErrc::kNotLogin)) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code5

namespace error_code6 {
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
int MySqrt(int x, std::error_code &ec) {  // return >= 0
  if (x < 0) {
    ec = std::make_error_code(std::errc::argument_out_of_domain);  // error1，系统异常
    return -1;
  }
  if (x == 3) {
    ec = MakeErrorCode(LoginErrc::kNotValidPass);  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = MakeErrorCode(LoginErrc::kNotLogin);  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void TestSqrt() {
  std::error_code ec = std::error_code();
  auto res = MySqrt(4, ec);
  if (ec) {  // 此时检查错误原因，利用ec
    const std::string kStr = ec.category().message(ec.value());
    std::cout << "res: " << kStr << std::endl;
    if (ec == MakeErrorCode(LoginErrc::kNotLogin)) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code6

namespace error_code7 {
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

void TestSqrt() {
  auto res = MySqrt(4);
  if (res.index() == 1) {
    std::cout << "variant type: " << res.index() << std::endl;
    std::cout << "res: " << std::get<1>(res).message() << std::endl;
  }
}
}  // namespace error_code7
