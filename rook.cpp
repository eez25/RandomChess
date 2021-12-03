#include "rook.hpp"

#include "board.hpp"

extern Board Bd;

std::vector<std::pair<int,int>> Rook::get_valid_moves()
{
    return get_valid_rook_moves();
}

std::vector < std::pair<int, int>> Rook::get_blockables()
{
    return get_rook_blockables();
}