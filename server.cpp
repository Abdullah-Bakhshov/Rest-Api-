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
    ([](const crow::request& req) {
        try {

            // check the type of content we are recieveing set by client
            std::cout << "Received request: " << req.get_header_value("Content-Type") << std::endl;
            
            // if we don't find anything we get a value of -1 which is npos, negative position , position not found
            // if we find the string we are looking for we get a value greater than 0
            if (req.get_header_value("Content-Type").find("multipart/form-data") == std::string::npos) {
                return crow::response(400, "Didn't recieve type multipart/form-data");
            }

            // we are parsing the request data as a multipart message, puts the parts in a vector
            crow::multipart::message msg(req);

            // if we dont have any parts that means we have recieved no data just a call to the api
            if (msg.parts.empty()) {
                return crow::response(400, "No parts in the request.");
            }

            // we are setting the file path and name to store the data
            const std::string temp_file = "uploaded_video.mov";

            // we are opening the file at temp_file and writing binary data into it
            std::ofstream out(temp_file, std::ios::binary);


            // if we don't have a file to open we return a 500 error
            if (!out) {
                return crow::response(500, "Failed to open file for writing.");
            }

            // we are iterating over the different parts of the message to check if the content type is video quicktime or if it is empty
            // we then give a error if we don't get expected type
            // otherwise we then write the data to the file set by the size of the body being put in
            for (const auto& part : msg.parts) {
                const std::string content_type = part.get_header_object("Content-Type").value;
                if (content_type.empty() || content_type != "video/quicktime") {
                    return crow::response(400, "Invalid file type.");
                }
                out.write(part.body.data(), part.body.size());
            }

            // we then close the file after this is completed
            out.close();


            // SUCCESS!!!
            return crow::response(200, "Video uploaded successfully.");
            
        } catch (const std::exception& e) {

            // this is if we get a error while we process it such as segmentation fault ect
            return crow::response(500, std::string("Server error: ") + e.what());
        }
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