// #include "BinaryTree.hpp"
// using namespace std;
// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// //#pragma once

// int main(){
   
//     /* this is the tree1
//           1
//         /   \
//        3     2
//       / \    / \
//      7   6  5   4
// */ 
// ariel::BinaryTree<int> tree;
//     // add to root child
//     tree.add_root(1);
//     tree.add_right(1,2);
//     tree.add_left(1,3);
//     // add to right child
//     tree.add_right(2,4);
//     tree.add_left(2,5);
//     // add to left child 
//     tree.add_right(3,6);
//     tree.add_left(3,7);
//     cout<<tree<<endl;

//     // cheng lef 

//     tree.add_left(3,9);
//     tree.add_right(2,4);
//     cout<<tree<<endl;

//             /* this is the tree1
//                 5
//               /   \
//              4     2
//             / \    / \
//            8   1  23   44
//         */ 
//         ariel::BinaryTree<int> tree2;
//         tree2.add_root(5);
//         tree2.add_right(5,2);
//         tree2.add_left(5,4);
//         tree2.add_right(4,1);
//         tree2.add_left(4,8);
//         tree2.add_right(2,44);
//         tree2.add_left(2,23);
//         cout<<"print tree 2 "<<endl;
//         cout<<tree2<<endl;

        
//         //------------------------- stl -------------------------
//         std::swap(tree,tree2);
//         cout<<"print tree 1 "<<endl;
//         cout<<tree<<endl;
//         cout<<"print tree 2 "<<endl;
//         cout<<tree2<<endl;
//         ariel::BinaryTree<int> p=tree2;
//         cout<<p<<endl;
//         std::replace (p.begin(), p.end(), 5, 99);
//         cout<<p<<endl;

//       vector<int> myvector;
//     for (auto it=tree2.begin_preorder(); it!=tree2.end_preorder(); ++it) {
//         myvector.push_back(*it);
//     }
//           vector<int> myvector2;
//     for (auto it=tree2.begin_inorder(); it!=tree2.end_inorder(); ++it) {
//         myvector2.push_back(*it);
//     }
//     for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
//         std::cout << ' ' << *it;
//       std::cout << '\n';
      
//   std::vector<int>::iterator it;

//   it = find (myvector.begin(), myvector.end(), 30);
//   if (it != myvector.end())
//     std::cout << "Element found in myvector: " << *it << '\n';
//   else
//     std::cout << "Element not found in myvector\n";

//   std::cout << '\n';
//       it = find (myvector.begin(), myvector.end(), 5);
//   if (it != myvector.end())
//     std::cout << "Element found in myvector: " << *it << '\n';
//   else
//     std::cout << "Element not found in myvector\n";

// //------------------------- opertor == and !=   -------------------------
//         int arrPre[]={1,3,9,6,2,5,4};
//         int arrNot[]={8,7,6,5,1,3,4};
//         int i=0;
//       for (auto it=tree2.begin_preorder(); it!=tree2.end_preorder(); ++it) {
//         if((*it)==arrPre[i]){cout<<"good"<<endl;}
//         else{cout<<"no good"<<endl;}
//         i++;
//     }
//     std::cout << '\n';
//     i=0;
//       for (auto it=tree2.begin_preorder(); it!=tree2.end_preorder(); ++it) {
//         if((*it)==arrNot[i]){cout<<"good"<<endl;}
//         else{cout<<"no good"<<endl;}
//         i++;
//     }
//     std::cout << '\n';

//       //change
//         tree2.add_root(12);
//         tree2.add_left(12,88);
//         tree2.add_left(2,3);
//         tree2.add_left(3,133);
//         cout<<tree2<<endl;
// }