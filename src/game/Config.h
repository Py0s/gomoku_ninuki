#pragma once

struct Config {
    bool human_player_1;
    bool human_player_2;
    bool fivebreak_rule;
    bool doublethree_rule;
    float ai_time;
    bool continue_game;

    Config() {
        human_player_1 = true;
        human_player_2 = false;
        fivebreak_rule = true;
        doublethree_rule = true;
        ai_time = 1;
        continue_game = true;
    }
//    int ai_player_pos; // Set -1 if no ai
};
