#include "Sender.h"
#include "Receiver.h"

Sender *Sender::m_sender = NULL;

void Sender::SetNumberOfSenders( int no )
{
	numberOfSenders = no;
}

void Sender::SendData( int sender_id )
{
        unique_lock<mutex> lck(m_senderMtx);
        m_senderCv.wait(lck);

	string message = to_string( sender_id ) + "abcde";
        cout << "Sender_" << sender_id << " sending data: " << message << "\n";
	m_buffer->writeData( message, sender_id );

	--numberOfSenders;
	if( !numberOfSenders )
		Receiver::getInstance()->StartProcessing();

	m_senderCv.notify_all();
}

void Sender::StartAllSenders()
{
	m_senderCv.notify_all();
}
