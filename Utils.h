#ifndef OCTOPUS_GAMES_UTILS_H
#define OCTOPUS_GAMES_UTILS_H

#define MAX(l,r) ((l) < (r) ? (r) : (l))

//#include "PlayerInGroup.h"

namespace WET1 {
    class Utils {
    public:

//        template<class T>
//        static T* mergeArrays(const T* arr1, const T* arr2, int size1, int size2){
//            T* arr_merge = new T[size1 + size2];
//
//            int idx1 = 0, idx2 = 0, idx3 = 0;
//            while(idx1 < size1 && idx2 < size2){
//                if(arr1[idx1] < arr2[idx2]){
//                    arr_merge[idx3++] = arr1[idx1++];
//                }
//                else {
//                    arr_merge[idx3++] = arr2[idx2++];
//                }
//            }
//            while(idx1 < size1){
//                arr_merge[idx3++] = arr1[idx1++];
//            }
//            while(idx2 < size2){
//                arr_merge[idx3++] = arr2[idx2++];
//            }
//
//            return arr_merge;
//        }

        template<class K, class T>
        static void mergeArrays(K dest_arr_K[], T dest_arr_T[], K arr1_K[], T arr1_T[], K arr2_K[], T arr2_T[], int size1, int size2){
            int idx1 = 0, idx2 = 0, idx3 = 0;
            while(idx1 < size1 && idx2 < size2){
                if(arr1_K[idx1] < arr2_K[idx2]){
                    dest_arr_K[idx3] = arr1_K[idx1];
                    dest_arr_T[idx3++] = arr1_T[idx1++];
                }
                else {
                    dest_arr_K[idx3] = arr2_K[idx2];
                    dest_arr_T[idx3++] = arr2_T[idx2++];
                }
            }
            while(idx1 < size1){
                dest_arr_K[idx3] = arr1_K[idx1];
                dest_arr_T[idx3++] = arr1_T[idx1++];
            }
            while(idx2 < size2){
                dest_arr_K[idx3] = arr2_K[idx2];
                dest_arr_T[idx3++] = arr2_T[idx2++];
            }
        }
    };
}


#endif //OCTOPUS_GAMES_UTILS_H
