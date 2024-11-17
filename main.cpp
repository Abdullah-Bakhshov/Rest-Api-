#include "crow.h"
#include <asio.hpp>


/*
(2024-11-16 23:50:58) [INFO    ] Crow/master server is running at http://0.0.0.0:800 using 8 threads
(2024-11-16 23:50:58) [INFO    ] Call `app.loglevel(crow::LogLevel::Warning)` to hide Info level logs.
(2024-11-16 23:51:10) [INFO    ] Request: 127.0.0.1:64943 0x147011818 HTTP/1.1 GET /
(2024-11-16 23:51:10) [INFO    ] Response: 0x147011818 / 200 0
(2024-11-16 23:51:10) [INFO    ] Response: 0x147011818 /favicon.ico 404 0

- crow is running a server, and the value 0.0.0.0 means its listening for all ip address.
- the port 800 as we set, using 8 threads for incoming requests.
- the client thats making the request is at 127.0.0.1 with port 64943 , and we carry out the get request.
- next line we get a 200 code meaning it worked perfect, the / means thats what we were asking for and the 
  0 is a representation of the bytes of information.
- next line we got a code 404 meaning the resource wasnt found at favicon.ico.
- response 0x147011818, means the hexidecimal is a unique identifier to track the process carried out 
  the token such that we can give back to that token our result.


- 127.0.0.1 is the loopback ip address essentially meaning when you make a call to your own server this
  is the default ip they use.


*/

int main(){
    // crow is the name of the library and we are using the SimpleApp class from it.
    // the instance of the class is app.
    crow::SimpleApp app;

    /* we are setting up a route such that app can follow this when 
    connected and this case the url path is "/"

    Therefore when a client makes a request to the rool URL
            for this example http://localhost:8080/ 
    crow will look at this and then return the lambda function 
    
                            Hello world!

    lambda function in c++ looks like:
        [local variables](anonymous input parameters) -> output type { function }
    */
    CROW_ROUTE(app, "/")([]{
        return "skibidi!";
    });

    /* setting the port to 80 and allowing the app to use multiple threads,
    then running this app
    */  

    app.port(800).multithreaded().run();

    return 0;
}

