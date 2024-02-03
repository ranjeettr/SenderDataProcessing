#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>
#include <vector>
#include <unistd.h>
#include "Sender.h"
#include "Receiver.h"

using namespace std;

int main()
{
	int numberOfSenders = 0;
	cout << "How many senders you want to create: ";
	cin >> numberOfSenders;
	Sender::getInstance()->SetNumberOfSenders( numberOfSenders );

	thread threads[numberOfSenders];

	for( int i = 0; i < numberOfSenders; i++ )
	{
		threads[i] = thread( &Sender::SendData, Sender::getInstance(), i+1 );
	}

	thread rcv = thread( &Receiver::ProcessData, Receiver::getInstance() );

	Sender::getInstance()->StartAllSenders();

	for( auto &ths : threads )
		ths.join();
	rcv.join();


	return 0;
}
