# include <Siv3D.hpp> // Siv3D v0.6.15
#include "engine.hpp"

// プレイヤーの色を定義
const Color PlayerColors[N_PLAYERS] = {
    Color(220, 50, 50),   // プレイヤー0: 赤
    Color(250, 220, 50),  // プレイヤー1: 黄
    Color(80, 200, 80),   // プレイヤー2: 緑
    Color(50, 100, 220)   // プレイヤー3: 青
};

// ミノをグリッドに描画する関数
void DrawMinoOnGrid(const Mino& mino, int pos, const Color& color, double gridX, double gridY, double cellSize, double alpha = 1.0) {
    auto shifted_mino = mino << pos;
    for (int bit_pos = 0; bit_pos < BOARD_BIT_SIZE; ++bit_pos) {
        if (shifted_mino.mino[FIL_IDX][bit_pos]) {
            int row = bit_pos / BOARD_WITH_WALL_SIZE;
            int col = bit_pos % BOARD_WITH_WALL_SIZE;
            if (row >= 1 && row <= BOARD_SIZE && col >= 1 && col <= BOARD_SIZE) {
                RectF cell(gridX + (col - 1) * cellSize, gridY + (row - 1) * cellSize, cellSize, cellSize);
                cell.draw(ColorF(color, alpha));
                cell.drawFrame(1, 0, ColorF(0, 0, 0, alpha * 0.5));
            }
        }
    }
}

// ミノの中心位置（FIL_IDXの重心）を計算する関数
Point GetMinoCenter(const Mino& mino) {
    int sumRow = 0, sumCol = 0, count = 0;
    for (int bit_pos = 0; bit_pos < BOARD_BIT_SIZE; ++bit_pos) {
        if (mino.mino[FIL_IDX][bit_pos]) {
            int row = bit_pos / BOARD_WITH_WALL_SIZE;
            int col = bit_pos % BOARD_WITH_WALL_SIZE;
            sumRow += row;
            sumCol += col;
            count++;
        }
    }
    if (count == 0) return Point(0, 0);
    return Point(sumCol / count, sumRow / count);
}

// ミノを小さく描画する関数（残りミノ表示用）
void DrawMinoSmall(const Mino& mino, const Vec2& pos, double cellSize, const Color& color) {
    // ミノの範囲を計算
    int minRow = BOARD_SIZE + 1, maxRow = 0, minCol = BOARD_SIZE + 1, maxCol = 0;
    for (int bit_pos = 0; bit_pos < BOARD_BIT_SIZE; ++bit_pos) {
        if (mino.mino[FIL_IDX][bit_pos]) {
            int row = bit_pos / BOARD_WITH_WALL_SIZE;
            int col = bit_pos % BOARD_WITH_WALL_SIZE;
            minRow = std::min(minRow, row);
            maxRow = std::max(maxRow, row);
            minCol = std::min(minCol, col);
            maxCol = std::max(maxCol, col);
        }
    }
    
    // ミノを描画
    for (int bit_pos = 0; bit_pos < BOARD_BIT_SIZE; ++bit_pos) {
        if (mino.mino[FIL_IDX][bit_pos]) {
            int row = bit_pos / BOARD_WITH_WALL_SIZE;
            int col = bit_pos % BOARD_WITH_WALL_SIZE;
            RectF cell(pos.x + (col - minCol) * cellSize, pos.y + (row - minRow) * cellSize, cellSize, cellSize);
            cell.draw(color);
            cell.drawFrame(1, 0, ColorF(0, 0, 0, 0.5));
        }
    }
}

void Main() {
	Console.open();
    init_unique_minos();
    init_all_minos();

    // ウィンドウサイズを設定
    Window::Resize(1600, 900);
    Scene::SetBackground(ColorF(0.95, 0.95, 0.95));

    // フォント
    Font font(24, Typeface::Bold);
    Font smallFont(18);

    // ゲーム状態
    Board board;
    int current_player = 0;
    bool is_ai[N_PLAYERS] = { false, true, true, true }; // プレイヤー0は人間、他はAI
    bool game_over = false;
    int consecutive_passes = 0;

    // UI状態
    int selected_mino_index = -1;
    int selected_unique_mino_idx = -1;
    int rotation = 0;
    
    // グリッド設定
    const double cellSize = 30.0;
    const double gridX = 400 - (BOARD_SIZE * cellSize) / 2;
    const double gridY = 450 - (BOARD_SIZE * cellSize) / 2;

    // AI思考中フラグ
    bool ai_thinking = false;
    double ai_think_timer = 0.0;
    Move ai_move = {-1, -1, 0.0, 0};

    while (System::Update()) {
        // ゲーム終了チェック
        if (consecutive_passes >= N_PLAYERS && !game_over) {
            game_over = true;
        }

        // AIの手番処理
        if (!game_over && is_ai[current_player] && !ai_thinking) {
            ai_thinking = true;
            ai_think_timer = 0.0;
        }

        if (ai_thinking) {
            ai_think_timer += Scene::DeltaTime();
            if (ai_think_timer > 0.5) { // 0.5秒待ってからAIが手を打つ
                ai_move = get_best_move(board, current_player);
                if (ai_move.mino_index == MINO_IDX_PASS) {
                    board.history[current_player].push_back(ai_move);
                    consecutive_passes++;
                } else {
                    board.put_mino(current_player, ai_move);
                    consecutive_passes = 0;
                }
                current_player = (current_player + 1) % N_PLAYERS;
                ai_thinking = false;
            }
        }

        // ======== 描画 ========

        // 手番表示
        String turnText = U"プレイヤー {} の手番"_fmt(current_player);
        if (game_over) {
            turnText = U"ゲーム終了";
        } else if (is_ai[current_player]) {
            turnText += U" (AI)";
        }
        font(turnText).draw(50, 50, PlayerColors[current_player]);
        
        // パスボタン（プレイヤー表示の右側）
        if (!game_over && !is_ai[current_player] && !ai_thinking) {
            if (SimpleGUI::Button(U"パス", Vec2(400, 45), 100)) {
                Move pass_move = {-1, -1, MINO_IDX_PASS};
                board.history[current_player].push_back(pass_move);
                consecutive_passes++;
                current_player = (current_player + 1) % N_PLAYERS;
                selected_mino_index = -1;
                selected_unique_mino_idx = -1;
            }
        }

        // グリッドの枠を描画
        RectF(gridX - 2, gridY - 2, BOARD_SIZE * cellSize + 4, BOARD_SIZE * cellSize + 4).drawFrame(2, 0, Color(50, 50, 50));

        // グリッドを描画
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                RectF cell(gridX + j * cellSize, gridY + i * cellSize, cellSize, cellSize);
                cell.draw(ColorF(1, 1, 1));
                cell.drawFrame(0.5, 0, ColorF(0.7, 0.7, 0.7));
            }
        }

        // 盤面の状態を描画
        for (int player_id = 0; player_id < N_PLAYERS; ++player_id) {
            for (int bit_pos = 0; bit_pos < BOARD_BIT_SIZE; ++bit_pos) {
                if (board.cells[player_id][bit_pos]) {
                    int row = bit_pos / BOARD_WITH_WALL_SIZE;
                    int col = bit_pos % BOARD_WITH_WALL_SIZE;
                    if (row >= 1 && row <= BOARD_SIZE && col >= 1 && col <= BOARD_SIZE) {
                        RectF cell(gridX + (col - 1) * cellSize, gridY + (row - 1) * cellSize, cellSize, cellSize);
                        cell.draw(PlayerColors[player_id]);
                        cell.drawFrame(1, 0, ColorF(0, 0, 0, 0.5));
                    }
                }
            }
        }

        // マウスホバー時のミノプレビュー（人間プレイヤーの手番のみ）
        if (!game_over && !is_ai[current_player] && selected_mino_index >= 0 && !ai_thinking) {
            Vec2 mousePos = Cursor::Pos();
            int gridCol = static_cast<int>((mousePos.x - gridX) / cellSize);
            int gridRow = static_cast<int>((mousePos.y - gridY) / cellSize);
            
            if (gridCol >= 0 && gridCol < BOARD_SIZE && gridRow >= 0 && gridRow < BOARD_SIZE) {
                const Mino& mino = board.players[current_player].minos[selected_mino_index];
                
                // ミノの中心を取得してオフセットを計算
                Point minoCenter = GetMinoCenter(mino);
                int centerOffsetCol = minoCenter.x - 1;  // 壁分を引く
                int centerOffsetRow = minoCenter.y - 1;
                
                // マウス位置がミノの中心になるように調整
                int targetCol = gridCol - centerOffsetCol;
                int targetRow = gridRow - centerOffsetRow;
                int bit_pos = (targetRow + 1) * BOARD_WITH_WALL_SIZE + (targetCol + 1);
                
                bool can_place = false;
                if (board.players[current_player].is_first_move) {
                    can_place = board.puttable_first(mino, bit_pos, current_player);
                } else {
                    can_place = board.puttable(mino, bit_pos, current_player);
                }
                
                Color previewColor = can_place ? PlayerColors[current_player] : Color(150, 150, 150);
                DrawMinoOnGrid(mino, bit_pos, previewColor, gridX, gridY, cellSize, 0.5);
            }
        }

        // 右側に各プレイヤーの情報を表示
        double infoX = gridX + BOARD_SIZE * cellSize + 50;
        double infoY = 100;
        
        for (int player_id = 0; player_id < N_PLAYERS; ++player_id) {
            // プレイヤー情報
            String playerText = U"プレイヤー {}"_fmt(player_id);
            if (is_ai[player_id]) {
                playerText += U" (AI)";
            }
            font(playerText).draw(infoX, infoY, PlayerColors[player_id]);
            
            // スコア
            int score = board.calculate_score(player_id);
            smallFont(U"スコア: {}"_fmt(score)).draw(infoX, infoY + 30, Color(50, 50, 50));
            
            // 残りミノを描画
            double minoX = infoX;
            double minoY = infoY + 60;
            
            // usableなミノをファミリーごとにカウント
            std::vector<int> unique_usable_minos;
            for (size_t i = 0; i < board.players[player_id].minos.size(); ++i) {
                if (board.players[player_id].minos[i].usable) {
                    // このミノのファミリーの最小インデックスを取得
                    int min_family_idx = board.players[player_id].minos[i].families[0];
                    for (int fam_idx : board.players[player_id].minos[i].families) {
                        if (fam_idx < min_family_idx) {
                            min_family_idx = fam_idx;
                        }
                    }
                    // 最小インデックスの場合のみ追加（重複を避ける）
                    if (static_cast<int>(i) == min_family_idx) {
                        unique_usable_minos.push_back(i);
                    }
                }
            }
            
            // ミノを描画（11個で改行、クリック可能）
            for (size_t idx = 0; idx < unique_usable_minos.size(); ++idx) {
                int mino_idx = unique_usable_minos[idx];
                double x = minoX + (idx % 11) * 28;
                double y = minoY + (idx / 11) * 28;
                
                // クリック可能な領域
                RectF minoArea(x - 2, y - 2, 26, 26);
                bool is_hovered = minoArea.mouseOver();
                bool is_current_player = (player_id == current_player && !is_ai[current_player] && !ai_thinking && !game_over);
                
                // ホバー時の背景
                if (is_current_player && is_hovered) {
                    minoArea.draw(ColorF(0.9, 0.9, 0.9, 0.5));
                }
                
                DrawMinoSmall(board.players[player_id].minos[mino_idx], Vec2(x, y), 4.5, PlayerColors[player_id]);
                
                // クリックで選択（現在のプレイヤーのみ）
                if (is_current_player && minoArea.leftClicked()) {
                    selected_mino_index = mino_idx;
                    selected_unique_mino_idx = static_cast<int>(idx);
                    rotation = 0;
                }
            }
            
            infoY += 140;
        }

        // 左側に現在のプレイヤーの残りミノを表示
        if (!game_over && !ai_thinking) {
            double minoListX = 50;
            double minoListY = 150;
            smallFont(U"残りのミノ (クリックで選択)").draw(minoListX, minoListY - 30, Color(50, 50, 50));
            
            int displayed_count = 0;
            for (size_t unique_idx = 0; unique_idx < unique_minos.size(); ++unique_idx) {
                // このunique_minoに対応する最初のusableなミノを探す
                int mino_idx = -1;
                for (size_t i = 0; i < board.players[current_player].minos.size(); ++i) {
                    if (board.players[current_player].minos[i].usable && 
                        board.players[current_player].minos[i].families == unique_minos[unique_idx].families) {
                        mino_idx = static_cast<int>(i);
                        break;
                    }
                }
                
                if (mino_idx >= 0) {
                    double x = minoListX + (displayed_count % 4) * 70;
                    double y = minoListY + (displayed_count / 4) * 70;
                    
                    RectF minoBox(x, y, 60, 60);
                    bool is_hovered = minoBox.mouseOver();
                    bool is_selected = (selected_unique_mino_idx == static_cast<int>(unique_idx));
                    
                    if (is_selected) {
                        minoBox.draw(ColorF(PlayerColors[current_player], 0.3));
                    } else if (is_hovered) {
                        minoBox.draw(ColorF(0.9, 0.9, 0.9));
                    } else {
                        minoBox.draw(ColorF(1, 1, 1));
                    }
                    minoBox.drawFrame(2, 0, is_selected ? PlayerColors[current_player] : Color(200, 200, 200));
                    
                    DrawMinoSmall(board.players[current_player].minos[mino_idx], Vec2(x + 5, y + 5), 8, PlayerColors[current_player]);
                    
                    if (!is_ai[current_player] && minoBox.leftClicked()) {
                        selected_mino_index = mino_idx;
                        selected_unique_mino_idx = static_cast<int>(unique_idx);
                        rotation = 0;
                    }
                    
                    displayed_count++;
                }
            }
            
            // 右クリックで回転
            if (!is_ai[current_player] && selected_mino_index >= 0 && MouseR.down()) {
                // 次の回転を探す
                int start_idx = selected_mino_index;
                const auto& families = board.players[current_player].minos[selected_mino_index].families;
                int next_idx = -1;
                for (size_t i = 0; i < families.size(); ++i) {
                    if (families[i] == selected_mino_index) {
                        next_idx = families[(i + 1) % families.size()];
                        break;
                    }
                }
                if (next_idx >= 0) {
                    selected_mino_index = next_idx;
                }
            }
            
            // マウス左クリックで配置
            if (!is_ai[current_player] && selected_mino_index >= 0 && MouseL.down()) {
                Vec2 mousePos = Cursor::Pos();
                int gridCol = static_cast<int>((mousePos.x - gridX) / cellSize);
                int gridRow = static_cast<int>((mousePos.y - gridY) / cellSize);
                
                if (gridCol >= 0 && gridCol < BOARD_SIZE && gridRow >= 0 && gridRow < BOARD_SIZE) {
                    int bit_pos = (gridRow + 1) * BOARD_WITH_WALL_SIZE + (gridCol + 1);
                    
                    const Mino& mino = board.players[current_player].minos[selected_mino_index];
                    bool can_place = false;
                    if (board.players[current_player].is_first_move) {
                        can_place = board.puttable_first(mino, bit_pos, current_player);
                    } else {
                        can_place = board.puttable(mino, bit_pos, current_player);
                    }
                    
                    if (can_place) {
                        Move move = {bit_pos, selected_mino_index, 0.0, 0};
                        board.put_mino(current_player, move);
                        consecutive_passes = 0;
                        current_player = (current_player + 1) % N_PLAYERS;
                        selected_mino_index = -1;
                        selected_unique_mino_idx = -1;
                    }
                }
            }
            
        }

        // ゲーム終了時の表示
        if (game_over) {
            // 最終スコアを計算して勝者を決定
            int best_score = board.calculate_score(0);
            int winner = 0;
            for (int i = 1; i < N_PLAYERS; ++i) {
                int score = board.calculate_score(i);
                if (score > best_score) {
                    best_score = score;
                    winner = i;
                }
            }
            
            String winnerText = U"勝者: プレイヤー {} (スコア: {})"_fmt(winner, best_score);
            font(winnerText).drawAt(800, 450, PlayerColors[winner]);
        }
    }
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
