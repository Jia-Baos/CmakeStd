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
    m_totalFunc = 0;
    m_obj = nullptr;
    for (int i = 0; i < EVENT_LIST_MAX_NUM; i++) {
      m_func[i] = nullptr;
    }
  }

  // 关联回调成员函数
  template <class _func_type>
  void associate(Object *obj, _func_type func) {
    m_obj = obj;
    m_func[m_totalFunc] = static_cast<pMemFunc>(func);
    m_totalFunc++;
  }
  // 删除事件关联回调成员函数
  template <class _func_type>
  void disAssociate(Object *obj, _func_type func) {
    if (obj != m_obj) {
      return;
    }

    // 查找
    for (int i = 0; i < m_totalFunc; i++) {
      if (m_func[i] == func) {
        break;
      }
    }

    // 移动删除
    for (int i; i < m_totalFunc - 1; i++) {
      m_func[i] = m_func[i + 1];
      m_func[i] = nullptr;
      m_totalFunc--;
    }
  }

  // 执行关联的回调函数
  void sendEvent(ArgType arg) {
    for (int i = 0; i < m_totalFunc; i++) {
      if (m_func[i] != nullptr) {
        ((m_obj->*pMemFunc(m_func[i])))(arg);
      }
    }
  }

 private:
  Object *m_obj;
  pMemFunc m_func[EVENT_LIST_MAX_NUM];
  int m_totalFunc;
};

/*----------------------------------------------------------------*/
/* class TestEvent                                                */
/*----------------------------------------------------------------*/
class TestEvent {
 public:
  void test() {
    // do somsthing
    // ……

    // 触发事件
    myEvent.sendEvent(100);
    myEvent.sendEvent(200);
  }

 public:
  // 定义事件
  Event<bool, int> myEvent;
};

/*----------------------------------------------------------------*/
/* class TestClass                                                */
/*----------------------------------------------------------------*/
class TestClass : public Object {
 public:
  TestClass() {
    // 关联事件
    m_event.myEvent.associate(this, &TestClass::executeCb1);
    m_event.myEvent.associate(this, &TestClass::executeCb2);
  }

  // 事件响应函数
  bool executeCb1(int result) {
    std::cout << "executeCb1 result = " << result << std::endl;
    return true;
  }
  // 事件响应函数
  bool executeCb2(int result) {
    std::cout << "executeCb2 result = " << result << std::endl;
    return true;
  }

  void execute() { m_event.test(); }
  void stop() {
    // 删除事件关联函数
    m_event.myEvent.disAssociate(this, &TestClass::executeCb1);
  }

 private:
  TestEvent m_event;
};
