#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class base
{
    public:
        virtual void print()
        {
            printf("base\n");
        }
};

class child : public base
{
    public:
        virtual void print()
        {
            printf("child\n");
        }
};

int main()
{
    //************  dynamic_cast ***********************
    child* p_child = new child();
    base* p_base = dynamic_cast<base*>(p_child);
    p_base->print();

    //************  static_cast ************************
    double dvalue = 1000.123;
    int32_t ivalue = static_cast<int32_t>(dvalue);
    printf("static_cast value is : %d\n", ivalue);

    //*********** reinterpret_cast ********************
    int32_t int_value [2] = {100, 200};
    int64_t int_address = reinterpret_cast<int64_t>(int_value);
    int32_t* int_point = reinterpret_cast<int32_t*>(int_address);
    printf("renterpret_case value is : %d\n", *int_point);

    //********** const_cast ****************************
    int const v = 10000;
    int const* const p_v = &v;
    // *p_v = 11111;
    int* c_v = const_cast<int*>(p_v);
    *c_v = 1234;

    printf("const_cast %d %d\n", *p_v, *c_v);

    return 0;
}
