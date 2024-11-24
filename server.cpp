#include "crow.h"
#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem> 

// // request data we are then processing, middleware
// // struct ContextData{

// //     // local data where we store the parsed data, intermediate for the other service to handle
// //     struct context{};

// //     // takes input to api and standerdises it
// //     void before_handle(crow::request &req, crow::response &res, context &ctx){

// //     }

// //     // after we are finished with intermediate service we then send it back to client in this format
// //     void after_handle(crow::request &req, crow::response &res, context &ctx){

// //     }
// // };



int main(){

    // Instance of the api server I'm creating
    // crow::App<ContextData> server;
    crow::SimpleApp server; // testing


    // Route for root
    CROW_ROUTE(server, "/")
    ([](){
        return "this is root";
    });

    
    // MACHINE LEARNING ROUTING
    
    // Route for uploading video processing - machine learning

    CROW_ROUTE(server, "/uploading_to_ml_model").methods(crow::HTTPMethod::POST)
        // making a request to the server, const makes it static and therefore can't be changed,
        // & means its passed by reference
    ([](const crow::request& req){

        // the request we got to the server is then parsed as a multipart message, 
        crow::multipart::message msg(req);

        // checking if the request contains any parts
        if (msg.parts.empty()) {
            return crow::response(400, "the file send was empty or not found");
        }

        // define a path to save the video to and the name of the file
        const std::string temp_file = "uploaded_video.mp4";

        // Save the file content to the filesystem as a text file opened as a binary file
        std::ofstream out(temp_file, std::ios::binary);

        // iterating through the parts of the message, msg.parts is a vector of parts
        for (const auto& part: msg.parts){
            // check if the header is correct => exoecting video/mp4
            // we are checking the map for the key with the value of "Content-Type"
            const std::string content_type = part.get_header_object("Content-Type").value;
            // we check if we found the header and if its value is a video file
            if (content_type.empty() || content_type != "video/mp4") {
                return crow::response(400, "the file is not a video file or it does not have a type");
            }
            // if we dont get a output from file we return a 500 error
            if (!out) {
                return crow::response(500, "failed to save the file to disk.");
            }
            // we write the body of the part to the file, .data() is the pointer and the .size() is the size of the datab
            out.write(part.body.data(), part.body.size());
        }
        // closing the file
        out.close();

        // SUCCESS
        return crow::response(200,"video has been succesfully been uploaded");
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