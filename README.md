# Remote Shell for Linux
Hello, this project lets you to connect to a another terminal and send commands!

## Example of using
I created simple testing code to show how you can use remote shell in your local network. 
### For fast way to compile this test code you need to write this commands
> g++ test_client.cpp netAPI.cpp database.cpp -o client -std=gnu++17 -w

and

> g++ test_server.cpp netAPI.cpp database.cpp -o server -std=gnu++17 -w

### After compilation of client and server you need to write this command in your main system or terminal

> ./client 0.0.0.0

Then go to another system or terminal and write a similar command ***and*** with the same ip-address that we wrote in client part, in our case it's "0.0.0.0"

> ./server 0.0.0.0

Great! We have local connection! Now you can see in client part similarity of terminal, so write your command and enjoy!

## Advantages of remote shell
+ Fast and simple method to ***fix issues*** on server, computer, phone or something else on Linux
+ Simple and understandable code with smart control of memory achieved by using ***Smart pointers*** in library SPtr.h and types whose name specifies the ***size in bits*** in library Core.h
+ Using ***RSA*** encryption for your safety!

## Good luck and have a nice day!
