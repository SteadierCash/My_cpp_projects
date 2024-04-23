#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    int max_n = 0;
    int n;
    for (int i = 0; i < 4; i++)
    {   
        cout << "podaje liczbe: ";
        cin >> n ;

        if (n > max_n)
            max_n = n;
    }
    cout << "max: " << max_n << endl;
    return 0;
}
// int main()
// {
//     int n;
//     cout << "number: "
//     cin >> n;
//     if (n % 6 == 0)
//         cout << "div by 6" << endl;
//     else if (n % 2 == 0)
//         cout << "div by 2" << endl;
//     else if (n % 3 == 0)
//         cout << "div by 3" << endl;

//     return 0;
// }


// int main()
// {
//     int mark;
//     cout << "mark: ";
//     cin >> mark;

//     switch (mark)
//     {
//         case 2:  cout << "you shall not pass" <<endl; break;
//         case 3:     
//         case 4:  
//         case 5:  cout << "passed" <<endl; break;
//         default: cout << "wrong mark" <<endl; break; 
//     }

//     return 0;
// }
// int main()
// {
//     int mark;
//     cout << "mark: ";
//     cin >> mark;

//     switch (mark)
//     {
//         case 2:  cout << "ndst"       <<endl; break;
//         case 3:  cout << "dost"       <<endl; break;    
//         case 4:  cout << "dobry"      <<endl; break;
//         case 5:  cout << "bd"         <<endl; break;
//         default: cout << "wrong mark" <<endl; break; 
//     }

//     return 0;
// }

// int main()
// {
//     string col;
//     cout << "Color: "; 
//     cin >> col;

//     if (col == "red")
//         cout << "it is red" << endl;
    
//     return 0; 
// }

// int main()
// {
//     int a;
//     cout << "Temperature: "; 
//     scanf("%d", &a);

//     if (a < 0)
//         cout << "Cold" << endl;
    
//     return 0; 
// }