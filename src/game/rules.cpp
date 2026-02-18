#include "game/rules.hpp"

Game::Rules::Rules(int time_start, int time_end, int score_max) : score{score_max}, time{time_start, time_end} {}
