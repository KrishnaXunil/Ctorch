
#include <iostream>
#include <cassert>
#include <memory>
#include "../include/value.hpp"

using namespace std;

void test_addition() {
    auto a = make_shared<Value<double>>(2.0);
    auto b = make_shared<Value<double>>(3.0);

    auto c = *a + b;

    assert(c->get_value() == 5.0);
    assert(c->get_operation() == Operation::ADD);

    cout << "[PASS] Addition test\n";
}

void test_multiplication() {
    auto a = make_shared<Value<double>>(2.0);
    auto b = make_shared<Value<double>>(3.0);

    auto c = *a * b;

    assert(c->get_value() == 6.0);
    assert(c->get_operation() == Operation::MUL);

    cout << "[PASS] Multiplication test\n";
}

void test_nested_expression() {
    auto a = make_shared<Value<double>>(2.0);
    auto b = make_shared<Value<double>>(3.0);
    auto c = make_shared<Value<double>>(4.0);

    auto x = *a * b;
    auto y = *x + c;
    auto loss = *y * y;

    assert(x->get_value() == 6.0);
    assert(y->get_value() == 10.0);
    assert(loss->get_value() == 100.0);

    assert(x->get_operation() == Operation::MUL);
    assert(y->get_operation() == Operation::ADD);
    assert(loss->get_operation() == Operation::MUL);

    cout << "[PASS] Nested expression test\n";
}

void test_computational_graph() {
    auto a = make_shared<Value<double>>(2.0);
    auto b = make_shared<Value<double>>(3.0);

    auto x = *a * b;
    auto y = *x + a;

    // x should have two parents
    assert(x->get_prev().size() == 2);

    // y should have two parents
    assert(y->get_prev().size() == 2);

    // Check that y retains its parent references
    assert(y->get_prev()[0] == x);
    assert(y->get_prev()[1] == a);

    // Check operation types
    assert(x->get_operation() == Operation::MUL);
    assert(y->get_operation() == Operation::ADD);

    // Leaf nodes should have no parents and NONE operation
    assert(a->get_prev().empty());
    assert(a->get_operation() == Operation::NONE);

    cout << "[PASS] Computational graph test\n";
}

int main() {

    cout << "\nRunning Ctorch tests...\n\n";

    test_addition();
    test_multiplication();
    test_nested_expression();
    test_computational_graph();

    cout << "\nAll tests passed!\n";

    return 0;
}
