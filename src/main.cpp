#include <iostream>
#include <ostream>

#include "matrix.h"

template<size_t N>
std::ostream& operator<<(std::ostream& out, std::array<size_t, N> const& ar)
{
    for (size_t i = 0; i < N; i++)
    {
        out << ar[i] << " ";
    }
    
    return out;
}

int main() {
    OTUS::Matrix<int, 0> matrix;
    const int n = 10;
    // fill the main diagonal
    for(int i = 0; i < n; i++) {
        matrix[i][i] = i;
    }

    // fill the secondary diagonal
    for(int i = n - 1; i >= 0; i--) {
        matrix[i][n - i - 1] = i;
    }
    std::cout << "Matrix:" << std::endl;
    for(int i = 1; i < n-1; i++) {
        for(int j = 1; j < n-1; j++) {
            if(j > 1) std::cout << " ";
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Size: " << matrix.size() << std::endl;

    std::cout << std::endl;
    std::cout << "Content:" << std::endl;
    for(auto elem: matrix)
    {
        auto [i, value] = elem;
        std::cout << "matrix[" << i << "] = " << value << std::endl;
    }

    // The following expression is valid:
    ((matrix[100][100] = 314) = 0) = 217;
    return 0;
}