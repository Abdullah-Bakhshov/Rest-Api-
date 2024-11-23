#include "crow.h"
#include <asio.hpp>

// request data we are then processing, middleware
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

    
    
    
    
    
    
    // MACHINE LEARNING ROUTING
    
    // Route for uploading video processing - machine learning

    CROW_ROUTE(server, "/uploading_to_ml_model").methods(crow::HTTPMethod::PUT)
    ([](){
        return "this is where machine learning will take place"; // this will give error we want to return a request to a cv2 model
    });

    // Route for retrieving the video processing

    CROW_ROUTE(server, "/retrieving_the_ml_model").methods(crow::HTTPMethod::GET)
    ([](){
        return "this will return the highlight timing and court coverage";
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

    // Runs server, set default port to default (80) and used threading to handle multiple requests
    server.port(80).multithreaded().run();

    // Success
    return 0;
}