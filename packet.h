// Simple Scheduling Simulator (packet.h)
// Jan 2013
// Andrew Stanton



#ifndef PACKET_H
#define PACKET_H

#include <string>
#include "address.h"



class Packet
{
public:

  //constructor
  Packet(Address, Address, string);
  
  //non-const
  void SetMessage ( string msg );
  void SetSource ( Address src );
  void SetDestination ( Address dst );
  
  //const
  Address GetSource () const;                 //same issue here as in node.cc --> do I make redundant fn calls or do I make the members public!!!
  Address GetDestination () const;
  string GetMessage () const;
private:
  //private data members
  Address m_source;
  Address m_destination;
  string m_message;
  
};

#endif /* PACKET_H */