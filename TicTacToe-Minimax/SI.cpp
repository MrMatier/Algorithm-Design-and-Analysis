#include "SI.h"
#include <climits>

std::pair<int, int> SI::znajdzNajlepszyRuch(const std::vector<std::vector<char>>& board, int size, int winCondition) {
    int bestScore = INT_MIN;
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isValidMove(board, i, j, size)) {
                std::vector<std::vector<char>> tempBoard = board;
                tempBoard[i][j] = 'O';
                int score = minimax(tempBoard, 0, false, 'O', 'X', INT_MIN, INT_MAX, size, winCondition);
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    return { bestRow, bestCol };
}

int SI::minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizingPlayer, char player, char opponent, int alpha, int beta, int size, int winCondition) {
    if (checkWin(board, player, size, winCondition)) return 100;
    if (checkWin(board, opponent, size, winCondition)) return -100;
    if (checkDraw(board, size)) return 0;

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (isValidMove(board, i, j, size)) {
                    board[i][j] = player;
                    int eval = minimax(board, depth + 1, false, player, opponent, alpha, beta, size, winCondition);
                    board[i][j] = ' ';
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (isValidMove(board, i, j, size)) {
                    board[i][j] = opponent;
                    int eval = minimax(board, depth + 1, true, player, opponent, alpha, beta, size, winCondition);
                    board[i][j] = ' ';
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

bool SI::isValidMove(const std::vector<std::vector<char>>& board, int row, int col, int size) {
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ';
}

bool SI::checkWin(const std::vector<std::vector<char>>& board, char player, int size, int winCondition) {
    for (int i = 0; i < size; ++i) {
        int count = 0;
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == player) {
                count++;
                if (count == winCondition) return true;
            }
            else {
                count = 0;
            }
        }
    }

    for (int j = 0; j < size; ++j) {
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (board[i][j] == player) {
                count++;
                if (count == winCondition) return true;
            }
            else {
                count = 0;
            }
        }
    }

    for (int i = 0; i <= size - winCondition; ++i) {
        for (int j = 0; j <= size - winCondition; ++j) {
            int count = 0;
            for (int k = 0; k < winCondition; ++k) {
                if (board[i + k][j + k] == player) {
                    count++;
                    if (count == winCondition) return true;
                }
                else {
                    count = 0;
                }
            }
        }
    }

    for (int i = 0; i <= size - winCondition; ++i) {
        for (int j = winCondition - 1; j < size; ++j) {
            int count = 0;
            for (int k = 0; k < winCondition; ++k) {
                if (board[i + k][j - k] == player) {
                    count++;
                    if (count == winCondition) return true;
                }
                else {
                    count = 0;
                }
            }
        }
    }

    return false;
}

bool SI::checkDraw(const std::vector<std::vector<char>>& board, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}
