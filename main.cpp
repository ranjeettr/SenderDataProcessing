#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

int numberOfSenders = 0;

mutex senderMtx;
condition_variable senderCv;

mutex receieverMtx;
condition_variable receiverCv;


void receiver()
{
	unique_lock<mutex> lck(receieverMtx);
	receiverCv.wait(lck);

	cout << "Receiver thread\n";
}

void sender( int sender_id )
{
	unique_lock<mutex> lck(senderMtx);
	senderCv.wait(lck);

	cout << "Sender thread: " << sender_id << "\n";
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

	sleep(1);

	senderCv.notify_all();

	for( auto &ths : threads )
		ths.join();
	rcv.join();


	return 0;
}
