#pragma once
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "chat_message.hpp"

namespace msg
{
    #pragma region server
     class chat_participant
    {
        public:
            virtual ~chat_participant() {}
            /// @brief доставитть
            /// @param msg 
            virtual void deliver(const chat_message& msg) = 0;
    };

    using boost::asio::ip::tcp;
    typedef std::deque<chat_message> chat_message_queue;
    typedef std::shared_ptr<chat_participant> chat_participant_ptr;

    

    class chat_room
    {

        std::set<chat_participant_ptr> participants_;
        enum { max_recent_msgs = 100 };
        chat_message_queue recent_msgs_;
        public:
         void join(chat_participant_ptr participant);
         void leave(chat_participant_ptr participant);
         void deliver(const chat_message& msg);
    };

    class chat_session
  : public chat_participant,
    public std::enable_shared_from_this<chat_session>
    {
 
       tcp::socket socket_;
            chat_room& room_;
            chat_message read_msg_;
            chat_message_queue write_msgs_;

            void do_read_header();
            void do_read_body();
            void do_write();

       public:
          chat_session(tcp::socket socket, chat_room& room)
            : socket_(std::move(socket)),
            room_(room){};
      
        void start();
        void deliver(const chat_message& msg);
    };

    
    class chat_server
    {
       tcp::acceptor acceptor_;
       chat_room room_;
       void do_accept();

       public:
    chat_server(boost::asio::io_context& io_context,
                const tcp::endpoint& endpoint);
    };

    #pragma endregion
    
    #pragma regiom client

       
     class chat_client
     {
        boost::asio::io_context& io_context_;
        tcp::socket socket_;
        chat_message read_msg_;
        chat_message_queue write_msgs_;
        void do_connect(const tcp::resolver::results_type& endpoints);
        void do_read_header();
        void do_read_body();
        void do_write();

        public:
        chat_client(boost::asio::io_context& io_context,
          const tcp::resolver::results_type& endpoints);
        void write(const chat_message& msg);
        void close();
     };

    #pragma endregion

}