//
// Created by Jiawei Wang on 1/13/22.
//

#include <z3++.h>
#include <iostream>
#include <unordered_map>

/*
int main() {
    int *p;
    int *q;
    int t;
    int a[2] = {0, 1};
    p = &a[0];
    q = &a[1];
    t =  *p;
    *p = *q;
    *q = t;
    assert(a[1] == 0);
    return 0;
}
 * */
struct PTS{
    std::string key;
    enum Datatype {
        INT,
        ARRAY,
    };
    Datatype type;
    int offset;
};

void print(z3::expr& expr) {
    std::cout  <<  expr.simplify()  << std::endl;
}

int main() {
    std::unordered_map<std::string, PTS> pts; //key: string, value: <string, int>
    z3::context ctx;
    z3::solver solver(ctx);
    z3::sort Int = ctx.int_sort();
    z3::sort Array = ctx.array_sort(Int,Int);
    // int *p;
    pts["p"] = PTS();
    // int *q;
    pts["q"] = PTS();
    // int t;
    z3::expr t = ctx.int_const("t");
    // int a[2] = {0, 1};
    z3::expr a = ctx.constant("a",Array);
    a = z3::store(a, 0, 0);
    a = z3::store(a, 1, 1);

    // p = &a[0];  M(p) :=M(M(q))
    PTS p_pts;
    p_pts.key = "a";
    p_pts.type = PTS::Datatype::ARRAY;
    p_pts.offset = 0;
    pts["p"] = p_pts;

    // q = &a[1];  M(p) :=M(M(q))
    PTS q_pts;
    q_pts.key = "a";
    q_pts.type = PTS::Datatype::ARRAY;
    q_pts.offset = 1;
    pts["q"] = q_pts;

    // t =  *p; M(p) :=M(M(q))
    t = ctx.int_const("t");
    auto p_tmp = z3::select(a, pts["p"].offset);
    solver.add(t == p_tmp);

    // *p = *q; M(p) := M(q)
    z3::expr p1 = z3::select(a, pts["p"].offset);
    z3::expr q1 = z3::select(a, pts["p"].offset);
    a = z3::store(a, pts["p"].offset, q1);

    // *q = t;  M(M(p) := q
    q1 = z3::select(a, pts["q"].offset);
    t = ctx.int_const("t");
    a = z3::store(a, pts["q"].offset, t);

    // assert(a[1] == 1);
    auto tmp00 = z3::select(a, 0);
    auto tmp01 = z3::select(a, 1);
    solver.add(z3::select(a, 1) == ctx.int_val(0));
    // END
    z3::check_result res = solver.check();
    std::cout << res << std::endl;
    return 0;
}