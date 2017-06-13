/**
    * Code by Aniket Chowdhury
    * aniket_chowdhury@hotmail.com
    * github.com/aniket-chowdhury
    *
    * Time Complexity : theta(log n)'
    *
    * #Example 3^5->5-1=4,3*1=3->(3*3)*(3*3)=81*3=283
*/

#include <iostream>

using namespace std;

uint64_t exponent(int x, int n)
{
    int m=n;
    int64_t z=x, power=1;
    while(m>0)
    {
        while(m%2==0)
        {
            m=m/2;
            z=z*z;
        }
        m=m-1;
        power*=z;
    }
    return power;
}

int main()
{
    int x, n;
    cin>>x>>n;
    cout<<exponent(x,n);
}
