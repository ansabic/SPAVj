//
// Created by antonio on 08. 12. 2021..
//
#include "longnumber.h"

int main() {
    LongNumber numa = read_longnum("/home/antonio/CLionProjects/SPAVj/longnum/a.txt");
    print_longnum(numa);
    LongNumber numb = read_longnum("/home/antonio/CLionProjects/SPAVj/longnum/b.txt");
    print_longnum(numb);
    LongNumber numc = add_longnum(numa, numb);
    print_longnum(numc);
    LongNumber numd = mul_by_digit(numc, 9);
    print_longnum(numd);
    LongNumber nume = mul_by_pow10(numd, 3);
    print_longnum(nume);

    LongNumber numf = mul_longnum(numa, numb);
    print_longnum(numf);

    delete_longnum(numa);
    delete_longnum(numb);
    delete_longnum(numc);
    delete_longnum(numd);
    delete_longnum(nume);
    delete_longnum(numf);
}
