// Simple Scheduling Simulator (node.h)
// Jan 2013
// Andrew Stanton


#ifndef NODE_H
#define NODE_H

#include <string>
#include "address.h"
#include "packet.h"
#include <map>

using namespace std;

class Node
{
public:
  //constructor
  Node ();

  //non-const
  void SetAddress (int, int, int, int, int);
  
  //const
  operator string () const;  
  uint32_t GetAddressInt () const;
  string GetAddressString () const;
  Address GetAddress () const;
  void PrintNode () const;
  void PrintChildren ( const uint32_t child_address_int = 0);
  bool IsMe ( const Node *dst ) const;
  void SendPacket ( const Packet &pck ) const;
  
private:
  //private member fns
  void ReceivePacket ( const Packet &pck ) const;
  Node *GetRouteNode ( const Address &dst ) const;
  bool IsRouteUp ( const Address &dst ) const;
  bool IsRouteDown ( const Address &dst ) const;
  void MyPacket ( const Packet &pck ) const;
  bool IsMyAddress ( const Address &addr ) const;
  void SetParent ();
  void SetMeAsChild ();
  
  //private data members
  Address m_nodeAddress;
  Node *m_myParentNode;
  map <uint32_t,Node *> m_childNodeLinkMapByAddress;    //decided to make the key a uint32_t because Address was not working well as a key for some reason, even though it worked in test program

  //static class members
  static uint32_t m_nodeIndex;
  static uint32_t m_addressByteArray[4];
  static Node *m_currentParentNode;
  static Node *m_lastParentNode;
  static Node *m_RootNode;              //this was the quick and easy way.  if I was to scale the depth, we'd have to keep track of each branch node from root
  
};

#endif /* NODE_H */