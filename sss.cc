// Simple Scheduling Simulator (sss.cc)
// Jan 2013
// Andrew Stanton



#include <iostream>
#include <string>
//#include "sss.h"              //dont need yet
#include "node.h"
#include "address.h"
//using namespace std;          //dont need yet



//to define all router/branch nodes, we need 16777216 nodes
//to cover all root level 1, 2, and one level of 3 we need, 131072
//favorite values = 16777216, 2097152, 262144, 131072, 65536   (2^24, 2^21, 2^18, 2^17, 2^16)
#define NODE_ARRAY_SIZE 262144



void PrintNodes ( Node * );
void RouteGame ( Node * );
void PrintChildren ( Node * );
void CheckChildren ( Node * );

int
main (void) 
{
  Node *NodeArray = new Node[NODE_ARRAY_SIZE];
  int input = -1;
  while ( input != 0 )
  {
    cout << "Print Nodes (1)\n"
         << "Route Game  (2)\n"
         << "Print Children (3)\n"
         << "Check Children (4)\n"
         << "Exit (0)\n"
         << "Select: ";
    cin >> input;
    switch ( input )
    {
    case 1:
      PrintNodes ( NodeArray );
      break;
    case 2:
      RouteGame ( NodeArray );
      break;
    case 3:
      PrintChildren ( NodeArray );
      break;
    case 4:
      CheckChildren ( NodeArray );
    }
  }
  //cout << endl << endl << "Size of Node Array = " << sizeof(NodeArray) << endl;
  delete [] NodeArray;
}



void
PrintNodes ( Node *NodeArray )
{
  int i, node1, node2;
  while (1)
  {
    cout << "\nGive node range to print " << "(valid range " << 0 << "-" << NODE_ARRAY_SIZE-1 << "):: ";
    cin >> node1 >> node2;
      
    if ( node1 < 0 || node1 >= NODE_ARRAY_SIZE || node2 < 0 || node2 >= NODE_ARRAY_SIZE )
      break;

    for ( i = node1 ; i <= node2 ; i++ )
    { 
      //~ cout << NodeArray[i].GetAddressString ();
      NodeArray[i].PrintNode ();
      if ( !(i % 3) )
        cout << endl;
      else
      {
        cout << "    ";
        
      }
    }
  }
}



void
RouteGame (Node *NodeArray)
{
  while (1)
  {
    int node1;
    string msg;
    Address dstAddr;
    cout << "Give source node number, destination address, and message" << "(valid range " << 0 << "-" << NODE_ARRAY_SIZE-1 << "):: ";
    cin >> node1 >> dstAddr;
    cin >> msg; //for some reason, this needs to be on its own line
    
    if ( node1 < 0 || node1 >= NODE_ARRAY_SIZE )
      break;
    
    Packet myPck ( NodeArray[node1].GetAddress (), dstAddr , msg );
    cout << "\nForming packet and sending...!" << endl << endl << endl;
    NodeArray[node1].SendPacket ( myPck );
  }
}


void 
PrintChildren ( Node *NodeArray )
{
  int i, node1, node2;
  while (1)
  {
    cout << "\nGive node range to print with children " << "(valid range " << 0 << "-" << NODE_ARRAY_SIZE-1 << "):: ";
    cin >> node1 >> node2;
      
    if ( node1 < 0 || node1 >= NODE_ARRAY_SIZE || node2 < 0 || node2 >= NODE_ARRAY_SIZE )
      break;

    for ( i = node1 ; i <= node2 ; i++ )
    { 
      NodeArray[i].PrintNode ();
      cout << endl;
      NodeArray[i].PrintChildren ();
    }
    
  }
 
}

void 
CheckChildren ( Node *NodeArray )
{
  int node1;
  Address testAddr;
  while (1)
  {
    cout << "\nGive node number and child address to see if it is a child " << "(valid node " << 0 << "-" << NODE_ARRAY_SIZE-1 << "):: ";
    cin >> node1 >> testAddr;
  
    if ( node1 < 0 || node1 >= NODE_ARRAY_SIZE )
      break;  
      
    cout << "I got node = " << node1 << " and addr = " << testAddr.GetString () << endl;
 
    NodeArray[node1].PrintChildren ( testAddr.GetInt () ); 
  }
}