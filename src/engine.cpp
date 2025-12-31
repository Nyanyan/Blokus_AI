#include "board.hpp"
#include <chrono>

inline uint64_t tim() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}



struct Node {
    Board board;
    int start_player_id;
    double value;

    Node(const Board& b, int pid) : board(b), start_player_id(pid) {}
};

Move get_best_move(Board& board, int player_id) {
    Player& player = board.players[player_id];
    std::vector<Move> legal_moves = board.generate_legal_moves(player_id, player.is_first_move);
    
    if (legal_moves.empty()) {
        return {-1, -1, MINO_IDX_PASS}; // パス
    }

    std::cerr << "Evaluating " << legal_moves.size() << " legal moves for Player " << player_id << " using MC...\n";

    const int n_try_per_move = 5;
    for (auto& move : legal_moves) {
        move.mcts_score = 0.0;
        move.n_tried = 0;
        uint64_t strt = tim();
        for (int i = 0; i < n_try_per_move; ++i) {
            Board sim_board = board;
            sim_board.put_mino(player_id, move);
            sim_board.random_playout((player_id + 1) % N_PLAYERS);
            double score = sim_board.calculate_mcts_score(player_id);
            move.mcts_score += static_cast<double>(score);
            move.n_tried++;
        }
        move.mcts_score /= static_cast<double>(move.n_tried);
        std::cerr << "Move at pos " << move.pos << " with mino " << move.mino_index << " has MC score: " << move.mcts_score << " after " << move.n_tried << " trials. elapsed " << (tim() - strt) << " ms (" << (tim() - strt) / move.n_tried << " ms/it)\n";
    }
    // 最もスコアの高い手を選択
    Move* best_move = &legal_moves[0];
    for (auto& move : legal_moves) {
        if (move.mcts_score > best_move->mcts_score) {
            best_move = &move;
        }
    }
    std::cerr << "Best move chosen at pos " << best_move->pos << " with mino " << best_move->mino_index << " having MC score: " << best_move->mcts_score << "\n";
    return *best_move;
}



int main() {
    init_unique_minos();
    init_all_minos();

    int ai_player_id = 0;
    int start_player_id = 0;

    Board board;

    std::vector<Node> nodes;
    nodes.emplace_back(board, start_player_id);

    int current_player = start_player_id;
    int consecutive_passes = 0;
    while (consecutive_passes < N_PLAYERS) {
        board.print_board();
        Move move;
        if (current_player == ai_player_id) {
            std::cout << "AI's turn (Player " << current_player << ")\n";
            move = get_best_move(board, current_player);
        } else {
            std::cout << "Random player's turn (Player " << current_player << ")\n";
            move = board.get_random_move(current_player);
        }

        if (move.mino_index == MINO_IDX_PASS) {
            // パス
            board.history[current_player].push_back(move);
            std::cerr << "Player " << current_player << " passes.\n";
            consecutive_passes++;
        } else {
            // 手を実行
            std::cerr << "Player " << current_player << " places mino " << move.mino_index << " at pos " << move.pos << "\n";
            board.put_mino(current_player, move);
            consecutive_passes = 0;
        }
        
        current_player = (current_player + 1) % N_PLAYERS;
    }

    board.print_scores();

    return 0;
}
