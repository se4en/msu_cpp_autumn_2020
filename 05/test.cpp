#include "serializer.h"

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer_>
    Error serialize(Serializer_& serializer) {
        return serializer(a, b, c);
    }

    template <class Deerializer_>
    Error deserialize(Deerializer_& deserializer) {
        return deserializer(&a, &b, &c);
    }
};

void base_work_test() {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    std::cout << y.a << y.b << y.c << std::endl;
}

int main() {
    base_work_test();
}