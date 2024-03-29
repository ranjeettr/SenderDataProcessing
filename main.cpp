#include <iostream>
#include <thread>
#include "Sender.h"
#include "Receiver.h"

using namespace std;

int main()
{
	int numberOfSenders = 0, numberOfMessagesPerSender = 0;

	cout << "How many senders you want to create: ";
	cin >> numberOfSenders;
	Sender::getInstance()->SetNumberOfSenders( numberOfSenders );

	if( numberOfSenders < 3 )
	{
		cout << "ERROR: Number of senders should be greater than or equal to 3\n";
		exit(1);
	}

	cout << "How many messages per sender you want to send: ";
	cin >> numberOfMessagesPerSender;

	if( numberOfMessagesPerSender < 2 )
	{
		cout << "WARNING: Try sending more than 2 messages per sender to see messages being sent in a random order\n";
	}

	thread rcv = thread( &Receiver::ProcessData, Receiver::getInstance() );

	thread threads[numberOfSenders];
	for( int i = 0; i < numberOfSenders; i++ )
	{
		threads[i] = thread( &Sender::SendData, Sender::getInstance(), i+1, numberOfMessagesPerSender );
	}

	for( auto &ths : threads )
		ths.join();
	rcv.join();


	return 0;
}
