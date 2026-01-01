#include "board.hpp"
#include <chrono>
#include <cmath>
#include <memory>

inline uint64_t tim() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

// 盤面の比較用ヘルパー関数
inline bool boards_equal(const Board& a, const Board& b) {
    // 各プレイヤーの石の配置を比較
    for (int i = 0; i < N_PLAYERS; ++i) {
        if (a.cells[i] != b.cells[i]) {
            return false;
        }
    }
    return true;
}

struct Node {
    Board board;
    int current_player_id;  // このノードで手番のプレイヤー
    int target_player_id;   // 評価対象のプレイヤー（MCTS開始時のプレイヤー）
    Move move;              // このノードに至る手
    
    Node* parent;
    std::vector<std::unique_ptr<Node>> children;
    
    int visit_count;
    double total_value;
    bool is_fully_expanded;
    std::vector<Move> untried_moves;
    
    Node(const Board& b, int current_pid, int target_pid, Node* p = nullptr, Move m = {-1, -1, MINO_IDX_PASS}) 
        : board(b), current_player_id(current_pid), target_player_id(target_pid), move(m), 
          parent(p), visit_count(0), total_value(0.0), is_fully_expanded(false) {
        // 未試行の手を生成
        Player& player = board.players[current_player_id];
        untried_moves = board.generate_legal_moves(current_player_id, player.is_first_move);
        if (untried_moves.empty()) {
            untried_moves.push_back({-1, -1, MINO_IDX_PASS});
        }
    }
    
    double ucb1(double exploration_param = 1.41) const {
        if (visit_count == 0) {
            return std::numeric_limits<double>::infinity();
        }
        double exploitation = total_value / visit_count;
        double exploration = exploration_param * std::sqrt(std::log(parent->visit_count) / visit_count);
        return exploitation + exploration;
    }
    
    bool is_terminal() {
        // 全プレイヤーがパスしたかチェック
        for (int i = 0; i < N_PLAYERS; ++i) {
            const Player& player = board.players[i];
            std::vector<Move> legal_moves = board.generate_legal_moves(i, player.is_first_move);
            if (!legal_moves.empty()) {
                return false;
            }
        }
        return true;
    }
};


Move get_best_move_mc(Board& board, int player_id) {
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
    return *best_move;
}

// グローバルなMCTS探索木のルート
std::unique_ptr<Node> global_mcts_root = nullptr;

Move get_best_move_mcts(Board& board, int player_id) {
    const int simulation_count = 500; // シミュレーション回数
    const double exploration_param = 1.41; // UCB1の探索パラメータ
    
    std::cerr << "Starting MCTS for Player " << player_id << " with " << simulation_count << " simulations...\n";
    uint64_t start_time = tim();
    
    // グローバルツリーから現在の盤面に対応するノードを探す
    std::unique_ptr<Node> root_ptr = nullptr;
    Node* root = nullptr;
    
    if (global_mcts_root != nullptr && boards_equal(global_mcts_root->board, board) && 
        global_mcts_root->current_player_id == player_id) {
        // 前回の探索結果を再利用
        std::cerr << "Reusing previous MCTS tree (visits: " << global_mcts_root->visit_count << ")\n";
        root_ptr = std::move(global_mcts_root);
        root = root_ptr.get();
        root->parent = nullptr; // 親ポインタをクリア
        root->target_player_id = player_id; // ターゲットプレイヤーを更新
    } else {
        // 新しいルートノードを作成
        std::cerr << "Creating new MCTS tree\n";
        root_ptr = std::make_unique<Node>(board, player_id, player_id);
        root = root_ptr.get();
    }
    
    // MCTSのメインループ
    for (int i = 0; i < simulation_count; ++i) {
        // 1. Selection: UCB1で葉ノードまで選択
        Node* node = root;
        while (!node->is_terminal() && node->untried_moves.empty() && !node->children.empty()) {
            // 最もUCB1値が高い子を選択
            Node* best_child = nullptr;
            double best_ucb = -std::numeric_limits<double>::infinity();
            for (auto& child : node->children) {
                double ucb = child->ucb1(exploration_param);
                if (ucb > best_ucb) {
                    best_ucb = ucb;
                    best_child = child.get();
                }
            }
            node = best_child;
        }
        
        // 2. Expansion: 未試行の手があれば子ノードを追加
        if (!node->untried_moves.empty() && !node->is_terminal()) {
            Move move = node->untried_moves.back();
            node->untried_moves.pop_back();
            
            Board new_board = node->board;
            if (move.mino_index != MINO_IDX_PASS) {
                new_board.put_mino(node->current_player_id, move);
            }
            int next_player = (node->current_player_id + 1) % N_PLAYERS;
            
            node->children.push_back(std::make_unique<Node>(new_board, next_player, player_id, node, move));
            node = node->children.back().get();
        }
        
        // 3. Simulation: ランダムプレイアウト
        Board sim_board = node->board;
        sim_board.random_playout(node->current_player_id);
        double score = sim_board.calculate_mcts_score(player_id);
        
        // 4. Backpropagation: 結果を親ノードへ伝播
        while (node != nullptr) {
            node->visit_count++;
            node->total_value += score;
            node = node->parent;
        }
        
        // 50トライごとに上位3手を表示
        if ((i + 1) % 50 == 0) {
            std::vector<std::pair<Node*, double>> child_stats;
            for (auto& child : root->children) {
                double avg_value = child->visit_count > 0 ? child->total_value / child->visit_count : 0.0;
                child_stats.push_back({child.get(), avg_value});
            }
            
            // 訪問回数でソート
            std::sort(child_stats.begin(), child_stats.end(), 
                [](const auto& a, const auto& b) { return a.first->visit_count > b.first->visit_count; });
            
            std::cerr << "After " << (i + 1) << " simulations - Top 3 moves:\n";
            for (int j = 0; j < std::min(3, static_cast<int>(child_stats.size())); ++j) {
                Node* child = child_stats[j].first;
                double avg_value = child_stats[j].second;
                std::cerr << "  #" << (j + 1) << ": pos=" << child->move.pos 
                          << " mino=" << child->move.mino_index 
                          << " visits=" << child->visit_count 
                          << " avg_value=" << avg_value << "\n";
            }
        }
    }
    
    // 最も訪問回数が多い子を選択
    Node* best_child = nullptr;
    int max_visits = -1;
    for (auto& child : root->children) {
        if (child->visit_count > max_visits) {
            max_visits = child->visit_count;
            best_child = child.get();
        }
    }
    
    uint64_t elapsed = tim() - start_time;
    
    if (best_child == nullptr) {
        std::cerr << "No valid moves found. Passing. Elapsed " << elapsed << " ms\n";
        global_mcts_root = nullptr; // ツリーをクリア
        return {-1, -1, MINO_IDX_PASS};
    }
    
    double avg_value = best_child->total_value / best_child->visit_count;
    std::cerr << "Best move: pos " << best_child->move.pos << " mino " << best_child->move.mino_index 
              << " (visits: " << best_child->visit_count << ", avg_value: " << avg_value << ") "
              << "Elapsed " << elapsed << " ms (" << (elapsed * 1000 / simulation_count) << " us/simulation)\n";
    
    Move result_move = best_child->move;
    
    // 選択した手の子ノードを次回の探索のために保存
    // best_childをrootのchildrenから取り出す
    std::unique_ptr<Node> next_root = nullptr;
    for (auto& child : root->children) {
        if (child.get() == best_child) {
            next_root = std::move(child);
            break;
        }
    }
    
    if (next_root) {
        next_root->parent = nullptr; // 親ポインタをクリア
        global_mcts_root = std::move(next_root);
        std::cerr << "Saved MCTS tree for next turn (visits: " << global_mcts_root->visit_count << ")\n";
    } else {
        global_mcts_root = nullptr;
    }
    
    return result_move;
}

Move get_best_move(Board& board, int player_id) {
    uint64_t strt_all = tim();
    // Move res = get_best_move_mc(board, player_id);  // Monte Carloを使用
    Move res = get_best_move_mcts(board, player_id);  // MCTSを使用
    std::cerr << "Best move chosen at pos " << res.pos << " with mino " << res.mino_index << " elapsed " << (tim() - strt_all) << " ms\n";
    return res;
}
