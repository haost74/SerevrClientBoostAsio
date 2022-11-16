#include "synserver.hpp"
#include <boost/json/src.hpp>


namespace syn{
    void server::start()
    {
        try
        {
            tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
            for(;;)
            {
                tcp::socket socket(io_service);
                acceptor.accept(socket);
                std::string message = make_daytime_string();

                boost::system::error_code ignored_error;
                boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    string server::make_daytime_string()
     {
        auto now = std::time(0);
        return ctime(&now);
     }
}