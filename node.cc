// Simple Scheduling Simulator (node.cc)
// Jan 2013
// Andrew Stanton



#include <iostream>
#include "node.h"
//#include <string>
//using namespace std;
//#include "tips.cc"



uint32_t Node::m_nodeIndex = 0;
uint32_t Node::m_addressByteArray[4] = { -1 , -1, -1, 0 };
Node *Node::m_currentParentNode = 0;
Node *Node::m_lastParentNode = 0;
Node *Node::m_RootNode = 0;



Node::Node () 
{            
  int subnet = 0;
  {
    static int32_t expireParentCounter = -1;
    if ( (expireParentCounter%256) == 0 )
      if ( (expireParentCounter%65536) == 0 )
        m_currentParentNode = m_RootNode;
      else
        m_currentParentNode = m_lastParentNode;
    else if ( expireParentCounter == -1 ) {
      m_RootNode = m_lastParentNode = m_currentParentNode = this;                  //initialized root node as lastParent and currentParent
      expireParentCounter = 0;
    }
    SetParent ();
    if ( (expireParentCounter%65536) == 0 )
      m_currentParentNode = this;
    expireParentCounter++;
  }
  
  m_addressByteArray[2] = (m_addressByteArray[2] + 1) % 256;
  //m_currentParentNode = this;                //only if we create end nodes/ non-router nodes
  
  if ( !(m_nodeIndex % 256) ) {
    m_addressByteArray[1] = (m_addressByteArray[1] + 1) % 256;  
    m_lastParentNode = m_currentParentNode;
    m_currentParentNode = this;
  }
  
  if ( !(m_nodeIndex % (256*256)) ) {
    m_addressByteArray[0] = (m_addressByteArray[0] + 1) % 256;
  }

  if ( m_addressByteArray[2] != 0 )  //should the assigning of a subnet be handled in address.cc????
    subnet = 3;
  else if ( m_addressByteArray[1] != 0 )     //it could be given here, if for the purpose, of having a concept of dynamically assigned subnets
    subnet = 2;
  else if ( m_addressByteArray[0] != 0 )
    subnet = 1;
  else
    subnet = 0;
  
  SetAddress (m_addressByteArray[0], m_addressByteArray[1], m_addressByteArray[2], m_addressByteArray[3], subnet);
  SetMeAsChild ();
  
  m_nodeIndex++;
}



void 
Node::SetAddress (int o1, int o2, int o3, int o4, int subnet) 
{
  m_nodeAddress.Set( o1, o2, o3, o4, subnet );
}



Node::operator string () const
{
  return GetAddressString ();
}



uint32_t 
Node::GetAddressInt () const
{
  return m_nodeAddress.GetInt();
}



string 
Node::GetAddressString () const
{
  return m_nodeAddress.GetString();
}



Address 
Node::GetAddress () const
{
  return m_nodeAddress;
}



void 
Node::PrintNode () const
{
  cout << "Node: " << GetAddressString () << "  Parent: " << m_myParentNode->GetAddressString ();
  //tips::print( m_childNodeLinkMapByAddress, "Child Node Map:\n     ", "\n     ");
}



//print "all" children or print a single child if it exists
//printing for all children started working once changed map value to unit
//when checking for a child, it does not check subnet to see if subnet is the same
void 
Node::PrintChildren ( const uint32_t child_address_int ) 
{
  int i;
  map<uint32_t,Node *>::iterator it;

  if ( m_childNodeLinkMapByAddress.empty () )
    cout << "          No Children!\n";
  else if ( child_address_int != 0 )
  {
    if ( m_childNodeLinkMapByAddress.find ( child_address_int ) != m_childNodeLinkMapByAddress.end () )         
      cout << "          Child Exists! Address = " << m_childNodeLinkMapByAddress.find ( child_address_int )->second->GetAddressString () << endl ;
    else
      cout << "          Child Does Not Exist!" << endl;
  }
  else
  {
    cout << "          Number of Children: " << m_childNodeLinkMapByAddress.size () << endl;
    for (it = m_childNodeLinkMapByAddress.begin () ; it != m_childNodeLinkMapByAddress.end () ; ++it)
      cout << "          " << it->first << " => " << it->second->GetAddressString () << '\n';
  }
}



bool 
Node::IsMe ( const Node *dst ) const
{
  return m_nodeAddress == dst->m_nodeAddress;
}



void 
Node::SendPacket ( const Packet &pck ) const
{
  Node *nextNode;
  if ( IsMyAddress ( pck.GetDestination () ) )
    MyPacket ( pck );
  else
  {
    nextNode = GetRouteNode ( pck.GetDestination () );
    if ( nextNode != 0 )
    {
      cout << GetAddressString () << " is sending pck to " << nextNode->GetAddressString () << endl;
      nextNode->ReceivePacket ( pck );
    }
    else
    {
      cout << GetAddressString () << " has no route for this node! " << endl;
      //delete the packet???
    }
  }
}



void 
Node::ReceivePacket ( const Packet &pck ) const
{
  if ( IsMyAddress ( pck.GetDestination () ) )
    MyPacket ( pck );
  else
    SendPacket ( pck );
}



Node * 
Node::GetRouteNode ( const Address &dst ) const
{
  if ( IsRouteUp ( dst ) )
    return m_myParentNode;      //route up to parent
  else
  {
    if ( m_childNodeLinkMapByAddress.find ( dst.GetInt () ) != m_childNodeLinkMapByAddress.end () )  // dst is a child of mine
      return m_childNodeLinkMapByAddress.find ( dst.GetInt () )->second;
    else
    {
      Address possibleChildAddress (dst);
      do
      {
      possibleChildAddress.DecrementSubnet ();
      if ( m_childNodeLinkMapByAddress.find ( possibleChildAddress.GetInt () ) != m_childNodeLinkMapByAddress.end () )
        return m_childNodeLinkMapByAddress.find ( possibleChildAddress.GetInt () )->second;     //dst is a child of one of my children
      } while ( possibleChildAddress.GetSubnet () > m_nodeAddress.GetSubnet () );
      //else (if we dont return in the while, there is no hope of routing)
        return 0; //no route!!!
    }
  }
}



void 
Node::MyPacket ( const Packet &pck ) const
{
  cout << GetAddressString () << " got his packet.  Src: " << pck.GetSource ().GetString () << " Dst: " << pck.GetDestination ().GetString () << " Message: " << pck.GetMessage () << endl;
}



bool 
Node::IsMyAddress ( const Address &dst ) const
{
  return m_nodeAddress == dst;
}



bool 
Node::IsRouteUp ( const Address &dst ) const
{
  return m_nodeAddress < dst;
}



bool 
Node::IsRouteDown ( const Address &dst ) const
{
  return m_nodeAddress > dst;
}



void 
Node::SetParent ()
{
  m_myParentNode = m_currentParentNode;
}



void 
Node::SetMeAsChild ()
{
  if ( m_myParentNode != this )
  {
    m_myParentNode->m_childNodeLinkMapByAddress[m_nodeAddress.GetInt ()] = this;
    
    //cout << "Added Child " << m_myParentNode->m_childNodeLinkMapByAddress[m_nodeAddress.GetInt ()]->GetAddressString () << " to Parent " << m_myParentNode->GetAddressString () << endl;
  }
  //for ( int i = 0 ; i < 16777216 ; i++ );
}

