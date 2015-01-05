#pragma once

struct Config {
    bool continue_game;
    bool human_player_1;
    bool human_player_2;
    float ai_time;
    bool fivebreak_rule;
    bool doublethree_rule;
    bool help;

    Config() {
        continue_game = true;
        human_player_1 = true;
        human_player_2 = false;
        ai_time = 0.5;
        fivebreak_rule = true;
        doublethree_rule = true;
        help = true;
    }

    void debug_config() {
        std::cout << "----------Config----------" << std::endl;
        std::cout << "continue_game " << std::boolalpha << continue_game << std::endl;
        std::cout << "human_player_1 " << std::boolalpha << human_player_1 << std::endl;
        std::cout << "human_player_2 " << std::boolalpha << human_player_2 << std::endl;
        std::cout << "ai_time " << std::boolalpha << ai_time << std::endl;
        std::cout << "fivebreak_rule " << std::boolalpha << fivebreak_rule << std::endl;
        std::cout << "doublethree_rule " << std::boolalpha << doublethree_rule << std::endl;
        std::cout << "help " << std::boolalpha << help << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
//    int ai_player_pos; // Set -1 if no ai
};
