// #include "src/msg/chat_message.hpp"
#include "src/msg/msg.hpp"
#include <vector>
using std::vector;

// Test-NetConnection 127.0.0.1 -Port 3200

int main(int argc, char *argv[])
{

  using namespace msg;
  try
  {
    if (argc < 3)
    {
      std::cerr << "Select start client\\server and Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }

    std::string tmp = argv[1];
    std::string s = "-s";
    std::string c = "-c";

    if (s == tmp)
    {
      boost::asio::io_context io_context;

      std::list<msg::chat_server> servers;
      for (int i = 1; i < argc; ++i)
      {
        tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
        servers.emplace_back(io_context, endpoint);
      }

      io_context.run();
    }
    else if (c == tmp)
    {
      boost::asio::io_context io_context;

      tcp::resolver resolver(io_context);
      std::string address = argv[2];
      std::string port = argv[3];
      std::cout << "address = " << address << " port = " << port << "\n";
      auto endpoints = resolver.resolve(address, port); // argv[1] = host argv[2] = port
      chat_client c(io_context, endpoints);

      std::thread t([&io_context]()
                    { io_context.run(); });

      char line[chat_message::max_body_length + 1];
      while (std::cin.getline(line, chat_message::max_body_length + 1))
      {
        chat_message msg;
        msg.body_length(std::strlen(line));
        std::memcpy(msg.body(), line, msg.body_length());
        msg.encode_header();
        c.write(msg);
      }

      c.close();
      t.join();
    }
    else
    {
      std::cout << argv[1] << '\n';
      std::cerr << "Select start client\\server and Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  std::string h("");
  while (h != "h")
    std::cin >> h;

  return 0;
}