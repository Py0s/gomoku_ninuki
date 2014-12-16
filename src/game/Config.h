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
        ai_time = 10;
        continue_game = true;
    }

    void debug_config() {
        std::cout << "----------Config----------" << std::endl;
        std::cout << human_player_1 << std::endl;
        std::cout << human_player_2 << std::endl;
        std::cout << fivebreak_rule << std::endl;
        std::cout << doublethree_rule << std::endl;
        std::cout << ai_time << std::endl;
        std::cout << continue_game << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
//    int ai_player_pos; // Set -1 if no ai
};
