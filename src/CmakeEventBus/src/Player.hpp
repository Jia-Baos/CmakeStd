/*
 * Copyright (c) 2014, Dan Quist
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _SRC_PLAYER_HPP_
#define _SRC_PLAYER_HPP_

#include "./event_bus_utils/Object.hpp"

#include <string>

class PlayerMoveEvent;

/**
 * \brief Demo class to showcase some of the features of the EventBus
 *
 * This is not part of the core functionality and can be modified or deleted as desired
 */
class Player : public Object {
 public:
  Player(std::string name) : name_(name), pos_x_(0), pos_y_(0), pos_z_(0) {}

  virtual ~Player() {}

  const std::string &GetName() { return name_; }

  void SetPosition(int x, int y, int z) {
    pos_x_ = x;
    pos_y_ = y;
    pos_z_ = z;
  }

  int GetX() { return pos_x_; }

  int GetY() { return pos_y_; }

  int GetZ() { return pos_z_; }

 private:
  std::string name_;
  int pos_x_;
  int pos_y_;
  int pos_z_;
};

#endif /* _SRC_PLAYER_HPP_ */
