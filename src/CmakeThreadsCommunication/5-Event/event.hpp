/**
 * @file event.hpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief Event Manager
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

/*----------------------------------------------------------------*/
/* class Object   响应事件函数的类必须是从Object派生下来          */
/*----------------------------------------------------------------*/
class Object {};

/*----------------------------------------------------------------*/
/* class Event     模板参数为 返回类型 和响应函数参数类型         */
/* 仅实现一个参数的事件响应函数                                   */
/*----------------------------------------------------------------*/

template <typename rtnTtpe, typename ArgType>
class Event {
// 使每个事件最多关联响应的函数个数
#define EVENT_LIST_MAX_NUM (10)
  typedef rtnTtpe (Object::*pMemFunc)(ArgType arg);

 public:
  Event() {
    m_total_func_ = 0;
    m_obj_ = nullptr;
    for (int i = 0; i < EVENT_LIST_MAX_NUM; i++) {
      m_func_[i] = nullptr;
    }
  }

  // 关联回调成员函数
  template <class _func_type>
  void Associate(Object *obj, _func_type func) {
    m_obj_ = obj;
    m_func_[m_total_func_] = static_cast<pMemFunc>(func);
    m_total_func_++;
  }
  // 删除事件关联回调成员函数
  template <class _func_type>
  void DisAssociate(Object *obj, _func_type func) {
    if (obj != m_obj_) {
      return;
    }

    // 查找
    for (int i = 0; i < m_total_func_; i++) {
      if (m_func_[i] == func) {
        break;
      }
    }

    // 移动删除
    for (int i; i < m_total_func_ - 1; i++) {
      m_func_[i] = m_func_[i + 1];
      m_func_[i] = nullptr;
      m_total_func_--;
    }
  }

  // 执行关联的回调函数
  void SendEvent(ArgType arg) {
    for (int i = 0; i < m_total_func_; i++) {
      if (m_func_[i] != nullptr) {
        ((m_obj_->*pMemFunc(m_func_[i])))(arg);
      }
    }
  }

 private:
  Object *m_obj_;
  pMemFunc m_func_[EVENT_LIST_MAX_NUM];
  int m_total_func_;
};

/*----------------------------------------------------------------*/
/* class TestEvent                                                */
/*----------------------------------------------------------------*/
class TestEvent {
 public:
  void Test() {
    // do somsthing
    // ……

    // 触发事件
    my_event.SendEvent(100);
    my_event.SendEvent(200);
  }

 public:
  // 定义事件
  Event<bool, int> my_event;
};

/*----------------------------------------------------------------*/
/* class TestClass                                                */
/*----------------------------------------------------------------*/
class TestClass : public Object {
 public:
  TestClass() {
    // 关联事件
    m_event_.my_event.Associate(this, &TestClass::ExecuteCb1);
    m_event_.my_event.Associate(this, &TestClass::ExecuteCb2);
  }

  // 事件响应函数
  bool ExecuteCb1(int result) {
    std::cout << "executeCb1 result = " << result << std::endl;
    return true;
  }
  // 事件响应函数
  bool ExecuteCb2(int result) {
    std::cout << "executeCb2 result = " << result << std::endl;
    return true;
  }

  void Execute() { m_event_.Test(); }
  void Stop() {
    // 删除事件关联函数
    m_event_.my_event.DisAssociate(this, &TestClass::ExecuteCb1);
  }

 private:
  TestEvent m_event_;
};
