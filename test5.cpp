//
// Created by Jiawei Wang on 1/14/22.
//
#include <z3++.h>
#include <iostream>
#include <unordered_map>

/*
 struct {
    int fld0;
    int fld1;
 } typename A;

 int main() {
    A a;    // alloc
    a.fld0 = 0;  // store (gep a, 0) 0
    a.fld1 = 1;  // store (gep a, 4) 1
    int *p = &a.fld1;  //  store p (gep a, 4)
    *p = 3;
    assert(a.fld1 == 3);
 }

 * */

void print(z3::expr& expr) {
    std::cout  <<  expr.simplify()  << std::endl;
}

int main() {
    z3::context ctx;
    z3::solver solver(ctx);
    z3::expr_vector z3_arr(ctx);

    z3::sort StringSort = ctx.string_sort();
    z3::sort ArraySort = ctx.array_sort(StringSort, StringSort);





}

