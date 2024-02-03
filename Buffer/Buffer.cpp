#include "Buffer.h"

Buffer *Buffer::m_bufferInstance = NULL;

bool Buffer::writeData( string &message, int sender_id )
{
	unique_lock<mutex>( dataMtx );

        map<int, vector<string>>::iterator it = m_buffer.find( sender_id );
        if( it != m_buffer.end() )
        {
                it->second.push_back( message );
        }
        else
        {
                vector<string> str;
                str.push_back( message );
                m_buffer.insert( pair<int, vector<string>>( sender_id, str ) );
        }

	return true;
}


bool Buffer::readData( string &message )
{
	unique_lock<mutex>( dataMtx );

	if( m_buffer.empty() )
		return false;

	map<int, vector<string>>::iterator it = m_buffer.begin();
	if( !( it->second.empty() ) )
	{
		vector<string>::iterator itstr = it->second.begin();
		message = *itstr;
		it->second.erase( itstr );
		if( it->second.empty() )
			m_buffer.erase( it );
	}

	return true;
}
