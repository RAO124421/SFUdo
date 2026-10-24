#include "signaling.h"

#include "../core/json.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;

using tcp = net::ip::tcp;

using json = nlohmann::json;

WebSocketClient::WebSocketClient(
    EventQueue *queue,
    Connections *conns
)
{
    eventQueue = queue;
    connections=conns;
}

void WebSocketClient::connectWebSocket()
{
    try
    {
        net::io_context ioc;

        tcp::resolver resolver(ioc);

        websocket::stream<tcp::socket> ws(ioc);

        auto const results =
            resolver.resolve(
                "localhost",
                "9000"
            );

        net::connect(
            ws.next_layer(),
            results
        );

        ws.handshake(
            "localhost",
            "/ws"
        );

        std::cout
            << "WebSocket Connected OK"
            << std::endl;

        eventQueue->push({
            "connected",
            "We are connected"
        });

        // SEND JSON MESSAGE
        json connectMessage = {
            {"host","server"},
            {"type", "join"},
        };

        ws.write(
            net::buffer(
                connectMessage.dump()
            )
        );

        // KEEP READING FOREVER
        while(true)
        {
            beast::flat_buffer buffer;

            ws.read(buffer);

            std::string message =
                beast::buffers_to_string(
                    buffer.data()
                );

            std::cout
                << "Server: "
                << message
                << std::endl;

            json parsedMessage = json::parse(message);
            if(parsedMessage["type"]=="connected"){
                 eventQueue->push({
                "setConnected",
                "Signaling server is connected "
                });
                continue;
            }
            
            if(parsedMessage["type"]=="client_connected"){
                connections->createClient(parsedMessage["clientid"]);
                json sendtoclient = {
                    {"host","server"},
                    {"type", "sendtoclient"},
                    {"clientid",parsedMessage["clientid"]}
                };

                ws.write(
                    net::buffer(
                        sendtoclient.dump()
                    )
                );



                continue;
            }


            // PUSH TO EVENT QUEUE
            // eventQueue->push({
            //     "message",
            //     message
            // });
        }
    }
    catch(std::exception const& e)
    {
        std::cout
            << "Error: "
            << e.what()
            << std::endl;

        eventQueue->push({
            "error",
            e.what()
        });
    }
}