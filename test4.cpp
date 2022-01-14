//
// Created by Jiawei Wang on 1/14/22.
//
#include <z3++.h>
#include <iostream>
#include <unordered_map>
//  int a = 1
// int *p  = &a
// *p = 3
// int  b = a
// assert(a  == 3)

void print(z3::expr& expr) {
    std::cout  <<  expr.simplify()  << std::endl;
}

int main() {
    //std::unordered_map<std::string, std::string> heapObj;
    //std::unordered_map<std::string, int> stackObj;
    z3::context ctx;
    z3::solver solver(ctx);
    z3::expr_vector z3_arr(ctx);

    z3::sort StringSort = ctx.string_sort();
    z3::sort ArraySort = ctx.array_sort(StringSort, StringSort);
    int idx;
    //  int a = 1
    z3::expr map = ctx.constant("map", ArraySort);
    map = z3::store(map, ctx.string_val("a"), ctx.string_val("1"));

    // int *p  = &a;
    map = z3::store(map, ctx.string_val("p"), ctx.string_val("a"));

    //  *p  = 3;   M(M(p)):=3
    auto p =  z3::select(map, ctx.string_val("p"));
    map = z3::store(map, p, ctx.string_val("3"));
    // assert(a == 3);
    solver.add(z3::select(map, ctx.string_val("a")) == ctx.string_val("3"));
    std::cout << solver.check() << std::endl;
    return 0;
}