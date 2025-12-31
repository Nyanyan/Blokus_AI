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

const std::bitset<BOARD_BIT_SIZE> BOARD_MASK(
    "0000000000000000000000"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0111111111111111111110"
    "0000000000000000000000"
);

const std::bitset<BOARD_BIT_SIZE> WALL_MASK(
    "1111111111111111111111"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1000000000000000000001"
    "1111111111111111111111"
);

struct Mino {
    std::bitset<BOARD_BIT_SIZE> mino[N_MINO_CELL_TYPE];
    int size;
    std::vector<int> families;
    bool usable = true;

    Mino() = default;
    
    Mino(const std::bitset<BOARD_BIT_SIZE> (&data)[N_MINO_CELL_TYPE]) {
        for (int i = 0; i < N_MINO_CELL_TYPE; ++i) {
            mino[i] = data[i];
        }
    }

    void compute_size() {
        size = mino[FIL_IDX].count();
    }

    // 左シフト演算子（列を左に移動）
    Mino operator<<(int shift) const {
        Mino result;
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            result.mino[cell_type] = mino[cell_type] << shift;
        }
        result.size = size;
        result.families = families;
        result.usable = usable;
        return result;
    }

    // 右シフト演算子（列を右に移動）
    Mino operator>>(int shift) const {
        Mino result;
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            result.mino[cell_type] = mino[cell_type] >> shift;
        }
        result.size = size;
        result.families = families;
        result.usable = usable;
        return result;
    }

    bool shiftable_left(int shift) const {
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            if (((mino[cell_type] << shift) & BOARD_MASK).count() != mino[cell_type].count()) {
                return false;
            } 
        }
        return true;
    }

    bool shiftable_right(int shift) const {
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            if (((mino[cell_type] >> shift) & BOARD_MASK).count() != mino[cell_type].count()) {
                return false;
            } 
        }
        return true;
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
    {M1},
    {M2},
    {M3V}, {M3I},
    {M4I}, {M4L}, {M4N}, {M4P}, {M4T},
    {M5F}, {M5I}, {M5L}, {M5N}, {M5P}, {M5T},
    {M5U}, {M5V}, {M5W}, {M5X}, {M5Y}, {M5Z}
};

std::vector<Mino> all_minos;


// 指定した行のビット列を取得
std::bitset<BOARD_WITH_WALL_SIZE> get_row_bits(const std::bitset<BOARD_BIT_SIZE>& bitset, int row) {
    std::bitset<BOARD_WITH_WALL_SIZE> row_bits;
    int start_pos = row * BOARD_WITH_WALL_SIZE;
    
    for (int j = 0; j < BOARD_WITH_WALL_SIZE; ++j) {
        row_bits[j] = bitset[start_pos + j];
    }
    
    return row_bits;
}

// 指定した行にビット列を設定
void set_row_bits(std::bitset<BOARD_BIT_SIZE>& bitset, int row, const std::bitset<BOARD_WITH_WALL_SIZE>& row_bits) {
    int start_pos = row * BOARD_WITH_WALL_SIZE;
    
    for (int j = 0; j < BOARD_WITH_WALL_SIZE; ++j) {
        bitset[start_pos + j] = row_bits[j];
    }
}

// ミノを左上に詰める
Mino normalize_position(const Mino& mino) {
    Mino normalized = mino;
    
    // 全セルタイプを統合して最初の非空行を見つける
    int first_row = -1;
    for (int i = 0; i < BOARD_WITH_WALL_SIZE; ++i) {
        bool has_bit = false;
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            auto row_bits = get_row_bits(normalized.mino[cell_type], i);
            if (!row_bits.none()) {
                has_bit = true;
                break;
            }
        }
        if (has_bit) {
            first_row = i;
            break;
        }
    }
    
    // 行を上に詰める
    if (first_row > 0) {
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            normalized.mino[cell_type] >>= (first_row * BOARD_WITH_WALL_SIZE);
        }
    }
    
    // 全セルタイプを統合して最初の非0列を見つける
    int min_col = BOARD_WITH_WALL_SIZE;
    for (int i = 0; i < BOARD_WITH_WALL_SIZE; ++i) {
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            auto row_bits = get_row_bits(normalized.mino[cell_type], i);
            if (!row_bits.none()) {
                for (int j = 0; j < BOARD_WITH_WALL_SIZE; ++j) {
                    if (row_bits[j]) {
                        min_col = std::min(min_col, j);
                        break;
                    }
                }
            }
        }
    }
    
    // 列を左に詰める
    if (min_col > 0 && min_col < BOARD_WITH_WALL_SIZE) {
        for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
            for (int i = 0; i < BOARD_WITH_WALL_SIZE; ++i) {
                auto row_bits = get_row_bits(normalized.mino[cell_type], i);
                row_bits >>= min_col;
                set_row_bits(normalized.mino[cell_type], i, row_bits);
            }
        }
    }
    
    return normalized;
}


void print_mino(const Mino& mino) {
    for (int i = 0; i < BOARD_WITH_WALL_SIZE; ++i) {
        auto fil_row = get_row_bits(mino.mino[FIL_IDX], i);
        auto cnr_row = get_row_bits(mino.mino[CNR_IDX], i);
        auto edg_row = get_row_bits(mino.mino[EDG_IDX], i);
        
        // // この行にビットが1つでも立っているかチェック
        // if (fil_row.none() && cnr_row.none() && edg_row.none()) {
        //     continue;
        // }
        
        for (int j = 0; j < BOARD_WITH_WALL_SIZE; ++j) {
            if (fil_row[j]) {
                std::cout << "#";
            } else if (cnr_row[j]) {
                std::cout << ".";
            } else if (edg_row[j]) {
                std::cout << "-";
            } else {
                std::cout << "$";
            }
        }
        std::cout << '\n';
    }
}

// 90度時計回りに回転
Mino rotate90(const Mino& mino) {
    Mino rotated;
    
    for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
        rotated.mino[cell_type].reset();
        
        for (int i = 0; i < BOARD_WITH_WALL_SIZE; ++i) {
            for (int j = 0; j < BOARD_WITH_WALL_SIZE; ++j) {
                int src_pos = i * BOARD_WITH_WALL_SIZE + j;
                int dst_pos = j * BOARD_WITH_WALL_SIZE + (BOARD_WITH_WALL_SIZE - 1 - i);
                
                if (mino.mino[cell_type][src_pos]) {
                    rotated.mino[cell_type][dst_pos] = 1;
                }
            }
        }
    }
    
    return normalize_position(rotated);
}

// 左右反転
Mino flip_horizontal(const Mino& mino) {
    Mino flipped;
    
    for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
        flipped.mino[cell_type].reset();
        
        for (int i = 0; i < BOARD_WITH_WALL_SIZE; ++i) {
            for (int j = 0; j < BOARD_WITH_WALL_SIZE; ++j) {
                int src_pos = i * BOARD_WITH_WALL_SIZE + j;
                int dst_pos = i * BOARD_WITH_WALL_SIZE + (BOARD_WITH_WALL_SIZE - 1 - j);
                
                if (mino.mino[cell_type][src_pos]) {
                    flipped.mino[cell_type][dst_pos] = 1;
                }
            }
        }
    }
    
    return normalize_position(flipped);
}

// 2つのミノが同一かどうかを判定
bool is_same_mino(const Mino& m1, const Mino& m2) {
    for (int cell_type = 0; cell_type < N_MINO_CELL_TYPE; ++cell_type) {
        if (m1.mino[cell_type] != m2.mino[cell_type]) {
            return false;
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

