#include "Sender.h"
#include "Receiver.h"

Sender *Sender::m_sender = NULL;

void Sender::SetNumberOfSenders( int no )
{
	numberOfSenders = no;
}

string generateRandomString( int len )
{
	const char alphnum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string tmp;

	for( int i = 0; i < len; i++ )
	{
		tmp += alphnum[ rand() % ( sizeof( alphnum ) - 1 ) ];
	}
	return tmp;
}

void Sender::SendData( int sender_id, int numberOfMessages )
{
	while( numberOfMessages-- )
	{
		string message = to_string( sender_id ) + generateRandomString(5);
        	cout << "Sender_" << sender_id << " sending data: " << message << "\n";
		m_buffer->writeData( message, sender_id );
	}

	{
        	unique_lock<mutex> lck(m_senderMtx);
		--numberOfSenders;
		if( !numberOfSenders )
			Receiver::getInstance()->StartProcessing();
	}
}
