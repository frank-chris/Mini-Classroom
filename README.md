# Server

In this directory, we have implemented server side functions.

## Functions
1. **server.cpp**: Starts the server, listens for the client side connection. Once it obtains a connection, it spawns a new thread to handle the client.
2. **server.hpp**: Contains all the important definitions, structs and functions used by the server.
3. **handle_client.cpp**: Contains all the functions and some of the helper functions needed by handle before he has logged in to his account.
4. **logged_in.cpp**: Contains all the functions that allow the user to perform all those actions once they have just logged in, such as create a class, enroll, join into a class, etc.
4. **instructor.cpp**: Contains the functions that the instructor needs in order to perform various actions once he has entered a particular classroom (where he is the instructor).
5. **student.cpp**: Contains the functions that the student needs in order to perform various actions once he has entered a particular classroom (where he is a student).
6. **chat_server.cpp**: Contains the functions that are required to make the live chat work, after the instructor starts it.
7. **data_transfer.cpp**: Contains functions that help in file-handling. Each time a function wants to either send or receive data from the client, the functions in this file are called.
8. **helper.cpp**: Contains helper not related to data transfer. They help making the code manageable.
9. **filesystem.cpp**: Contains functions that create entries in the filesystem that we maintain on the server end.

&nbsp;
# Client

In this directory, we have implemented client side functions.

## Files
1. **client.cpp**: Contains code for initializing the client and setting up a connection with the server.
2. **handle.cpp**: Handles the send and receive functions to communicate with the server. It is also responsible to take in commands from the user.
3. **logging.cpp**: Handles the client's logged in and logged out states. Contains two functions, one for logging in and another for reigstering a new user.
4. **entering.cpp**: Handles the outline view of the user's classes. Contains functions to view coursrs and enroll or enter a course.
5. **instructor.cpp**: Handles the Instructor's features for a particular course.
6. **student.cpp**: Handles the Student's features for a particular course.
7. **chat_client.cpp**: Handles the chat utility in the client. Innitates a new connection for connection with the chat server.
8. **enc.cpp**: Handles the encryption of the user credentials using substitution cypher.


&nbsp;

# Compiling  
  
To compile server and client binaries use:    
`make all`    

# Running  
To run the server:  
`./server_src/server <ip-address>`  
Example:       
`./server_src/server 127.0.0.1`    
   
To run the client:(use the port number 8080)  
`./client_src/client <ip-address> 8080`   
Example:     
`./client_src/client 127.0.0.1 8080`   
   
# Running Mininet test   
To run the Mininet topology and test code, use:   
`make mininet`    

# Cleaning   
To clean up, use   
`make clean`   
  
&nbsp;
# How to use it (Tutorial)
At all points, the terminal will guide with your list of available commands, and what they can be used for.
Follow the instructions, try not to type commands that are not allowed at the given point.
