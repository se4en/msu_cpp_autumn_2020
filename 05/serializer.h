#include <iostream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
    std::ostream& out_;

    template <class... ArgsT>
    Error process(ArgsT... args);
public:
    explicit Serializer(std::ostream& out);

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);
};