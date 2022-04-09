#include <iostream>

int b =30;

void test(int *p){
    std::cout<<&p<<'\n';
}
int main(){

    int a = 0;
    int *p = &a;
    std::cout<<&p<<'\n';
    std::cout<<p<<'\n';
    std::cout<<&a<<'\n';
    test(p);

    return 0;
}