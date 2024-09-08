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

#ifndef _SRC_EVENT_PLAYER_CHAT_EVENT_HPP_
#define _SRC_EVENT_PLAYER_CHAT_EVENT_HPP_

#include "./Event.hpp"
#include "../Player.hpp"

#include <string>

class PlayerChatEvent : public Event {
 public:
  PlayerChatEvent(Object &sender, Player &player, std::string const &msg) : Event(sender), player_(player), msg_(msg) {}

  virtual ~PlayerChatEvent() {}

  Player &GetPlayer() { return player_; }

  std::string const &GetMessage() { return msg_; }

 private:
  Player &player_;
  std::string const &msg_;
};

#endif /* _SRC_EVENT_PLAYER_CHAT_EVENT_HPP_ */
