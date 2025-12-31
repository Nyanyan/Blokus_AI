#include "board.hpp"




struct Node {
    Board board;
    int start_player_id;
    double value;

    Node(const Board& b, int pid) : board(b), start_player_id(pid) {}
};



int main() {
    init_unique_minos();
    init_all_minos();

    int ai_player_id = -1;
    int start_player_id = 0;

    Board board;
    std::vector<Node> nodes;
    nodes.emplace_back(board, start_player_id);

    int current_player = start_player_id;
    int consecutive_passes = 0;
    while (consecutive_passes < N_PLAYERS) {
        board.print_board();
        
        if (current_player == ai_player_id) {
            std::cout << "AI's turn (Player " << current_player << ")\n";
        } else {
            // ランダムな手を取得
            Move move = board.get_random_move(current_player);
            
            if (move.mino_index == MINO_IDX_PASS) {
                // パス
                board.history[current_player].push_back(move);
                std::cerr << "Player " << current_player << " passes.\n";
                consecutive_passes++;
            } else {
                // 手を実行
                std::cerr << "Player " << current_player << " places mino " << move.mino_index << " at (" << move.top << ", " << move.left << ")\n";
                board.put_mino(current_player, move);
                consecutive_passes = 0;
            }
            std::cout << "Random player's turn (Player " << current_player << ")\n";
        }
        
        current_player = (current_player + 1) % N_PLAYERS;
    }

    board.print_scores();

    return 0;
}
