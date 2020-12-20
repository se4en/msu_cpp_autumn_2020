#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>
#include <sstream>
#include <type_traits>

enum class Error {
    No_error,
    Unsupported_type,
    Corrupted_archive
};

class Serializer {
    std::string separator = " ";
    std::ostream& out_; 

    template <class T>
    Error process(T last);

    template <class T, class... ArgsT>
    Error process(T first, ArgsT... args); 
public:
    explicit Serializer(std::ostream& out);

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Serializer::Serializer(std::ostream& out): out_(out) {}

template <class T>
Error Serializer::process(T last) {
    if (std::is_same<T, bool>::value) {
        if (last)
            out_ << "true";
        else
            out_ << "false";
    }
    else if (std::is_same<T, uint64_t>::value) {
        out_ << last;
    }
    else
        return Error::Unsupported_type;
    return Error::No_error;
}

template <class T, class... ArgsT>
Error Serializer::process(T first, ArgsT... args) {
    if (std::is_same<T, bool>::value) {
        if (first) 
            out_ << "true" << separator;
        else
            out_ << "false" << separator;
    }
    else if (std::is_same<T, uint64_t>::value) 
        out_ << first << separator;
    else
        return Error::Unsupported_type;
    return process(args...);
}

template <class T>
Error Serializer::save(T& object) {
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args) {
    return process(args...);
}

//===================================================================================================================================================================================================

class Deserializer {
    static constexpr char separator = ' ';
    std::istream& in_;

    template <class T>
    Error process(T last);

    template <class T, class... ArgsT>
    Error process(T first, ArgsT... args); 
public:
    explicit Deserializer(std::istream& in);

    template <class T>
    Error load(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Deserializer::Deserializer(std::istream& in): in_(in) {}

template <class T>
Error Deserializer::load(T& object) {
    return object.deserialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT... args) {
    return process(args...);
}

template <class T>
Error Deserializer::process(T last) {
    std::string text;
    in_ >> text;

    if (std::is_same<T, bool*>::value) {
        if (text=="true")
            *last = true;
        else if (text=="false")
            *last = false;
        else
            return Error::Corrupted_archive;
        
    }
    else if (std::is_same<T, uint64_t*>::value)
        try {
            *last = stoull(text); 
        }
        catch(std::invalid_argument& err) {
            return Error::Corrupted_archive;
        }
        catch(std::out_of_range& err) {
            return Error::Corrupted_archive;
        }
    else 
        return Error::Unsupported_type;
    return Error::No_error;
}

template <class T, class... ArgsT>
Error Deserializer::process(T first, ArgsT... args) {
    Error cur_err = process(first);
    if (cur_err==Error::No_error)
        return process(args...);
    else 
        return cur_err;
}

#endif