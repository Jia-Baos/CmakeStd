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

#ifndef _SRC_EVENT_PLAYER_MOVE_EVENT_HPP_
#define _SRC_EVENT_PLAYER_MOVE_EVENT_HPP_

#include "./Event.hpp"
#include "../Player.hpp"

/**
 * \brief Example event class to showcase some of the features of the EventBus
 *
 * This is not part of the core functionality and can be modified or deleted as desired
 */
class PlayerMoveEvent : public Event {
 public:
  PlayerMoveEvent(Object &sender, Player &player, int oldX, int oldY, int oldZ)
      : Event(sender), player_(player), old_x_(oldX), old_y_(oldY), old_z_(oldZ) {}

  virtual ~PlayerMoveEvent() {}

  Player &GetPlayer() { return player_; }

  int GetOldX() { return old_x_; }

  int GetOldY() { return old_y_; }

  int GetOldZ() { return old_z_; }

 private:
  Player &player_;

  int old_x_;
  int old_y_;
  int old_z_;
};

#endif /* _SRC_EVENT_PLAYER_MOVE_EVENT_HPP_ */
