#include <iostream>

using namespace std;


void plusAndMinus(int n)
{
  for (int i = 0; i < n; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      if(i%2==0)
      {
        cout<<"+";
      }
      else
      {
        cout<<"-";
      }
    }
    cout << endl;
  }
}




int main() {



    return 0;
}