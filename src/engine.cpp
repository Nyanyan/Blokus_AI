#include <iostream>
#include <vector>

constexpr int DNC = 0; // do not care
constexpr int FIL = 1; // filled
constexpr int CNR = 2; // corner
constexpr int EDG = 3; // edge

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


const std::vector<std::vector<std::vector<int>>> unique_minos = {
    M1, 
    M2, 
    M3V, M3I, 
    M4I, M4L, M4N, M4P, M4T,
    M5F, M5I, M5L, M5N, M5P, M5T, M5U, M5V, M5W, M5X, M5Y, M5Z
};



void print_mino(const std::vector<std::vector<int>>& mino) {
    for (const auto& row : mino) {
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
