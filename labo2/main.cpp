
#include "taller.h"
using namespace std;

int main()
{

    vector<int> v{1, 2, 3, 4, 5, 6};
    cout << "El vector principal es: " << endl;
    for (int a = 0; a < v.size(); a++)
    {
        cout << v[a];
    }
    printf("\n");
    printf("\n");
    cout << "El numero mayor es "<< mayor(v) << endl;
    printf("\n");
    cout << "El vector inverso es; "<< endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << reverso(v)[i];
    }
    printf("\n");
    printf("\n");
    cout << "El vector rotado 3 veces es: "<< endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << rotar(v, 3)[i];
    }
    printf("\n");
    printf("\n");
    // cout << "Hacer test en el main" << endl;
    return 0;
}
