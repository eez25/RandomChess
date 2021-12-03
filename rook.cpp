#include "rook.hpp"

#include "board.hpp"

extern Board Bd;

std::vector<std::pair<int,int>> Rook::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;

    // a Rook can move up the board until it meets a piece, and can capture it if it is an enemy
    int c = get_position().second;
    for (int r = get_position().first + 1; r < BOARD_LENGTH; r++)
    {
        if (check_valid(&moves, r, c)) break;
    }

    // the same, down the board
    for (int r = get_position().first - 1; r >= 0; r--)
    {
        if (check_valid(&moves, r, c)) break;
    }

    // the same, to the right
    int r = get_position().first;
    for (int c = get_position().second + 1; c < BOARD_LENGTH; c++)
    {
        if (check_valid(&moves, r, c)) break;
    }

    // the same, down the board
    for (int c = get_position().second - 1; c >= 0; c--)
    {
        if (check_valid(&moves, r, c)) break;
    }

    return moves;
}

std::vector < std::pair<int, int>> Rook::get_blockables()
{
    std::vector<std::pair<int, int>> blockables;

    std::pair<int, int> rook_pos = get_position(),
        king_pos = Bd.get_active_pieces(PType::K, Piece::opposite(get_team()))[0]->get_position();

    // if the rook and king are in the same row, the rook can be captured or any space between
    // them can be occupied to block the check
    if (rook_pos.first - king_pos.first == 0)
    {
        int r = rook_pos.first;
        for (int c = rook_pos.second; c != king_pos.second; king_pos.second > rook_pos.second ? c++ : c--)
        {
            blockables.emplace_back(r, c);
        }
    }

    // else if the rook and king are in the same column, same as above
    else {
        int c = rook_pos.second;
        for (int r = rook_pos.first; r != king_pos.first; king_pos.first > rook_pos.first ? r++ : r--)
        {
            blockables.emplace_back(r, c);
        }
    }

    return blockables;
}