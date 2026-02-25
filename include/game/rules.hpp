#pragma once

#include "game/counter.hpp"
#include "game/score.hpp"

// Forward
namespace Audio
{
class Instance;
} // namespace Audio
//

namespace Game
{
namespace GUI{class Layout;}

class Rules
{
public:
  Rules(int time_start, int time_end, int score_max, int high_score);

  Score score;
  Counter<int> time{0, 60};

  auto restartGame(Audio::Instance &audio, Game::GUI::Layout &game_ui) -> void;
};
} // namespace Game
