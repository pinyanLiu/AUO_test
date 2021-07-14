#include <iostream>

void display_coefAndBnds_rowNum(int coef_row_num, int coef_diff, int bnd_row_num, int bnd_diff) {

    std::cout << "\t";
    std::cout << "@:    ";
    std::cout << coef_row_num - coef_diff << " ~ " << coef_row_num - 1 << "\t ";
    std::cout << bnd_row_num - bnd_diff << " ~ " << bnd_row_num - 1 << std::endl;
}