#include <random>
#include <algorithm>
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
    int pos; // 左シフト数
    int mino_index;
    double mcts_score;
    int n_tried;
};

constexpr int CELL_EMPTY = -1;
constexpr int N_PLAYERS = 4;
constexpr double WIN_SCORE_BONUS = 10000.0;

struct Board {
    std::bitset<BOARD_BIT_SIZE> cells[N_PLAYERS];
    std::bitset<BOARD_BIT_SIZE> silhouette; // すべてのプレイヤーの石が置かれている部分のビット集合
    Player players[N_PLAYERS];
    std::vector<std::vector<Move>> history;
    
    Board() {
        for (int i = 0; i < N_PLAYERS; ++i) {
            cells[i].reset();
        }
        history.clear();
        history.resize(N_PLAYERS);
        for (int i = 0; i < N_PLAYERS; ++i) {
            players[i] = Player();
        }
    }

    bool puttable_first(Mino mino, int pos, int player_id) {
        // 最初のミノを pos に置けるか判定する関数
        // minoのCNRが盤面の隅に来ること、minoのFILがすべて空であることが条件。

        // 各プレイヤーの開始位置（四隅）
        int corner_positions[4][2] = {
            {0, 0},                    // プレイヤー0: 左上
            {0, BOARD_SIZE + 1},       // プレイヤー1: 右上
            {BOARD_SIZE + 1, BOARD_SIZE + 1},  // プレイヤー2: 右下
            {BOARD_SIZE + 1, 0}        // プレイヤー3: 左下
        };

        std::bitset<BOARD_BIT_SIZE> corner;
        int corner_idx = corner_positions[player_id][0] * BOARD_WITH_WALL_SIZE + corner_positions[player_id][1];
        corner.set(corner_idx);
        // if (player_id != 0) {
        //     std::cerr << corner.to_string() << std::endl;
        // }

        if (!mino.shiftable_left(pos)) { // シフトできない
            // if (player_id != 0) {
            //     std::cerr << "not shiftable " << pos << std::endl;
            //     print_mino(mino);
            // }
            return false;
        }
        Mino mino_cpy = mino << pos;
        // print_mino(mino_cpy);
        if ((mino_cpy.mino[FIL_IDX] & silhouette).any()) { // 既存の石と被っている
            // if (player_id != 0) {
            //     std::cerr << "overlap with existing stones" << std::endl;
            // }
            return false;
        }
        if ((mino_cpy.mino[CNR_IDX] & corner).none()) { // 盤の隅(壁内)にCNRが来ていない
            // if (player_id != 0) {
            //     std::cerr << "corner not covered" << std::endl;
            // }
            return false;
        }
        return true;
    }

    bool puttable(Mino mino, int pos, int player_id) {
        // ミノを pos に置けるか判定する関数
        // minoのCNRに1つ以上自分の色があること、minoのすべてのEDGに自分の色がないこと、minoのFILがすべてCELL_EMPTYであることが条件。
        
        if (!mino.shiftable_left(pos)) { // シフトできない
            return false;
        }
        Mino mino_cpy = mino << pos;
        if ((mino_cpy.mino[FIL_IDX] & silhouette).any()) { // 既存の石と被っている
            return false;
        }
        if ((mino_cpy.mino[CNR_IDX] & cells[player_id]).none()) { // 角が自分の石と接していない
            return false;
        }
        if ((mino_cpy.mino[EDG_IDX] & cells[player_id]).any()) { // 辺が自分の石と接している
            return false;
        }
        return true;
    }

    std::vector<Move> generate_legal_moves(int player_id, bool is_first_move) {
        std::vector<Move> legal_moves;
        Player& player = players[player_id];
        
        for (size_t mino_index = 0; mino_index < player.minos.size(); ++mino_index) {
            Mino& mino = player.minos[mino_index];
            if (!mino.usable) {
                continue;
            }
            
            for (int pos = 0; pos <= BOARD_BIT_SIZE; ++pos) {
            // for (int pos = 0; pos <= 10; ++pos) {
                if (is_first_move) {
                    if (puttable_first(mino, pos, player_id)) {
                        legal_moves.push_back({pos, static_cast<int>(mino_index), 0.0, 0});
                    }
                } else {
                    if (puttable(mino, pos, player_id)) {
                        legal_moves.push_back({pos, static_cast<int>(mino_index), 0.0, 0});
                    }
                }
            }
        }
        std::cerr << legal_moves.size() << " legal moves generated for Player " << player_id << (is_first_move ? " (first move)" : "") << ".\n";
        return legal_moves;
    }

    void put_mino(int player_id, const Move& move) {
        Player& player = players[player_id];
        Mino& mino = player.minos[move.mino_index];
        
        // ミノを盤面に配置
        std::bitset<BOARD_BIT_SIZE> put_mino = mino.mino[FIL_IDX] << move.pos;
        cells[player_id] |= put_mino;
        silhouette |= put_mino;

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
        for (int i = 0; i < BOARD_SIZE + 2; ++i) {
            std::cerr << "_";
        }
        std::cout << "\n";
        for (int i = 1; i < BOARD_SIZE + 1; ++i) {
            std::cerr << "|";
            for (int j = 1; j < BOARD_SIZE + 1; ++j) {
                int pos = i * BOARD_WITH_WALL_SIZE + j;
                int player_at_pos = -1;
                
                for (int p = 0; p < N_PLAYERS; ++p) {
                    if (cells[p][pos]) {
                        player_at_pos = p;
                        break;
                    }
                }
                
                if (player_at_pos == -1) {
                    std::cout << " ";
                } else {
                    std::cout << player_at_pos;
                }
            }
            std::cerr << "|";
            std::cout << "\n";
        }
        for (int i = 0; i < BOARD_SIZE + 2; ++i) {
            std::cerr << "`";
        }
        std::cout << "\n";
    }

    void print_move(int player_id, const Move& move) {
        std::cout << "Player " << player_id << " places mino " << move.mino_index << " at " << move.pos << "\n";
        print_mino(players[player_id].minos[move.mino_index]);
    }

    int calculate_score(int player_id) {
        Player& player = players[player_id];
        return -player.remaining_mino_size;
    }

    double calculate_mcts_score(int player_id) {
        std::vector<int> scores_sorted;
        int player_score;
        for (int i = 0; i < N_PLAYERS; ++i) {
            int score = calculate_score(i);
            scores_sorted.push_back(score);
            if (i == player_id) {
                player_score = score;
            }
        }
        std::sort(scores_sorted.begin(), scores_sorted.end(), std::greater<int>());
        double score;
        if (player_score == scores_sorted[0]) {
            int second_diff = scores_sorted[0] - scores_sorted[1];
            score = static_cast<double>(player_score) + second_diff; // スコア+2位との差分
        } else {
            int diff = scores_sorted[0] - player_score; // 1位との差分
            score = static_cast<double>(player_score) - diff; // スコア-1位との差分
        }
        // if (player_score == scores_sorted[0] && player_score > scores_sorted[1]) { // 単独1位
        //     int second_diff = scores_sorted[0] - scores_sorted[1];
        //     score = static_cast<double>(player_score) + WIN_SCORE_BONUS - second_diff; // スコア+ボーナス-2位との差分
        // } else if (player_score == scores_sorted[0] && player_score == scores_sorted[1]) { // 1位タイ
        //     int tie_count = std::count(scores_sorted.begin(), scores_sorted.end(), player_score);
        //     score = static_cast<double>(player_score) + WIN_SCORE_BONUS / tie_count; // スコア+ボーナス/タイ人数
        // } else { // 2位以降
        //     int diff = scores_sorted[0] - player_score; // 1位との差分
        //     score = static_cast<double>(player_score) - diff; // スコア-1位との差分
        // }
        return score;
    }

    void print_scores() {
        for (int i = 0; i < N_PLAYERS; ++i) {
            int score = calculate_score(i);
            std::cout << "Player " << i << " score: " << score << "\n";
        }
    }

    Move get_random_move(int player_id) {
        Player& player = players[player_id];
        std::vector<Move> legal_moves = generate_legal_moves(player_id, player.is_first_move);
        
        if (legal_moves.empty()) {
            return {-1, -1, MINO_IDX_PASS}; // パス
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, legal_moves.size() - 1);
        int move_idx = dis(gen);
        
        return legal_moves[move_idx];
    }

    void random_playout(int start_player_id) {
        // start_player_idからランダムにゲームを進行させる関数
        int current_player = start_player_id;
        int consecutive_passes = 0;
        while (consecutive_passes < N_PLAYERS) {
            print_board();
            
            // ランダムな手を取得
            Move move = get_random_move(current_player);
            
            if (move.mino_index == MINO_IDX_PASS) {
                // パス
                history[current_player].push_back(move);
                std::cerr << "Player " << current_player << " passes.\n";
                consecutive_passes++;
            } else {
                // 手を実行
                std::cerr << "Player " << current_player << " places mino " << move.mino_index << " at " << move.pos << "\n";
                put_mino(current_player, move);
                consecutive_passes = 0;
            }

            std::cerr << "\n";
            
            // 次のプレイヤーへ
            current_player = (current_player + 1) % N_PLAYERS;
        }

        print_scores();
    }
};