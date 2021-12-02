#include "piece.hpp"

class Knight : public Piece 
{
    public:
        //constructor
        Knight(Team team, int r, col c) : Piece(PType::N, team, std::pair(r,(int)c)){}

        std::vector<std::pair<int,int>> get_valid_moves();
};