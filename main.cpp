#include "crow.h"
#include <asio.hpp>




int main(){

    // Instance of the api server I'm creating
    crow::SimpleApp server;

    // Route for root
    CROW_ROUTE(server, "/")
    ([](){
        return "this is root";
    });

    // Route for video processing
    CROW_ROUTE(server, "/video_process")
    ([](){
        return "this is where machine learning will take place";
    });

    // Route for video data
    CROW_ROUTE(server, "/video_meta")
    ([](){
        return "this is where we call on the data base for video data";
    });

    // Runs server, set default port to default ~ 80 and used threading to handle multiple calls
    server.port(80).multithreaded().run();

    // Success
    return 0;
}