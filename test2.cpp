//
// Created by Jiawei Wang on 1/14/22.
//

/*
int main() {
    int *p;
    int *q;
    int t;
    int x = 1, y = 2;
    p = &x;
    q = &y
    t =  *p;
    *p = *q;
    *q = t;
    assert(y == 1);
    return 0;
}
*/
#include <z3++.h>
#include <iostream>
#include <unordered_map>
struct PTS{
    std::string key;
    enum Datatype {
        INT,
        ARRAY,
    };
    Datatype type;
    int offset;
};

int main() {
    std::unordered_map <std::string, PTS> pts; //key: string, value: <string, int>
    z3::context ctx;
    z3::solver solver(ctx);
    z3::sort Int = ctx.int_sort();
    // int *p;
    pts["p"] = PTS();
    //int *q;
    pts["q"] = PTS();

    //int t;
    z3::expr t = ctx.int_const("t");

    //int x = 1, y = 2;
    z3::expr x = ctx.int_const("x");
    z3::expr y = ctx.int_const("y");
    solver.add(x==ctx.int_val(1));
    solver.add(y==ctx.int_val(2));

    //p = &x;
    pts["p"].key = "x";

    //q = &y
    pts["q"].key = "y";

    //t =  *p; M(p):=M(M(q))
    t = ctx.int_const("t");
    solver.add(t == ctx.int_const(pts["p"].key.c_str())); // "x"

    //*p = *q;
    z3::expr p1 = ctx.int_const(pts["p"].key.c_str()); //x
    z3::expr q1 = ctx.int_const(pts["q"].key.c_str()); //y
    solver.add(p1==q1);
    //*q = t;
    t = ctx.int_const("t");
    solver.add(ctx.int_const(pts["q"].key.c_str()) == t);

    //assert(y == 1);
    solver.add(ctx.int_const("y") == ctx.int_val(1));
    std::cout << solver.check() << std::endl;

    return 0;
}