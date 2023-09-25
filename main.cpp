#include <iostream>
#include <atomic>
#include <csignal>
#include <thread>

using namespace std::chrono_literals;

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerParams.h"

std::atomic <bool> running{true};

using TCPServerConnection = Poco::Net::TCPServerConnection;

void signal_handler(int s){
    std::cout << "\nStopping server...\n";
    running = false;
}

class ReverseInputDataConnection: public TCPServerConnection{

public:
    void run() override {
            unsigned char m_buf[257] = {0};
            decltype(auto) ss = socket();

            while (running) {
                int n = ss.receiveBytes(m_buf, sizeof(m_buf));
                if (n > 2) {
                    std::reverse(m_buf, m_buf + n - 2);
                    ss.sendBytes(m_buf, n);
                }
            }
    }
    ReverseInputDataConnection(const Poco::Net::StreamSocket& s) :
            TCPServerConnection(s){}
};

int main() {
    try {
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);

        auto factory = new Poco::Net::TCPServerConnectionFactoryImpl<ReverseInputDataConnection>();
        Poco::Net::ServerSocket server_socket(28888);
        auto params = new Poco::Net::TCPServerParams();

        Poco::Net::TCPServer server(
                factory,
                server_socket,
                params);

        server.start();

        while (running) {
            std::this_thread::sleep_for(500ms);
        }

        server.stop();
    }
    catch(const Poco::Exception& exc) {
        std::cerr << "Exception thrown: " << exc.displayText() << std::endl;
    }
    catch(const std::exception& exc) {
        std::cerr << "Exception thrown: " << exc.what() << std::endl;
    }
    return 0;
}