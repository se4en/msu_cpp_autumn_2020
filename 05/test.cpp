#include "serializer.h"

#define FAIL(test, result, right_result) std::cout << "[FAIL] " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl; 
#define OK(test, result, right_result) std::cout << "[OK]   " << test << "\n\tget:  " << result << "\n\twant: " << right_result << std::endl;

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;
    bool d;

    template <class Serializer_>
    Error serialize(Serializer_& serializer) {
        return serializer(a, b, c, d);
    }

    template <class Deserializer_>
    Error deserialize(Deserializer_& deserializer) {
        return deserializer(&a, &b, &c, &d);
    }
};

struct Ok_data {
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

struct Wrong_data {
    uint64_t a;
    bool b;
    char c;

    template <class Serializer_>
    Error serialize(Serializer_& serializer) {
        return serializer(a, b, c);
    }

    template <class Deerializer_>
    Error deserialize(Deerializer_& deserializer) {
        return deserializer(&a, &b, &c);
    }
};

void bool_test() {
    Data x {1, true, 2, false};
    Data y {0, false, 0 , true};

    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    serializer.save(x);
    deserializer.load(y);

    if (y.b && !y.d)
        OK("bool", y.b<<" "<<y.d, "1 0")
    else
        FAIL("bool", y.b<<" "<<y.d, "1 0")
}

void uint_test() {
    Data x {11111111, true, 22222222, false};
    Data y {0, false, 0 , true};

    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    serializer.save(x);
    deserializer.load(y);

    if (y.a==11111111 && y.c==22222222)
        OK("uint", y.a<<" "<<y.c, "11111111 22222222")
    else
        FAIL("uint", y.a<<" "<<y.c, "11111111 22222222")
}

void unsupported_type_test() {
    Wrong_data x {1, true, 's'};

    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    Error err = serializer.save(x);

    if (err==Error::Unsupported_type)
        OK("unsupported_type", "Unsupported_type", "Unsupported_type")
    else { 
        if (err==Error::No_error)
            FAIL("unsupported_type", "No_error", "Unsupported_type")
        else
            FAIL("unsupported_type", "Corrupted_archive", "Unsupported_type")
    }
}

void no_error_test() {
    Data x {1, true, 2, false};
    Data y {0, false, 0 , true};

    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    serializer.save(x);
    Error err = deserializer.load(y);


    if (err==Error::No_error)
        OK("no_error", "No_error", "No_error")
    else { 
        if (err==Error::Unsupported_type)
            FAIL("no_error", "Unsupported_type", "No_error")
        else
            FAIL("no_error", "Corrupted_archive", "No_error")
    }
}

void corrupted_archive_test() {
    Ok_data x {1, true, 2};
    Data y {0, false, 3, false};

    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);

    serializer.save(x);
    Error err = deserializer.load(y);


    if (err==Error::Corrupted_archive)
        OK("corrupted_archive", "Corrupted_archive", "Corrupted_archive")
    else { 
        if (err==Error::Unsupported_type)
            FAIL("corrupted_archive", "Unsupported_type", "Corrupted_archive")
        else
            FAIL("corrupted_archives", "No_error", "Corrupted_archive")
    }
}

int main() {
    bool_test();
    uint_test();
    unsupported_type_test();
    no_error_test();
    corrupted_archive_test();
}