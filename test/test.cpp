/*********************************************
* @Author       : Elendeer
* @Date         : 2020-06-11 17:19:57
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-09-19 16:39:07
* @Description  :
*********************************************/
#include <iostream>
#include <vector>


using namespace std;

int main() {
    vector<int> a = {1, 2 ,3 };

    a.erase(a.begin() + 1);

    for (int i : a) {
        cout << i << " ";
    }
    cout << endl << a.size() << endl;

    return 0;
}