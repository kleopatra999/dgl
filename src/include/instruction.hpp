#pragma once

#include "make_unique.hpp"

#include <memory>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;



struct Instruction
{
    uint16_t                    id;
    unique_ptr<asio::streambuf> _buf;
    unique_ptr<ostream>         _stream;

    Instruction(uint16_t id) :
            id(id),
            _buf(make_unique<asio::streambuf>()),
            _stream(make_unique<ostream>(_buf.get())) {
        write(id);
    };

    template<typename T>
    void write(T e) {
        stream().write((char*)&e, sizeof(e));
    }

    template<typename T>
    void write(T* b, size_t size) {
        stream().write((char*)b, size);
    }

    ostream& stream()                   { return *_stream; }
    asio::streambuf& buf()              { return *_buf; }
};
