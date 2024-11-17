#include "crow.h"
#include <asio.hpp>




int main(){

    // instance of the api server
    crow::SimpleApp server;

    // route for root
    CROW_ROUTE(server, "/")
    ([](){
        return "this is root";
    });

    // route for video processing
    CROW_ROUTE(server, "/video_process")
    ([](){
        return "this is where machine learning will take place";
    });

    // route for video data
    CROW_ROUTE(server, "/video_meta")
    ([](){
        return "this is where we call on the data base for video data";
    });

    // set default port to default ~ 80 and used threading to handle multiple calls
    server.port(80).multithreaded().run();

    // success
    return 0;
}