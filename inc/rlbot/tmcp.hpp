#pragma once

#include <variant>

namespace MatchComms {

  enum class Action {
    BALL,
    BOOST,
    DEMO,
    READY,
    DEFEND
  };

  /// The bot is going for the ball.
  struct Ball{
    float time;         /// expected time contact with ball will occur
    float direction[3]; /// the direction in which the bot intends to hit the ball
  };

  /// The bot is going for boost.
  struct Boost{
    int target; /// which pad the bot intends to collect
  };

  /// The bot is going to demolish another car
  struct Demo{
    float time; /// expected time demo will occur
    int target; /// will be -1 if target is unknown 
  };

  /**
   *  The bot is waiting for a chance to go for the ball. 
   *  Some examples are positioning (retreating/shadowing) and recovering. 
   */
  struct Ready{
    float time; /// the game time when teh bot could arrive at the ball
  };

  /**
   * The bot is in a position to defend the goal and 
   * is not planning to move up. Only use DEFEND if 
   * your bot is in place to defend, not if still en-route. 
   * If the bot decides to leave the net, signal this using 
   * either "BALL" (if going for a touch) or "READY" (if moving upfield).
   * 
   * A bot should use "DEFEND" to let its teammates know it 
   * is safe to move up a bit without worrying about an open net.
   */
  struct Defend{
    // no data
  };

	using message = std::variant <
		Ball, 
		Boost, 
		Demo, 
		Ready, 
		Defend
	>;

  struct Packet {
    int version[2];
		int team;
		int index;
		message action;
  };

};