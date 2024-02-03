#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <vector>
#include <unistd.h>

using namespace std;

int numberOfSenders = 0;

mutex senderMtx;
condition_variable senderCv;

mutex receieverMtx;
condition_variable receiverCv;

map<int, vector<string>> buffer;


void receiver()
{
	unique_lock<mutex> lck(receieverMtx);
	receiverCv.wait(lck);

	cout << "Receiver thread\n";

	while( !buffer.empty() )
	{
		map<int, vector<string>>::iterator it = buffer.begin();
	        if( !( it->second.empty() ) )
        	{
                	vector<string>::iterator itstr = it->second.begin();
	                cout << "Processing data: " << *itstr << "\n";
        	        it->second.erase( itstr );
                	if( it->second.empty() )
                        	buffer.erase( it );
	        }
	}
}

void sender( int sender_id )
{
	unique_lock<mutex> lck(senderMtx);
	senderCv.wait(lck);

	string message = to_string( sender_id ) + "abcde";
        map<int, vector<string>>::iterator it = buffer.find( sender_id );
        if( it != buffer.end() )
	{
                it->second.push_back( message );
	}
        else
        {
                vector<string> str;
                str.push_back( message );
                buffer.insert( pair<int, vector<string>>( sender_id, str ) );
        }

	cout << "Sender_" << sender_id << " sending data: " << message << "\n";

	--numberOfSenders;
	if( !numberOfSenders )
		receiverCv.notify_one();
	senderCv.notify_all();
}

int main()
{
	cout << "How many senders you want to create: ";
	cin >> numberOfSenders;

	thread threads[numberOfSenders];

	for( int i = 0; i < numberOfSenders; i++ )
	{
		threads[i] = thread( sender, i+1 );
	}

	thread rcv = thread( receiver );

	senderCv.notify_all();

	for( auto &ths : threads )
		ths.join();
	rcv.join();


	return 0;
}
