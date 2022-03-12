// Simple Scheduling Simulator (address.cc)
// Jan 2013
// Andrew Stanton



#include <iostream>  
#include "address.h"
#include <stdio.h>
using namespace std;



Address::Address (int o1, int o2, int o3, int o4, int subnet) 
{
  Set (o1, o2, o3, o4, subnet);
}   



Address::Address ( const Address & addressToCopy)
{
  m_octetArray[0] = addressToCopy.m_octetArray[0];
  m_octetArray[1] = addressToCopy.m_octetArray[1];
  m_octetArray[2] = addressToCopy.m_octetArray[2];
  m_octetArray[3] = addressToCopy.m_octetArray[3];
  m_Address = addressToCopy.m_Address;
  m_subnet = addressToCopy.m_subnet;
}



void 
Address::Set (int o1, int o2, int o3, int o4, int subnet) 
{
  //Assume o1-o4 are safe or go learn Exceptions!
  m_Address = o1*16777216 + o2*65536 + o3*256 + o4;
  m_octetArray[0] = o1;
  m_octetArray[1] = o2;
  m_octetArray[2] = o3;
  m_octetArray[3] = o4;
  m_subnet = subnet;    //assume safe number (0-3) or go learn Exceptions!
}           



ostream
&operator<<( ostream &output, const Address &addr )
{
  //addr.Print ();      //tried to call this function to make it easy, but it didnt work I think
  //string        period = ".";
  //output << addr.m_octetArray[0] << period << addr.m_octetArray[1] << period << addr.m_octetArray[2] << period << addr.m_octetArray[3] << "\\" << addr.m_subnet;
}



istream 
&operator>>( istream &input, Address &addr ) 
{
  int o1, o2, o3, o4, subnet;
  input >> o1;             //need extra checks here!!!
  input.ignore ();
  input >> o2;
  input.ignore ();  
  input >> o3;
  input.ignore (); 
  input >> o4;
  input.ignore ();  
  input >> subnet;
  addr.Set (o1, o2, o3, o4, subnet);
}



 //~ const Address &
 //~ Address::operator= ( Address &right)
//~ {
  //~ if ( &right != this )
    //~ Set ( right.m_octetArray[0]. right.m_octetArray[1], right.m_octetArray[2], right.m_octetArray[3], right.m_subnet );
  //~ return *this;
//~ }


//greater than being true means down route
// don't focus on the concept of greater/higher or lesser/lower, rather it is up or down
// it can be higher if the dst is toward the root without having to descend else where
// it can be lower if the dst is down your stem or branches
bool 
Address::operator> (const Address &right) const
{
  int i;
  for (i = 0 ; i < m_subnet ; i++)
  {
    if (m_octetArray[i] != right.m_octetArray[i]) return false;
  }
  return true;
}



//less than means up route
bool 
Address::operator< (const Address &right) const
{
 return ! (*this > right);
}



//easy equality operation
bool 
Address::operator== (const Address &right) const
{
  int i;
  for (i = 0 ; i < 4 ; i++)
  {
    if (m_octetArray[i] != right.m_octetArray[i]) return false;
  }
  return true; 
}



bool 
Address::operator!= (const Address &right) const
{
  return ! (*this == right);
}



Address::operator uint32_t () const
{
  return m_Address;
}



uint32_t 
Address::GetInt () const
{
  return m_Address;
}



string
Address::GetString () const
{
  string strAddress;
  string period = ".";
  char temp[4];
  
  snprintf(temp, 4, "%u", m_octetArray[0]);
  strAddress = temp;
  strAddress += period;
  
  snprintf(temp, 4, "%u", m_octetArray[1]);
  strAddress += temp;
  strAddress += period;
   
  snprintf(temp, 4, "%u", m_octetArray[2]);
  strAddress += temp;
  strAddress += period;
   
  snprintf(temp, 4, "%u", m_octetArray[3]);
  strAddress += temp;
  
  snprintf(temp, 4, "%u", m_subnet);
  strAddress += "\\";
  strAddress += temp;
  
  return strAddress;
}



uint8_t 
Address::GetSubnet () const
{
  return m_subnet;
}



void
Address::Print () const
{
  string        period = ".";
  cout << m_octetArray[0] << period << m_octetArray[1] << period << m_octetArray[2] << period << m_octetArray[3] << "\\" << m_subnet;
}



void
Address::DecrementSubnet ()
{
  if ( m_subnet > 0 )
    m_subnet--;
    

  if ( m_subnet == 0 )
    Set ( 0, 0, 0, 0, 0 );
  else if ( m_subnet == 1 )
    Set ( m_octetArray[0], 0, 0, 0, 1 );
  else if ( m_subnet == 2 )
    Set ( m_octetArray[0], m_octetArray[1], 0, 0, 2 );
  else if ( m_subnet == 3 )
    Set ( m_octetArray[0], m_octetArray[1], m_octetArray[2], 0, 3 ); 
}