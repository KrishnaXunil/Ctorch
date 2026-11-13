#include <iostream>
#include <memory>
#include <vector>
#include <utility>
using namespace std;

enum class Operation {
    NONE,
    ADD,
    MUL
};

const char* operation_to_string(Operation op) {
    switch (op) {
        case Operation::ADD: return "ADD";
        case Operation::MUL: return "MUL";
        default: return "NONE";
    }
}

//Here in prev parameter, we need to store references to Value objects 
//which contribute to current expression(Value object), these are 
//intermediary nodes but we need to hold them because they are referenced
//while backprop so this could be a memory bottleneck but optimization strategy
//could be used as done in pytorch

template <typename T>
//we need to have this class inherited so that we can access the shared 
//pointer to that pointer using (this) pointer because normally it will
//give a normal pointr to that object that could get destroyed.
//crazy shit
class Value : public enable_shared_from_this<Value<T>> {

private:
    T x;

    using ValuePtr = shared_ptr<Value<T>>;

    //Here we cant keep normal Value pointers because in nested expressions 
    //like a*b+c holding only Value* would let temporary a*b get destroyed
    //giving reference to a dangling pointer leaking memory
    //so we need to use shared pointer because we need to make sure
    //the temporary nodes stay alive till the time we reference it
    //using a vector is sufficient

    vector<ValuePtr> prev;
    Operation op;

public:

    Value(T val, vector<ValuePtr> prev = {},Operation op=Operation::NONE)
        : x(val), prev(move(prev)),op(op) {}

    ValuePtr operator+(const ValuePtr& v1) {
        T out = this->x + v1->x;

        return make_shared<Value<T>>(
            out,
            vector<ValuePtr>{
                this->shared_from_this(), v1
            },
            Operation::ADD
        );
    }

    ValuePtr operator*(const ValuePtr& v1) {
        T out = this->x * v1->x;

        return make_shared<Value<T>>(
            out,
            vector<ValuePtr>{
                this->shared_from_this(), v1
            },
            Operation::MUL
        );
    }

    T get_value() const {
        return this->x;
    }

    const vector<ValuePtr>& get_prev() const {
        return prev;
    }

    const Operation get_operation() const {
        return op;
    }

};


//this ostream is c++ type for output stream
//cout is an object of this type
//It needs to be public because when we override the operator is usually to the right
//but here operator << is to the left so it needs to be public
//we exposed a getter for Value so that 'x' can be accessed via it.
template<typename T>
ostream& operator<<(ostream& os, const Value<T>& v) {

    os << "Value(data=" << v.get_value() << ", prev={";

    bool first = true;

    for (const auto& child : v.get_prev()) {
        if (!first) os << ", ";

        os << child->get_value();
        first = false;
    }

    os << "}, operation=" << operation_to_string(v.get_operation()) << ")";

    return os;
}
//similar example
// ofstream file("out.txt")
// file<<a --------This writes to a file