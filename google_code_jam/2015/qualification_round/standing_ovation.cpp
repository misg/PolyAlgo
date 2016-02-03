#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++)
    {
        int max_shyness;
        cin >> max_shyness;
        
        int standing = 0;
        int friends  = 0;

        for (int shyness = 0; shyness < max_shyness + 1; shyness++)
        {
            char n_people_c;
            cin >> n_people_c;

            int n_people = n_people_c - '0';
            
            if (shyness <= standing)
                standing += n_people;
            else
            {
                friends  += shyness - standing;
                standing += (shyness - standing) + n_people;
            }
        }

        cout << "Case #" << i + 1 << ": " << friends << endl;
    }
}
