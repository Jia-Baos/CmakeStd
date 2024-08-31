#pragma once

#include <iostream>
#include <utility>
#include <optional>
#include <system_error>

#include <string.h>
#include <errno.h>

namespace error_code1 {
int sqrt1(int x) {  // return >= 0
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

std::pair<int, bool> sqrt2(int x) {  // return >= 0
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
std::optional<int> sqrt3(int x) {
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
int sqrt4(int x, int *pret) {  // return >= 0
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
int sqrt5(int x) {               // return >= 0
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
int sqrt6(int x) {  // return >= 0
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
int sqrt7(int x, int &ec) {  // return >= 0
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

void testErrorCode() {
  auto res1 = sqrt1(-1);
  if (res1 == -1) {
    std::cout << "res1: x can't be less 0" << std::endl;
  }

  auto res2 = sqrt2(-1);
  if (res2.second == false) {
    std::cout << "res2: x can't be less 0" << std::endl;
  }

  auto res3 = sqrt3(-1);
  if (res3.has_value() == false) {
    std::cout << "res3: x can't be less 0" << std::endl;
  }

  int pret{};
  auto res4 = sqrt4(-1, &pret);
  if (res4 == 1) {
    std::cout << "res4: x can't be less 0" << std::endl;
  } else if (res4 = 2) {
    std::cout << "res4: x can't be 4" << std::endl;
  }

  auto res5 = sqrt5(-1);
  if (res5 == -1) {  // 此时检查错误原因，利用errorno_own
    if (errorno_own == 1) {
      std::cout << "res5: x can't be less 0" << std::endl;
    } else if (errorno_own == 2) {
      std::cout << "res5: x can't be 4" << std::endl;
    }
  }

  setlocale(LC_ALL, "zh_CN.UTF-8");  // 设置错误为中文显示
  auto res6 = sqrt6(4);
  if (res6 == -1) {  // 此时检查错误原因，利用errno
    const char *str = strerror(errno);
    std::cout << "res6: " << str << std::endl;
    perror("res6: ");  // 自动添加错误原因
  }

  int ec{};
  auto res7 = sqrt7(4, ec);
  if (res7 == -1) {  // 此时检查错误原因，利用ec
    const char *str = strerror(ec);
    std::cout << "res7: " << str << std::endl;
    perror("res7: ");  // 自动添加错误原因
  }
}
}  // namespace error_code1

namespace error_code2 {
enum class LoginErrc {  // 强类型枚举
  success = 0,
  not_valid_pass,
  not_login,

};

const char *LoginStrError(LoginErrc ec) {
  switch (ec) {
    case LoginErrc::success:
      return "login success";
      break;
    case LoginErrc::not_valid_pass:
      return "not_valid_pass";
      break;
    case LoginErrc::not_login:
      return "not_login";
      break;

    default:
      return "unkonow error";
      break;
  }
}

// 现代C++
int sqrt(int x, LoginErrc &ec) {  // return >= 0
  if (x < 0) {
    ec = LoginErrc::not_valid_pass;  // error1
    return -1;
  }
  if (x == 4) {
    ec = LoginErrc::not_login;  // error2
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void test_sqrt() {
  LoginErrc ec = LoginErrc::success;
  auto res = sqrt(4, ec);
  if (ec != LoginErrc::success) {  // 此时检查错误原因，利用ec
    const char *str = LoginStrError(ec);
    std::cout << "res: " << str << std::endl;
  }
}

}  // namespace error_code2

namespace error_code3 {
enum class LoginErrc {  // 强类型枚举
  success = 0,
  not_valid_pass,
  not_login,

};

struct ErrorCode {
  int val;
  const char *(*category)(int val);

  bool operator==(const ErrorCode &) const = default;
};

const char *LoginStrError(LoginErrc val) {
  switch (val) {
    case LoginErrc::success:
      return "login success";
      break;
    case LoginErrc::not_valid_pass:
      return "not_valid_pass";
      break;
    case LoginErrc::not_login:
      return "not_login";
      break;

    default:
      return "unkonow error";
      break;
  }
}

// 现代C++
int sqrt(int x, ErrorCode &ec) {  // return >= 0
  if (x < 0) {
    ec = {(int)std::errc::argument_out_of_domain, (const char *(*)(int val))strerror};  // error1，系统异常
    return -1;
  }
  if (x == 3) {
    ec = {(int)LoginErrc::not_valid_pass, (const char *(*)(int val))LoginStrError};  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = {(int)LoginErrc::not_login, (const char *(*)(int val))LoginStrError};  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void test_sqrt() {
  ErrorCode ec = ErrorCode();
  auto res = sqrt(4, ec);
  if (ec.val != 0) {  // 此时检查错误原因，利用ec
    const char *str = ec.category(ec.val);
    std::cout << "res: " << str << std::endl;
    if (ec == ErrorCode{(int)LoginErrc::not_login, (const char *(*)(int val))LoginStrError}) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code3

namespace error_code4 {
enum class LoginErrc {  // 强类型枚举
  success = 0,
  not_valid_pass,
  not_login,
};

const char *LoginStrError(LoginErrc val) {
  switch (val) {
    case LoginErrc::success:
      return "login success";
      break;
    case LoginErrc::not_valid_pass:
      return "not_valid_pass";
      break;
    case LoginErrc::not_login:
      return "not_login";
      break;

    default:
      return "unkonow error";
      break;
  }
}

struct ErrorCategory {
  virtual const char *message(int val) = 0;
};

struct ErrorCode {
  int val;
  ErrorCategory *category;

  bool operator==(const ErrorCode &) const = default;
};

auto *stdErrorCategory() {  // 防止实例被外部构造
  struct StdErrorCategory : ErrorCategory {
    virtual const char *message(int val) override { return strerror(val); }
  };

  static StdErrorCategory instance;
  return &instance;
}

auto *loginErrorCategory() {  // 防止实例被外部构造
  struct LoginErrorCategory : ErrorCategory {
    virtual const char *message(int val) override { return LoginStrError((LoginErrc)val); }
  };

  static LoginErrorCategory instance;
  return &instance;
}

// 强类型枚举，所以构成重载
ErrorCode makeErrorCode(std::errc ec) { return {(int)ec, stdErrorCategory()}; }
ErrorCode makeErrorCode(LoginErrc ec) { return {(int)ec, loginErrorCategory()}; }

// 现代C++
int sqrt(int x, ErrorCode &ec) {  // return >= 0
  if (x < 0) {
    ec = {(int)std::errc::argument_out_of_domain, stdErrorCategory()};  // error1，系统异常
    return -1;
  }
  if (x == 3) {
    ec = {(int)LoginErrc::not_valid_pass, loginErrorCategory()};  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = makeErrorCode(LoginErrc::not_login);  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void test_sqrt() {
  ErrorCode ec = ErrorCode();
  auto res = sqrt(4, ec);
  if (ec.val != 0) {  // 此时检查错误原因，利用ec
    const char *str = ec.category->message(ec.val);
    std::cout << "res: " << str << std::endl;
    if (ec == ErrorCode{(int)LoginErrc::not_login, loginErrorCategory()}) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code4

namespace error_code5 {
enum class LoginErrc {  // 强类型枚举
  success = 0,
  not_valid_pass,
  not_login,
};

const char *LoginStrError(LoginErrc val) {
  switch (val) {
    case LoginErrc::success:
      return "login success";
      break;
    case LoginErrc::not_valid_pass:
      return "not_valid_pass";
      break;
    case LoginErrc::not_login:
      return "not_login";
      break;

    default:
      return "unkonow error";
      break;
  }
}

auto const &loginErrorCategory() {  // 防止实例被外部构造
  struct LoginErrorCategory : std::error_category {
    virtual std::string message(int val) const override { return LoginStrError((LoginErrc)val); }
    virtual const char *name() const noexcept override { return "LoginErrc"; }
  };

  static const LoginErrorCategory instance;
  return instance;
}

// 强类型枚举，所以构成重载
std::error_code makeErrorCode(LoginErrc ec) { return std::error_code((int)ec, loginErrorCategory()); }

// 现代C++
int sqrt(int x, std::error_code &ec) {  // return >= 0
  if (x < 0) {
    ec = std::make_error_code(std::errc::argument_out_of_domain);  // error1，系统异常
    // ec = make_error_code(std::errc::argument_out_of_domain); // OK，重载决议时会从根据std::errc进行推导
    return -1;
  }
  if (x == 3) {
    ec = makeErrorCode(LoginErrc::not_valid_pass);  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = makeErrorCode(LoginErrc::not_login);  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void test_sqrt() {
  std::error_code ec = std::error_code();
  auto res = sqrt(4, ec);
  if (ec) {  // 此时检查错误原因，利用ec
    const std::string str = ec.category().message(ec.value());
    std::cout << "res: " << str << std::endl;
    if (ec == makeErrorCode(LoginErrc::not_login)) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code5

namespace error_code6 {
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
int sqrt(int x, std::error_code &ec) {  // return >= 0
  if (x < 0) {
    ec = std::make_error_code(std::errc::argument_out_of_domain);  // error1，系统异常
    return -1;
  }
  if (x == 3) {
    ec = makeErrorCode(login_errc::not_valid_pass);  // error2，自定义异常
    return -1;
  }
  if (x == 4) {
    ec = makeErrorCode(login_errc::not_login);  // error3，自定义异常
    return -1;
  }
  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;  // [0, INT_MAX]
    }
  }
}

void test_sqrt() {
  std::error_code ec = std::error_code();
  auto res = sqrt(4, ec);
  if (ec) {  // 此时检查错误原因，利用ec
    const std::string str = ec.category().message(ec.value());
    std::cout << "res: " << str << std::endl;
    if (ec == makeErrorCode(login_errc::not_login)) {
      // 判断错误类型并进行处理
      std::cout << "goto the login" << std::endl;
    }
  }
}
}  // namespace error_code6

namespace error_code7 {
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

void test_sqrt() {
  auto res = sqrt(4);
  if (res.index() == 1) {
    std::cout << "variant type: " << res.index() << std::endl;
    std::cout << "res: " << std::get<1>(res).message() << std::endl;
  }
}
}  // namespace error_code7