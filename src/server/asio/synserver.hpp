#pragma once
// #include <boost/json/src.hpp>
#include <iostream>
#include "boost/json/parse.hpp"
#include <boost/thread/thread.hpp>

#include <string>
using std::string;
namespace json = boost::json;


#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ctime>

using boost::asio::ip::tcp;

namespace syn
{
    class server
    {

        boost::asio::io_service io_service;
        
       public:
         void start();
         string make_daytime_string();
    };
}