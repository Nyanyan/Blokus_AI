#include <iostream>
#include <vector>
#include <bitset>

constexpr int BOARD_SIZE = 20; // board size
constexpr int BOARD_WITH_WALL_SIZE = BOARD_SIZE + 2;
constexpr int BOARD_BIT_SIZE = BOARD_WITH_WALL_SIZE * BOARD_WITH_WALL_SIZE;

constexpr int N_MINO_CELL_TYPE = 3; // セルタイプ数
constexpr int FIL_IDX = 0; // filled
constexpr int CNR_IDX = 1; // corner
constexpr int EDG_IDX = 2; // edge

struct Mino {
    std::bitset<BOARD_BIT_SIZE> mino[N_MINO_CELL_TYPE];
    int size;
    std::vector<int> families;
    bool usable = true;

    void compute_size() {
        size = mino[FIL_IDX].count();
    }
};


const std::bitset<BOARD_BIT_SIZE> M1[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000010"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000101"
        "0000000000000000000000"
        "0000000000000000000101"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000010"
        "0000000000000000000101"
        "0000000000000000000010"
    )
};

const std::bitset<BOARD_BIT_SIZE> M2[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001001"
        "0000000000000000000000"
        "0000000000000000001001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000110"
        "0000000000000000001001"
        "0000000000000000000110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M3V[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000010"
        "0000000000000000000110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000101"
        "0000000000000000001000"
        "0000000000000000000000"
        "0000000000000000001001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000010"
        "0000000000000000000101"
        "0000000000000000001001"
        "0000000000000000000110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M3I[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000010001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001110"
        "0000000000000000010001"
        "0000000000000000001110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M4I[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000011110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000100001"
        "0000000000000000000000"
        "0000000000000000100001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000011110"
        "0000000000000000100001"
        "0000000000000000011110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M4L[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001000"
        "0000000000000000001110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010100"
        "0000000000000000000001"
        "0000000000000000000000"
        "0000000000000000010001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001000"
        "0000000000000000010110"
        "0000000000000000010001"
        "0000000000000000001110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M4N[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001100"
        "0000000000000000000110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010010"
        "0000000000000000000001"
        "0000000000000000010000"
        "0000000000000000001001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001100"
        "0000000000000000010010"
        "0000000000000000001001"
        "0000000000000000000110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M4P[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000110"
        "0000000000000000000110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001001"
        "0000000000000000000000"
        "0000000000000000000000"
        "0000000000000000001001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000110"
        "0000000000000000001001"
        "0000000000000000001001"
        "0000000000000000000110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M4T[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001110"
        "0000000000000000000100"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000010001"
        "0000000000000000001010"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001110"
        "0000000000000000010001"
        "0000000000000000001010"
        "0000000000000000000100"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5F[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000110"
        "0000000000000000001100"
        "0000000000000000000100"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001001"
        "0000000000000000010000"
        "0000000000000000000001"
        "0000000000000000010000"
        "0000000000000000001010"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000110"
        "0000000000000000001001"
        "0000000000000000010010"
        "0000000000000000001010"
        "0000000000000000000100"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5I[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000111110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000001000001"
        "0000000000000000000000"
        "0000000000000001000001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000111110"
        "0000000000000001000001"
        "0000000000000000111110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5L[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000010000"
        "0000000000000000011110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000101000"
        "0000000000000000000001"
        "0000000000000000000000"
        "0000000000000000100001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010000"
        "0000000000000000101110"
        "0000000000000000100001"
        "0000000000000000011110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5N[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000110"
        "0000000000000000011100"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001001"
        "0000000000000000100000"
        "0000000000000000000001"
        "0000000000000000100010"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000110"
        "0000000000000000011001"
        "0000000000000000100010"
        "0000000000000000011100"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5P[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001110"
        "0000000000000000000110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000010000"
        "0000000000000000001001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001110"
        "0000000000000000010001"
        "0000000000000000001001"
        "0000000000000000000110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5T[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001110"
        "0000000000000000000100"
        "0000000000000000000100"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000001010"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001110"
        "0000000000000000010001"
        "0000000000000000001010"
        "0000000000000000001010"
        "0000000000000000000100"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5U[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001010"
        "0000000000000000001110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010101"
        "0000000000000000000000"
        "0000000000000000000000"
        "0000000000000000010001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001010"
        "0000000000000000010101"
        "0000000000000000010001"
        "0000000000000000001110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5V[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000010"
        "0000000000000000000010"
        "0000000000000000001110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000101"
        "0000000000000000000000"
        "0000000000000000010000"
        "0000000000000000000000"
        "0000000000000000010001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000010"
        "0000000000000000000101"
        "0000000000000000001101"
        "0000000000000000010001"
        "0000000000000000001110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5W[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000010"
        "0000000000000000000110"
        "0000000000000000001100"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000101"
        "0000000000000000001000"
        "0000000000000000010000"
        "0000000000000000000001"
        "0000000000000000010010"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000010"
        "0000000000000000000101"
        "0000000000000000001001"
        "0000000000000000010010"
        "0000000000000000001100"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5X[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000000100"
        "0000000000000000001110"
        "0000000000000000000100"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001010"
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000010001"
        "0000000000000000001010"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000100"
        "0000000000000000001010"
        "0000000000000000010001"
        "0000000000000000001010"
        "0000000000000000000100"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5Y[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001000"
        "0000000000000000011110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010100"
        "0000000000000000100001"
        "0000000000000000000000"
        "0000000000000000100001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001000"
        "0000000000000000010110"
        "0000000000000000100001"
        "0000000000000000011110"
    )
};

const std::bitset<BOARD_BIT_SIZE> M5Z[N_MINO_CELL_TYPE] = {
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000000000"
        "0000000000000000001100"
        "0000000000000000000100"
        "0000000000000000000110"
        "0000000000000000000000"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000010010"
        "0000000000000000000000"
        "0000000000000000010001"
        "0000000000000000000000"
        "0000000000000000001001"
    ),
    std::bitset<BOARD_BIT_SIZE>(
        "0000000000000000001100"
        "0000000000000000010010"
        "0000000000000000001010"
        "0000000000000000001001"
        "0000000000000000000110"
    )
};



std::vector<Mino> unique_minos = {
    {M1, M1.size(), M1[0].size()},
    {M2, M2.size(), M2[0].size()},
    {M3V, M3V.size(), M3V[0].size()}, {M3I, M3I.size(), M3I[0].size()},
    {M4I, M4I.size(), M4I[0].size()}, {M4L, M4L.size(), M4L[0].size()}, {M4N, M4N.size(), M4N[0].size()}, {M4P, M4P.size(), M4P[0].size()}, {M4T, M4T.size(), M4T[0].size()},
    {M5F, M5F.size(), M5F[0].size()}, {M5I, M5I.size(), M5I[0].size()}, {M5L, M5L.size(), M5L[0].size()}, {M5N, M5N.size(), M5N[0].size()}, {M5P, M5P.size(), M5P[0].size()}, {M5T, M5T.size(), M5T[0].size()},
    {M5U, M5U.size(), M5U[0].size()}, {M5V, M5V.size(), M5V[0].size()}, {M5W, M5W.size(), M5W[0].size()}, {M5X, M5X.size(), M5X[0].size()}, {M5Y, M5Y.size(), M5Y[0].size()}, {M5Z, M5Z.size(), M5Z[0].size()}
};

std::vector<Mino> all_minos;



void print_mino(const Mino& mino) {
    for (const auto& row : mino.mino) {
        for (const auto& cell : row) {
            if (cell == DNC) {
                std::cout << " ";
            } else if (cell == FIL) {
                std::cout << "#";
            } else if (cell == CNR) {
                std::cout << ".";
            } else if (cell == EDG) {
                std::cout << "-";
            } else {
                std::cout << "?";
            }
        }
        std::cout << '\n';
    }
}

// 90度時計回りに回転
Mino rotate90(const Mino& mino) {
    size_t new_h = mino.w;
    size_t new_w = mino.h;
    std::vector<std::vector<int>> rotated(new_h, std::vector<int>(new_w));
    
    for (size_t i = 0; i < mino.h; ++i) {
        for (size_t j = 0; j < mino.w; ++j) {
            rotated[j][mino.h - 1 - i] = mino.mino[i][j];
        }
    }
    
    return {rotated, new_h, new_w};
}

// 左右反転
Mino flip_horizontal(const Mino& mino) {
    std::vector<std::vector<int>> flipped = mino.mino;
    
    for (size_t i = 0; i < mino.h; ++i) {
        for (size_t j = 0; j < mino.w / 2; ++j) {
            std::swap(flipped[i][j], flipped[i][mino.w - 1 - j]);
        }
    }
    
    return {flipped, mino.h, mino.w};
}

// 2つのミノが同一かどうかを判定
bool is_same_mino(const Mino& m1, const Mino& m2) {
    if (m1.h != m2.h || m1.w != m2.w) {
        return false;
    }
    
    for (size_t i = 0; i < m1.h; ++i) {
        for (size_t j = 0; j < m1.w; ++j) {
            if (m1.mino[i][j] != m2.mino[i][j]) {
                return false;
            }
        }
    }
    
    return true;
}

std::vector<Mino> get_all_transposed_minos(const Mino &mino) {
    std::vector<Mino> transposed_minos;
    // 90度ずつ回転したミノ4つ、左右反転させた上で90度ずつ回転したミノ4つを生成し、同一のものは除外して返す
    
    std::vector<Mino> candidates;
    
    // 元のミノを0度、90度、180度、270度回転
    Mino current = mino;
    for (int i = 0; i < 4; ++i) {
        candidates.push_back(current);
        current = rotate90(current);
    }
    
    // 左右反転したミノを0度、90度、180度、270度回転
    current = flip_horizontal(mino);
    for (int i = 0; i < 4; ++i) {
        candidates.push_back(current);
        current = rotate90(current);
    }
    
    // 重複を除外
    for (const auto& candidate : candidates) {
        bool is_duplicate = false;
        for (const auto& existing : transposed_minos) {
            if (is_same_mino(candidate, existing)) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            transposed_minos.push_back(candidate);
        }
    }
    
    return transposed_minos;
}



void generate_all_minos() {
    for (const auto& mino : unique_minos) {
        auto transposed = get_all_transposed_minos(mino);
        
        // この family の開始インデックス
        size_t family_start = all_minos.size();
        
        // family 内の全てのインデックスを記録
        std::vector<int> family_indices;
        for (size_t i = 0; i < transposed.size(); ++i) {
            family_indices.push_back(family_start + i);
        }
        
        // 各ミノに family インデックスを設定して追加
        for (auto& m : transposed) {
            m.families = family_indices;
            all_minos.push_back(m);
        }
    }
}

void print_all_minos() {
    for (Mino& mino : all_minos) {
        print_mino(mino);
        std::cout << "Families: ";
        for (const auto& fam : mino.families) {
            std::cout << fam << " ";
        }
        std::cout << "\n\n";
    }
    std::cout << "Total unique minos including transpositions: " << all_minos.size() << "\n";
}


void print_all_unique_minos() {
    for (const auto& mino : unique_minos) {
        print_mino(mino);
        std::cout << "\n";
    }
}


void init_unique_minos() {
    for (auto& mino : unique_minos) {
        mino.compute_size();
    }
}

void init_all_minos() {
    generate_all_minos();
    for (auto& mino : all_minos) {
        mino.compute_size();
    }
}

