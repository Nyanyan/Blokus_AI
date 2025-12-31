#include "engine.hpp"

int main() {
    init_unique_minos();
    init_all_minos();

    int ai_player_id = 0;
    int start_player_id = 0;

    Board board;

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
