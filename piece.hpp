#pragma once

#include <string>
#include <vector>

class Piece
{
    private:
        std::string name;
        bool team;
        
    public:
        std::string get_name();
        bool get_team();
        std::vector<std::pair<int,int>> get_valid_moves();
        void move(std::pair<int,int> coords);
};