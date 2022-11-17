//#include "src/msg/chat_message.hpp"
#include "src/msg/msg.hpp"
#include <vector>
using std::vector;

// Test-NetConnection 127.0.0.1 -Port 3200   

/*

   int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(argv[1], argv[2]);
    chat_client c(io_context, endpoints);

    std::thread t([&io_context](){ io_context.run(); });

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
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

*/


int main(int argc, char* argv[])
{
 using namespace msg;
  try
  {
    if (argc < 3)
    {
      std::cerr << "Select start client\\server and Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }

    // vector<std::string> port_s;
    // vector<std::string> port_c;
    // unsigned short ch = 0;

    // for (int i = 1; i < argc; ++i)
    // {
    //   std::string tmp = argv[i];
    //   std::string s = "-s";
    //   std::string c = "-c";
    //   if(tmp == s)
    //   {
    //     ch = 1;
    //   }
    //   else if(tmp == c)
    //   {
    //     ch = 2;
    //   }
    //   std::cout << tmp << " " << ch << '\n';
    //   if(ch == 1 && tmp != s) port_s.push_back(tmp);
    //   if(ch == 2 && tmp != c) port_c.push_back(tmp);
    // }

    // std::cout << port_s.size() << '\n';
    // std::cout << port_c.size() << '\n';

    // if(port_s.size() > 0)
    // {

    // }

    // if(port_c.size() > 0)
    // {
      
    // }

    // return 0;


      std::string tmp = argv[1];
      std::string s = "-s";
      std::string c = "-c";

    if(s == tmp)
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
    else if(c == tmp)
    {
      boost::asio::io_context io_context;

      tcp::resolver resolver(io_context);
      std::string address = argv[2];
      std::string port = argv[3];
      std::cout << "address = " << address << " port = " << port << "\n";
      auto endpoints = resolver.resolve(address, port); // argv[1] = host argv[2] = port
      chat_client c(io_context, endpoints);

      std::thread t([&io_context](){ io_context.run(); });

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
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  std::string h("");
  while(h != "h")
    std::cin >> h;

    return 0;
}