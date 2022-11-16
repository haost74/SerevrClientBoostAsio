//#include "src/msg/chat_message.hpp"
#include "src/msg/msg.hpp"
#include <vector>
using std::vector;


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

    boost::asio::io_context io_context;

    std::list<msg::chat_server> servers;
    for (int i = 1; i < argc; ++i)
    {
      tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
      servers.emplace_back(io_context, endpoint);
    }

    io_context.run();
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