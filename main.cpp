#include "crow.h"
#include <asio.hpp>

// request data we are then processing
struct ContextData{

    // local data where we store the parsed data, intermediate for the other service to handle
    struct context{};

    // takes input to api and standerdises it
    void before_handle(crow::request &req, crow::response &res, context &ctx){

    }

    // after we are finished with intermediate service we then send it back to client in this format
    void after_handle(crow::request &req, crow::response &res, context &ctx){

    }
};



int main(){

    // Instance of the api server I'm creating
    crow::App<ContextData> server;

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


    // SETTING THE ROUTES FOR VIDEO DATA

    // Route for setting video data in the data base
    CROW_ROUTE(server, "/video_meta_storing").methods(crow::HTTPMethod::PUT)
    ([](){
        return "this is where we store data for video data"; 
    });

    // Route for getting video data from the data base
    CROW_ROUTE(server, "/video_meta_history").methods(crow::HTTPMethod::GET)
    ([](){
        // handles what we send back to the client
        return "this is where we call on the data base for video data";
    });

    // Runs server, set default port to default ~ 80 and used threading to handle multiple calls
    server.port(80).multithreaded().run();

    // Success
    return 0;
}