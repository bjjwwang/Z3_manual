//
// Created by Jiawei Wang on 1/14/22.
//
#include <z3++.h>
#include <iostream>
#include <unordered_map>

/*
int arr[2] = {0,1};
int *p = arr + 1;
*p = 5;
assert(arr[1] == 5);
assert(arr[0] == 0);

 * */
void print( z3::expr& expr) {
    std::cout  <<  expr.simplify()  << std::endl;
}

int main() {
    z3::context ctx;
    z3::solver solver(ctx);
    z3::expr_vector z3_arr(ctx);

    z3::sort StringSort = ctx.string_sort();
    z3::sort StrArraySort = ctx.array_sort(StringSort, StringSort);

    z3::expr map = ctx.constant("map", ctx.array_sort(ctx.string_sort(), ctx.string_sort()));
    z3::expr arr = ctx.constant("arr", ctx.array_sort(ctx.int_sort(), ctx.string_sort()));
    // int arr[2] = {0,1};
    map = z3::store(map, ctx.string_val("arr[0]"), ctx.string_val("0"));
    map = z3::store(map, ctx.string_val("arr[1]"), ctx.string_val( "1"));
    arr = z3::store(arr, 0, ctx.string_val("arr[0]"));
    arr = z3::store(arr, 1, ctx.string_val("arr[1]"));

    // int *p = arr + 1;
    map = z3::store(map, ctx.string_val("p"), z3::select(arr, 1));

    // *p = 5;
    auto m_p = z3::select(map, ctx.string_val("p"));
    auto mm_p = z3::select(map, m_p);
    //print(m_p);
    //print(mm_p);
    map = z3::store(map, m_p, ctx.string_val("5"));

    //assert(arr[1] == 5);
    solver.add(z3::select(map, z3::select(arr, 1)) == ctx.string_val("5"));
    std::cout  << solver.check() << std::endl;
    //assert(arr[0] == 0);
    solver.add(z3::select(map, z3::select(arr, 0)) == ctx.string_val("1"));
    std::cout  << solver.check() << std::endl;
}

