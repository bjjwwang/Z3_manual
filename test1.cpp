//
// Created by Jiawei Wang on 1/14/22.
//
#include <z3++.h>
#include <iostream>
#include <unordered_map>
/*
 * int main() {
    int a = 0;
    a += 3.1;
    assert(a == 3);
    long b = 1000;
    b += a;
    assert(b == 1003);
    short c = 10000;
    c += b;
    assert(c == 11003);
    char d = '0';
    d += 5;
    assert(d == '5');
    float e = 2.718;
    e = e + 2.0;
    assert(e - 4.718 < 0.01);
    double f = 3.14;
    assert (f - 3.14 < 0.01);
    signed g = c + 5;
    assert(g == 11008);
    int h = sizeof(a) + 6;
    assert(h == 10);
    return 0;
 * */

int main() {
    z3::context ctx;
    z3::solver solver(ctx);
    z3::sort Int = ctx.int_sort();
    z3::sort Real = ctx.real_sort();
    //    int a = 0;
    a = ctx.int_const("a");
    solver.add(a == ctx.int_val(0));
    //    a += 3.1;
    a = ctx.int_const("a");
    solver.add(a == ctx.int_val((int)3.1));
    //    assert(a == 3);
    solver.add(a == ctx.int_val(3));
    std::cout << solver.check() << std::endl;

}
