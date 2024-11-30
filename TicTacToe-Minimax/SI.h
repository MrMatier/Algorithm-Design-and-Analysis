#ifndef SI_H
#define SI_H

#include <vector>
#include <utility>

class SI {
public:
    static std::pair<int, int> znajdzNajlepszyRuch(const std::vector<std::vector<char>>& board, int size, int winCondition);

private:
    static int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizingPlayer, char player, char opponent, int alpha, int beta, int size, int winCondition);
    static int ocena(const std::vector<std::vector<char>>& board, char player, char opponent, int size, int winCondition);
    static bool isValidMove(const std::vector<std::vector<char>>& board, int row, int col, int size);
    static bool checkWin(const std::vector<std::vector<char>>& board, char player, int size, int winCondition);
    static bool checkDraw(const std::vector<std::vector<char>>& board, int size);
};

#endif 

