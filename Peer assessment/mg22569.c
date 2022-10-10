#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#define ALPHANUM 96

//create data type bool
enum bool {true, false};
typedef enum bool bool;

bool isvowel(char y);
bool isprime(char a, char b, char c);
bool correctformat(char q, char w, char e);
bool firstnlastlet(char o, char p);
void test(void);

int main(void)
{
  test();

  //create counter for list of names
  int counter = 0;

  //check if name is valid
  for (int i = 'a'; i <= 'z'; i++)
  {
    for (int j = 'a';  j <= 'z'; j++)
    {
      for (int z = 'a';  z <= 'z'; z++)
      {
        if (correctformat(i, j, z) == true && firstnlastlet(i, z) == true && isprime(i, j, z) == true)
        {
          printf("%i %c%c%c\n", ++counter, i, j, z);
        }
      } 
    }
  }
}

bool isvowel(char y)
{
  //check if the character is vowel
  if (y == 'a' || y == 'e' || y == 'i' || y == 'o' || y == 'u')
  {
    return true;
  }
  return false;
}

bool isprime(char a, char b, char c)
{
  //convert ASCII value to number of alphabet order
  int A = a - ALPHANUM, B = b - ALPHANUM, C = c - ALPHANUM;

  //sum value of three letters
  int t = A + B + C;

  //check if value is prime
  for (int j = 1; j <= t; j++)
  {
    if (t % j == 0 && j != 1 && j != t)
    {
      return false;
    }
  }
  return true;
}

bool correctformat(char q, char w, char e)
{
  //captures if name is in the right format 
  bool Q = isvowel(q);
  bool W = isvowel(w);
  bool E = isvowel(e);
  if (Q == true && W == false && E == true)
  {
    return true;
  }
  if (Q == false && W == true && E == false)
  {
    return true;
  }
  return false;
}

bool firstnlastlet(char o, char p)
{
  if (o == p)
  {
    return true;
  }
  return false;
}

void test(void)
{
  assert(isvowel('a') == true);
  assert(isvowel('b') == false);
  assert(isprime('b', 'o', 'b') == true);
  assert(isprime('a', 'b', 'a') == false);
  assert(correctformat('b', 'o', 'b') == true);
  assert(correctformat('o', 'o', 'b') == false);
  assert(firstnlastlet('o', 'o') == true);
  assert(firstnlastlet('p', 'o') == false);
}