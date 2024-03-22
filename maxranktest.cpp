//
// Created by Gal Ishai on 3/21/24.
//

#include "olympics24a2.h"
#include <iostream>

int main()
{
    olympics_t olympus;
    std::cout << (int)olympus.add_team(1) << '\n';
    std::cout << (int)olympus.add_team(2) << '\n';
    std::cout << (int)olympus.add_team(3) << '\n';
    std::cout << (int)olympus.add_team(4) << '\n';
    std::cout << (int)olympus.add_player(2,6) << '\n';
    std::cout << (int)olympus.add_player(1,5) << '\n';
    std::cout << (int)olympus.add_player(3,7) << '\n';
    std::cout << (int)olympus.add_player(4,8) << '\n';
    std::cout << (int)olympus.play_tournament(5,8).ans() << '\n';
    std::cout << (int)olympus.get_highest_ranked_team().ans() << '\n';



}