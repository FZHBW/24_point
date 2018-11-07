//
//  main.cpp
//  24ponit
//
//  Created by MacBook Pro on 2018/11/1.
//  Copyright © 2018 MacBook Pro. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

double cacu(double a, double b, int c);
void alltcacu(int *pt1 , double ***pt2);
void print(int a, int b, int c, int d, int e, int f, double *);
string its(int c);

int main() {
    //创建数组
    double ***cacuednum = new double**[9];
    for (int i = 0; i < 9; i++) {
        cacuednum[i] = new double*[9];
        for (int j = 0; j < 9; j++) cacuednum[i][j] = new double[9];
    }
    int *num = new int[5];
    //基本输出格式
    cout << "Welecome to 24_point Caculator" << endl;
    cout << "type in 4 numbers:" ;
    for(int i = 0; i<4; i++)    cin >> num[i];
    //计算
    alltcacu(num, cacuednum);
    return 0;
}

void alltcacu(int *pt1 , double ***pt2){
    int b = 0;
    int m =0, n=0;
    string fst="", sec="",fin="";
    vector<string> tempvec;
    vector<string>::iterator ite1, ite2, ite3;
    
    //所有的三个数字可能性！
    for(int i=0; i<4; i++){//第一个数字
        for(int j=i+1; j<4; j++){//第二个数字
            if(i>0) b=1;
            else b=0;
            //六种组合方法,存于第一层第一行
            for(int k=0; k<6; k++){
                pt2[i+j+b][k][0] = cacu(pt1[i], pt1[j],k );
            }
            //第三个数字
            for(int p=0; p<4; p++){
                if( p!=i && p != j){
                    for(int q = 0; q<6; q++){
                        for(int s = 0; s< 6; s++){
                            pt2[i+j+b][q][s+1] = cacu(pt1[p], pt2[i+j+b][q][0], s);
                            for(int l=0; l<6; l++){
                                if(cacu(pt2[i+j+b][q][s+1],pt1[6-p-i-j],l) == 24){
                                    m++;
                                    //第一二位数字完成输出调整
                                    if(q==4 || q==5)    fst = "("+ to_string(pt1[j]) + its(q) + to_string(pt1[i]) +")";
                                    else    fst = "("+ to_string(pt1[i]) + its(q) + to_string(pt1[j]) +")";
                                    //第三位数字完成输出调整
                                    if(s==4 || s==5)  sec = "("+ fst + its(s) + to_string(pt1[p]) + ")";
                                    else    sec = "("+ to_string(pt1[p]) + its(s) + fst + ")";
                                    //第四位数字完成输出调整
                                    if(l==4 || l==5)  fin = to_string(pt1[6-i-j-p])+its(l)+sec;
                                    else    fin = sec + its(l) + to_string(pt1[6-i-j-p]);
                                    tempvec.push_back(fin);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    for(int i=0; i<4; i++){//第一个数字
        for(int j=i+1; j<4; j++){//第二个数字
            if(i>0) b=1;
            else b=0;
            if(i+j+b>3)
                break;
            for(int p = 0; p<6; p++){
                for(int q = 0; q<6; q++){
                    for(int r = 0; r<6; r++){
                        if(cacu(pt2[i+j+b][p][0], pt2[6-i-j-b][q][0],r) == 24){
                            m++;
                            for(int s=0; s<4; s++){
                                if( s!=i && s!=j){
                                    //第一二位数字输出调整
                                    if(p==4||p==5)  fst = "(" + to_string(pt1[j]) + its(p) + to_string(pt1[i]) + ")";
                                    else    fst = "(" + to_string(pt1[i]) + its(p) + to_string(pt1[j]) + ")";
                                    //第三四位输出调整
                                    if(q==4||q==5)  sec = "(" + to_string(pt1[6-i-j-s]) + its(q) + to_string(pt1[s]) + ")";
                                    else    sec = "(" + to_string(pt1[s]) + its(q) + to_string(pt1[6-i-j-s]) + ")";
                                    //结合输出调整
                                    if(r==4||r==5)  fin = sec + its(r) + fst;
                                    else    fin = fst + its(r) + sec;
                                    tempvec.push_back(fin);
                                    //找到第三个数字即可完成s最后运算
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    n = m;ite1 = tempvec.begin();
    ite2 = (ite1++);
    ite3 = ite2;
    for(int i=0; i<m-1; i++){
        for(int j=i+1; j<m, ite2 != tempvec.end(); j++){
            ite3 = ite2;
            if((*ite1) == (*ite2)){
                tempvec.erase(ite2);
                ite2 = ite3;
                m--;
            }
            if(ite2 == tempvec.end()) break;
            else ite2++;
        }
        ite1++;
        ite2 = ite1+1;
        
    }
    ite1=tempvec.begin();
    for(int i=0; i<m; i++){
        cout << *ite1 << endl;
        ite1++;
    }
    cout << m << " ways to get 24 in total.";
    cout << "ByeBye! ";
}

double cacu(double a, double b, int c){
    switch (c) {
        case 0:
            return a+b;
            break;
        case 1:
            return a*b;
            break;
        case 2:
            return a-b;
            break;
        case 3:
            return a/b;
            break;
        case 4:
            return b-a;
            break;
        case 5:
            return b/a;
            break;
        default:
            break;
    }
    return 0;
}

string its(int c){
    switch (c) {
        case 0:
            return "+";
            break;
        case 1:
            return "*";
            break;
        case 2:
        case 4:
            return "-";
            break;
        case 3:
        case 5:
            return "/";
            break;
        default:
            break;
    }
    return 0;
}
