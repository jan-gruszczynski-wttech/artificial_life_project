#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;


vector<int> permutateList(vector<int> list_to_permutate) {

    auto vector_len = list_to_permutate.size();

    for (auto i = vector_len; i > 0; i--) {
        int rand_val = rand() % i;
//        cout<<rand_val<<endl;
//        cout<<i<<endl;
//        cout<<endl;
        swap(list_to_permutate[i-1],list_to_permutate[rand_val]);
//        list_to_permutate[i] = list_to_permutate[rand_val]
//        cout << rand_val << "\n";
    }
//    for (auto i: list_to_permutate)
//        std::cout << i << ' ';


//    cout << rand_val;


    return list_to_permutate;
}


int main() {
    srand(time(nullptr));

    std::cout << "Hello, World!" << std::endl;
//    srand(time(0));
//    int rand_val = rand() % 10;
//    cout<<rand_val;
    vector<int> solution = {1,2,3,4,5};
    permutateList(solution);

    return 0;
}
