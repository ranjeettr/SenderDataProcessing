The purpose of this is to create N senders and one receiver threads
N senders will send messages of the format <sender_id><alphanumeric string> unsorted way
Once N senders send all the messages, the receiver thread will process all the messages in sorted order of sender id.

Eg:- 
Sender_1 sends 1adas
Sender_3 sends 3zxcv
Sender_2 sends 2qweq
Sender_1 sends 1aaaa

Data should be processed in the order
1adas
1aaaa
2qweq
3zxcv

Note:- The order in which senders send data is dependent on OS scheduling the sender threads

Build Process
=============
1. To build this, download and install g++, CMake and make
2. Once you copy/checkout this code, run "make" in the top level directory
3. After running make, the binary processmessages will deployed in the build directory
4. Go to build directory
5. Execute the binary as ./processmessages
6. In order to delete the build artifactories, run "make clean"



1. The directory Buffer contains the data structure that stores data sent by N senders
2. The directory Sender contains code for Sender threads and sending data
3. The directory Receiver contains code for processing data in sorted order of sender_id



If you have any questions, please reachout to ranjeettr@gmail.com

Thanks,
Ranjeet
