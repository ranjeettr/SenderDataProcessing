#include "Receiver.h"

Receiver *Receiver::m_receiver = NULL;

void Receiver::ProcessData()
{
	unique_lock<mutex> lck( m_receiverMtx );
	m_receiverCv.wait( lck );

	string message;

	while(1)
	{
		if( !m_buffer->readData( message ) )
			break;

		cout << "Processing data: " << message << "\n";
	}
}

void Receiver::StartProcessing()
{
	m_receiverCv.notify_all();
}
