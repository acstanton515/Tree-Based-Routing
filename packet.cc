// Simple Scheduling Simulator (packet.cc)
// Jan 2013
// Andrew Stanton



#include "packet.h"



Packet::Packet (Address src, Address dst, string msg)
{
  SetMessage ( msg );
  SetSource ( src );
  SetDestination ( dst );
}



void 
Packet::SetMessage ( string msg )
{
  m_message = msg;
}



void 
Packet::SetSource ( Address src )
{
  m_source = src;
}



void 
Packet::SetDestination ( Address dst )
{
  m_destination = dst;
}



Address 
Packet::GetSource () const
{
  return m_source;
}



Address 
Packet::GetDestination () const
{
  return m_destination;
}



string 
Packet::GetMessage () const
{
  return m_message;
}