#include <iostream>
#include <vector>

constexpr int BOARD_SIZE = 20;

constexpr int DNC = 0; // do not care
constexpr int FIL = 1; // filled
constexpr int CNR = 2; // corner
constexpr int EDG = 3; // edge


struct Mino {
    std::vector<std::vector<int>> mino;
    size_t h;
    size_t w;
    std::vector<int> families;
    bool usable = true;
};

const std::vector<std::vector<int>> M1 = {
    {CNR, EDG, CNR},
    {EDG, FIL, EDG},
    {CNR, EDG, CNR}
};

const std::vector<std::vector<int>> M2 = {
    {CNR, EDG, EDG, CNR},
    {EDG, FIL, FIL, EDG},
    {CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M3V = {
    {DNC, CNR, EDG, CNR},
    {CNR, EDG, FIL, EDG},
    {EDG, FIL, FIL, EDG},
    {CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M3I = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4I = {
    {CNR, EDG, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4L = {
    {CNR, EDG, CNR, DNC, DNC},
    {EDG, FIL, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4N = {
    {CNR, EDG, EDG, CNR, DNC},
    {EDG, FIL, FIL, EDG, CNR},
    {CNR, EDG, FIL, FIL, EDG},
    {DNC, CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4P = {
    {CNR, EDG, EDG, CNR},
    {EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, EDG},
    {CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M4T = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, CNR, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5F = {
    {DNC, CNR, EDG, EDG, CNR},
    {CNR, EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, EDG, CNR},
    {CNR, EDG, FIL, EDG, DNC},
    {DNC, CNR, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5I = {
    {CNR, EDG, EDG, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5L = {
    {CNR, EDG, CNR, DNC, DNC, DNC},
    {EDG, FIL, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5N = {
    {DNC, DNC, CNR, EDG, EDG, CNR},
    {CNR, EDG, EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, FIL, EDG, CNR},
    {CNR, EDG, EDG, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5P = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, FIL, EDG},
    {DNC, CNR, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5T = {
    {CNR, EDG, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, EDG, FIL, EDG, DNC},
    {DNC, CNR, EDG, CNR, DNC}
};

const std::vector<std::vector<int>> M5U = {
    {CNR, EDG, CNR, EDG, CNR},
    {EDG, FIL, EDG, FIL, EDG},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5V = {
    {DNC, DNC, CNR, EDG, CNR},
    {DNC, DNC, EDG, FIL, EDG},
    {CNR, EDG, EDG, FIL, EDG},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5W = {
    {DNC, DNC, CNR, EDG, CNR},
    {DNC, CNR, EDG, FIL, EDG},
    {CNR, EDG, FIL, FIL, EDG},
    {EDG, FIL, FIL, EDG, CNR},
    {CNR, EDG, EDG, CNR, DNC}
};


const std::vector<std::vector<int>> M5X = {
    {DNC, CNR, EDG, CNR, DNC},
    {CNR, EDG, FIL, EDG, CNR},
    {EDG, FIL, FIL, FIL, EDG},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, CNR, EDG, CNR, DNC}
};


const std::vector<std::vector<int>> M5Y = {
    {DNC, CNR, EDG, CNR, DNC, DNC},
    {CNR, EDG, FIL, EDG, EDG, CNR},
    {EDG, FIL, FIL, FIL, FIL, EDG},
    {CNR, EDG, EDG, EDG, EDG, CNR}
};

const std::vector<std::vector<int>> M5Z = {
    {CNR, EDG, EDG, CNR, DNC},
    {EDG, FIL, FIL, EDG, DNC},
    {CNR, EDG, FIL, EDG, CNR},
    {DNC, EDG, FIL, FIL, EDG},
    {DNC, CNR, EDG, EDG, CNR}
};


const std::vector<Mino> unique_minos = {
    {M1, M1.size(), M1[0].size(), {}},
    {M2, M2.size(), M2[0].size(), {}},
    {M3V, M3V.size(), M3V[0].size(), {}}, {M3I, M3I.size(), M3I[0].size(), {}},
    {M4I, M4I.size(), M4I[0].size(), {}}, {M4L, M4L.size(), M4L[0].size(), {}}, {M4N, M4N.size(), M4N[0].size(), {}}, {M4P, M4P.size(), M4P[0].size(), {}}, {M4T, M4T.size(), M4T[0].size(), {}},
    {M5F, M5F.size(), M5F[0].size(), {}}, {M5I, M5I.size(), M5I[0].size(), {}}, {M5L, M5L.size(), M5L[0].size(), {}}, {M5N, M5N.size(), M5N[0].size(), {}}, {M5P, M5P.size(), M5P[0].size(), {}}, {M5T, M5T.size(), M5T[0].size(), {}},
    {M5U, M5U.size(), M5U[0].size(), {}}, {M5V, M5V.size(), M5V[0].size(), {}}, {M5W, M5W.size(), M5W[0].size(), {}}, {M5X, M5X.size(), M5X[0].size(), {}}, {M5Y, M5Y.size(), M5Y[0].size(), {}}, {M5Z, M5Z.size(), M5Z[0].size(), {}}
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



int main() {
    generate_all_minos();

    return 0;
}
