#include<iostream>

template <typename T>
class Value{

private:
    T x;

public:
    
    Value(T val){
        this->x=val;
    }
    
    Value operator+(const Value& v1){
        T out=this->x+v1.x;
        return Value(out);
    }

    Value operator*(const Value& v1){
        T out=this->x*v1.x;
        return Value(out);
    }

    T get_value() const{
        return this->x;
    }

};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Value<T>& v) {
    return os << "Value(" << v.get_value() << ")";
}

int main(){
   
    Value<int> a1(5);
    Value<int> a2(10);
    Value<int> a3(15);

    std::cout<<a1+a2<<std::endl;
    std::cout<<a2*a3<<std::endl;
    std::cout<<a1+a2*a3<<std::endl;
}