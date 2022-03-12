// Simple Scheduling Simulator (address.h)
// Jan 2013
// Andrew Stanton


#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <stdint.h>
using namespace std;

class Address
{
public:
  //constructors
  Address (int = 0, int = 0 , int = 0, int = 0, int = 0);
  Address (const Address & );
  
  //non-const
  void Set (int, int, int, int, int); 
  friend ostream &operator<<( ostream &, const Address & );
  friend istream &operator>>( istream &, Address & );
  
  //const
  //const Address &operator= ( Address &);
  bool operator> (const Address &) const;
  bool operator< (const Address &) const;
  bool operator== (const Address &) const;
  bool operator!= (const Address &) const;
  operator uint32_t () const;
  uint32_t GetInt () const;
  string GetString () const;
  uint8_t GetSubnet () const;
  void Print () const;
  void DecrementSubnet ();
private:
  //void SetAddressByte ( int, int );
  
  uint8_t m_octetArray[4];
  uint32_t m_Address;
  uint8_t m_subnet;
  
  
};

#endif /* ADDRESS_H */