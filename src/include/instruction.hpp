#pragma once

#include "make_unique.hpp"

#include <memory>
#include <boost/asio.hpp>

using namespace std;
typedef boost::asio::streambuf asio_streambuf;

struct Instruction
{
    uint16_t                    id;
    unique_ptr<asio_streambuf>  _buf;
    unique_ptr<ostream>         _stream;

    Instruction(uint16_t id) :
            id(id),
            _buf(make_unique<asio_streambuf>()),
            _stream(make_unique<ostream>(_buf.get())) {
    };

    ostream& stream() {
        return *_stream;
    }
};
