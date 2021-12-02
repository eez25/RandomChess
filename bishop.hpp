#include "piece.hpp"

// making this a virtual class because it is one of two (this and Rook) that
// are subclassed by the same child class (Queen)
class Bishop : virtual public Piece 
{
    public:
        //constructor
        Bishop(Team team, std::pair<int,int> pos) : Piece(PType::Bishop, team, pos){}
        Bishop() = default;
        
        std::vector<std::pair<int,int>> get_valid_moves();
};