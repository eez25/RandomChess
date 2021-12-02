#include "piece.hpp"

class King : public Piece 
{
    public:
        //constructor
        King(Team team, int r, col c) : Piece(PType::K, team, std::pair(r,(int)c)){}
        
        std::vector<std::pair<int,int>> get_valid_moves();
};