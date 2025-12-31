#include <iostream>
#include <vector>

constexpr int DNC = 0; // do not care
constexpr int FIL = 1; // filled
constexpr int CNR = 2; // corner
constexpr int EDG = 3; // edge


struct Mino {
    std::vector<std::vector<int>> mino;
    size_t h;
    size_t w;
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
    {M1, M1.size(), M1[0].size()},
    {M2, M2.size(), M2[0].size()},
    {M3V, M3V.size(), M3V[0].size()}, {M3I, M3I.size(), M3I[0].size()},
    {M4I, M4I.size(), M4I[0].size()}, {M4L, M4L.size(), M4L[0].size()}, {M4N, M4N.size(), M4N[0].size()}, {M4P, M4P.size(), M4P[0].size()}, {M4T, M4T.size(), M4T[0].size()},
    {M5F, M5F.size(), M5F[0].size()}, {M5I, M5I.size(), M5I[0].size()}, {M5L, M5L.size(), M5L[0].size()}, {M5N, M5N.size(), M5N[0].size()}, {M5P, M5P.size(), M5P[0].size()}, {M5T, M5T.size(), M5T[0].size()},
    {M5U, M5U.size(), M5U[0].size()}, {M5V, M5V.size(), M5V[0].size()}, {M5W, M5W.size(), M5W[0].size()}, {M5X, M5X.size(), M5X[0].size()}, {M5Y, M5Y.size(), M5Y[0].size()}, {M5Z, M5Z.size(), M5Z[0].size()}
};



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




int main() {
    for (const auto& mino : unique_minos) {
        print_mino(mino);
        std::cout << "\n";
    }
    return 0;
}
