#pragma once

#include <boost/asio.hpp>

struct Instruction
{
    uint16_t                id;

    Instruction(uint16_t id)
        : id(id) {};
};
