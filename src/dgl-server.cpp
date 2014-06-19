#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;



void session(tcp::socket socket) {
    try {
        asio::streambuf buf;
        istream         stream(&buf);
        for (;;) {
            asio::read_until(socket, buf, '\n');
            uint16_t    id;
            stream.read((char*)&id, sizeof(id));
            stream.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << id << endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(asio::io_service& io_service, unsigned short port) {
    tcp::acceptor acceptor(
        io_service,
        tcp::endpoint(tcp::v4(), port));
    for (;;) {
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        std::thread(session, std::move(socket)).detach();
    }
}

int main(int, char**) {
    try {
        asio::io_service io_service;
        server(io_service, 12345);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
