// map practice with my objects from sss
// Feb 2013
// Andrew Stanton



#include <iostream>
#include <string>
//#include "sss.h"              //dont need yet
#include "node.h"
#include "address.h"
//using namespace std;          //dont need yet



int
main ( void )
{
  Node *NodeArray = new Node[32];
  map <Address,Node *> nodeMap;
  //std::map<Address,Node *>::iterator it;

  
  Address addr1 ( 0, 0, 0, 0, 0 );
  nodeMap[addr1] = &NodeArray[0];
  addr1.Set ( 0, 0, 1, 0, 3 );
  nodeMap[addr1] = &NodeArray[1];
  addr1.Set ( 0, 0, 2, 0, 3 );
  nodeMap[addr1] = &NodeArray[2];
  addr1.Set ( 0, 0, 3, 0, 3 );
  nodeMap[addr1] = &NodeArray[3];
  addr1.Set ( 0, 0, 4, 0, 3 );
  nodeMap[addr1] = &NodeArray[4];
  addr1.Set ( 0, 0, 5, 0, 3 );
  nodeMap[addr1] = &NodeArray[5];
  
 for (std::map<Address,Node *>::iterator it=nodeMap.begin(); it!=nodeMap.end(); ++it)
    std::cout << it->first.GetString () << " => " << it->second->GetAddressString () << '\n';
    
  //for ( int i = 0 ; i < nodeMap.size () ; i++ )
    //cout << nodeMap[i]->GetAddressString () << endl;
    
  //it = nodeMap.find( addr1 );
  //cout << it->second->GetAddressString () << endl;
  
  //cout << nodeMap[addr1]->GetAddressString () << endl;

}

