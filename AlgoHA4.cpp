#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
vector<int> pref_suf(string str){int n = str.size();vector<int> result(n);int count = 0;result[0] = 0;int i=1;
    while (i < n) {
        if (str[i] == str[count]) {
            count++;
            result[i] = count;
            i++;}
        else {
            if (count != 0)
                count = result[count - 1];
            else {
                result[i] = 0;
                i++;}}}
    return result;
}
void intresting_str(string str){vector<int> result = pref_suf(str);int n = str.size();
    if (result[n - 1] == 0) {
        cout << -1<<endl;
        return;}
    for (int i = 0; i < n - 1; i++) {
        if (result[i] == result[n - 1]) {
            cout << str.substr(0, result[i])<<endl;
            return;}}
    if (result[result[n - 1] - 1] == 0)
        cout << -1<<endl;
    else
        cout << str.substr(0, result[result[n - 1] - 1])<<endl;
}
 
int main()
{
    string str ;
    cin>>str;
    intresting_str(str);
 
    return 0;
}

