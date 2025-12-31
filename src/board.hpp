#include <random>
#include "mino.hpp"

struct Player {
    std::vector<Mino> minos;
    int remaining_mino_size;
    bool is_first_move = true;

    Player() {
        minos = all_minos;
        remaining_mino_size = 0;
        for (const auto &mino: unique_minos) {
            remaining_mino_size += mino.size;
        }
        is_first_move = true;
    }
};

constexpr int MINO_IDX_PASS = -1;

struct Move {
    int top;
    int left;
    int mino_index;
};

constexpr int BOARD_SIZE = 20;
constexpr int CELL_EMPTY = -1;
constexpr int N_PLAYERS = 4;

struct Board {
    int cells[BOARD_SIZE + 2][BOARD_SIZE + 2];
    Player players[N_PLAYERS];
    std::vector<std::vector<Move>> history;
    
    Board() {
        for (int i = 0; i < BOARD_SIZE + 2; ++i) {
            for (int j = 0; j < BOARD_SIZE + 2; ++j) {
                cells[i][j] = CELL_EMPTY;
            }
        }
        history.resize(N_PLAYERS);
        for (int i = 0; i < N_PLAYERS; ++i) {
            players[i] = Player();
        }
    }

    bool puttable_first(Mino mino, int top, int left, int player_id) {
        // 最初のミノを (top, left) に置けるか判定する関数
        // minoのCNRが盤面の隅に来ること、minoのFILがすべてCELL_EMPTYであることが条件。

        // 各プレイヤーの開始位置（四隅）
        int corner_positions[4][2] = {
            {0, 0},                    // プレイヤー0: 左上
            {0, BOARD_SIZE + 1},       // プレイヤー1: 右上
            {BOARD_SIZE + 1, BOARD_SIZE + 1},  // プレイヤー2: 右下
            {BOARD_SIZE + 1, 0}        // プレイヤー3: 左下
        };
        
        int corner_i = corner_positions[player_id][0];
        int corner_j = corner_positions[player_id][1];
        
        bool touches_corner = false;
        
        for (size_t i = 0; i < mino.h; ++i) {
            for (size_t j = 0; j < mino.w; ++j) {
                int board_i = top + i;
                int board_j = left + j;
                
                // ボードの範囲外チェック
                if (board_i < 0 || board_i >= BOARD_SIZE + 2 || 
                    board_j < 0 || board_j >= BOARD_SIZE + 2) {
                    return false;
                }
                
                int cell_type = mino.mino[i][j];
                int board_cell = cells[board_i][board_j];
                
                if (cell_type == FIL) {
                    // FILのセルは空でなければならない
                    if (board_cell != CELL_EMPTY) {
                        return false;
                    }
                } else if (cell_type == CNR) {
                    // CNRのセルが盤面の隅と一致するかチェック
                    if (board_i == corner_i && board_j == corner_j) {
                        touches_corner = true;
                    }
                }
            }
        }
        
        // 盤面の隅に接している必要がある
        return touches_corner;
    }

    bool puttable(Mino mino, int top, int left, int player_id) {
        // ミノを (top, left) に置けるか判定する関数
        // minoのCNRに1つ以上自分の色があること、minoのすべてのEDGに自分の色がないこと、minoのFILがすべてCELL_EMPTYであることが条件。
        
        bool has_corner = false;
        
        for (size_t i = 0; i < mino.h; ++i) {
            for (size_t j = 0; j < mino.w; ++j) {
                int board_i = top + i;
                int board_j = left + j;
                
                // ボードの範囲外チェック
                if (board_i < 0 || board_i >= BOARD_SIZE + 2 || 
                    board_j < 0 || board_j >= BOARD_SIZE + 2) {
                    return false;
                }
                
                int cell_type = mino.mino[i][j];
                int board_cell = cells[board_i][board_j];
                
                if (cell_type == FIL) {
                    // FILのセルは空でなければならない
                    if (board_cell != CELL_EMPTY) {
                        return false;
                    }
                } else if (cell_type == EDG) {
                    // EDGのセルに自分の色があってはならない
                    if (board_cell == player_id) {
                        return false;
                    }
                } else if (cell_type == CNR) {
                    // CNRのセルに自分の色があるかチェック
                    if (board_cell == player_id) {
                        has_corner = true;
                    }
                }
            }
        }
        
        // CNRに少なくとも1つ自分の色が必要
        return has_corner;
    }

    std::vector<Move> generate_legal_moves(int player_id, bool is_first_move) {
        std::vector<Move> legal_moves;
        Player& player = players[player_id];
        
        for (size_t mino_index = 0; mino_index < player.minos.size(); ++mino_index) {
            Mino& mino = player.minos[mino_index];
            if (!mino.usable) continue;
            
            for (int top = 0; top <= BOARD_SIZE + 2 - static_cast<int>(mino.h); ++top) {
                for (int left = 0; left <= BOARD_SIZE + 2 - static_cast<int>(mino.w); ++left) {
                    if (is_first_move) {
                        if (puttable_first(mino, top, left, player_id)) {
                            legal_moves.push_back({top, left, static_cast<int>(mino_index)});
                        }
                    } else {
                        if (puttable(mino, top, left, player_id)) {
                            legal_moves.push_back({top, left, static_cast<int>(mino_index)});
                        }
                    }
                }
            }
        }
        
        return legal_moves;
    }

    void put_mino(int player_id, const Move& move) {
        Player& player = players[player_id];
        Mino& mino = player.minos[move.mino_index];
        
        // ミノを盤面に配置
        for (size_t i = 0; i < mino.h; ++i) {
            for (size_t j = 0; j < mino.w; ++j) {
                if (mino.mino[i][j] == FIL) {
                    cells[move.top + i][move.left + j] = player_id;
                }
            }
        }
        
        // 使用したミノとそのfamilyの全てを使用不可にする
        for (int family_idx : mino.families) {
            player.minos[family_idx].usable = false;
        }
        
        // remaining_mino_sizeを更新
        player.remaining_mino_size -= mino.size;
        
        // 履歴に追加
        history[player_id].push_back(move);
        
        // 初手フラグを更新
        player.is_first_move = false;
    }

    void print_board() {
        for (int i = 1; i < BOARD_SIZE + 1; ++i) {
            for (int j = 1; j < BOARD_SIZE + 1; ++j) {
                if (cells[i][j] == CELL_EMPTY) {
                    std::cout << ".";
                } else {
                    std::cout << static_cast<int>(cells[i][j]);
                }
            }
            std::cout << "\n";
        }
    }

    void print_move(int player_id, const Move& move) {
        std::cout << "Player " << player_id << " places mino " << move.mino_index << " at (" << move.top << ", " << move.left << ")\n";
        print_mino(players[player_id].minos[move.mino_index]);
    }

    int calculate_score(int player_id) {
        Player& player = players[player_id];
        return -player.remaining_mino_size;
    }

    void print_scores() {
        for (int i = 0; i < N_PLAYERS; ++i) {
            int score = calculate_score(i);
            std::cout << "Player " << i << " score: " << score << "\n";
        }
    }

    void random_play(int start_player_id) {
        // start_player_idからランダムにゲームを進行させる関数
        std::random_device rd;
        std::mt19937 gen(rd());
        
        int current_player = start_player_id;
        int consecutive_passes = 0;
        while (consecutive_passes < N_PLAYERS) {
            Player& player = players[current_player];
            
            // 合法手を生成
            std::vector<Move> legal_moves = generate_legal_moves(current_player, player.is_first_move);

            print_board();
            
            if (legal_moves.empty()) {
                // パス
                history[current_player].push_back({-1, -1, MINO_IDX_PASS});
                std::cerr << "Player " << current_player << " passes.\n";
                consecutive_passes++;
            } else {
                // ランダムに1手選んで実行
                std::uniform_int_distribution<> dis(0, legal_moves.size() - 1);
                int move_idx = dis(gen);
                print_move(current_player, legal_moves[move_idx]);
                put_mino(current_player, legal_moves[move_idx]);
                consecutive_passes = 0;
            }

            std::cerr << "\n";
            
            // 次のプレイヤーへ
            current_player = (current_player + 1) % N_PLAYERS;
        }

        print_scores();
    }
};