//
//  main.cpp
//  HuffmanTree
//
//  Created by 王 瑞 on 12-12-11.
//  Copyright (c) 2012年 王 瑞. All rights reserved.
//
//CASTCASTSATATATASA
// 0111010110110


#include <iostream>
#include <string.h>
using namespace std;

//定义huffman树的结点，我加入code,和s，是为了在叶子上储存叶子对应的字母和字母的编码，方便输出
typedef struct {
    float weight;
    int lChild,rChild,parent;
    char code;
    char s[5];
}HTNode;

typedef HTNode HuffmanTree;

int codeNum;
int m;
char keyAndCode[4][10];
static int tht=0;

//create huffman tree
void CreateHuffmanTree(HuffmanTree T[],float fr[],int n,char b[]);

//遍历huffman tree，给特定字母编码
int  PreList(HuffmanTree T[],int layer,char a[],char b,char key[]);

//将输入的长串字母编程1和0的编码
int  search(char a,HuffmanTree T[],int layer,char temp[],int f);

//将输入的1和0的编码变成字母，即解码(encode)
int decoded(char decode[],int num,HuffmanTree T[],int layer);

/*
 
 注明：本人构造的huffman树和ppt给的示例并不相同，因此编码和解码也不相同
 

 */


int main(int argc, const char * argv[])
{
    char a[20];
    char b[20];
    int i,j;
    bool flag=false;
    int numForGetIn=0;
    char decode[30];
    cout<<"请输入需要编码的字符串:"<<endl;
    cin>>a;
    
    //提取输入字符的最小字符集，存入b[]中
    for (i=0; a[i]!='\0'; i++) {
        j=0;
        while (b[j]!='\0') {
        
        if (a[i]==b[j]) {
            flag=true;
        }
            j++;
        }
        if (flag==false) {
            b[numForGetIn]=a[i];
            numForGetIn++;
        }
    }
        b[numForGetIn]='\0';
    //获取b[]中的字符数
 
    for(j=0 ;b[j]!='\0' ; j++) {
    }

    int numOfB=j;
    float weightForChar[j];
    int numForEachChar=0;
    //分析每个b组中的字符出现的次数，即huffman树的权重
    for(j=0;b[j]!='\0';j++){
    for (i=0; a[i]!='\0'; i++) {
        if (b[j]==a[i]) {
            numForEachChar++;
        }
    }
        weightForChar[j]=numForEachChar;
        numForEachChar=0;
    }
    //cout<<b<<endl;
    //cout<<weightForChar[0]<<endl<<weightForChar[1]<<endl<<weightForChar[2]<<endl<<weightForChar[3]<<endl;
    //cout<<j<<endl;
    
    //huffman Tree Constructor
    //const int n=20;
     m=numOfB*2-1;
    codeNum=numOfB;
    
    HuffmanTree T[10];

    
    char codeForNode[m];
    CreateHuffmanTree(T,weightForChar,numOfB,b);
    PreList(T, m-1, codeForNode, '\0',b);
    
    char result[1024];
    for (i=0; i<1024; i++) {
        result[i]='\0';
    }
    i=0;
   
    while(a[i]!='\0'){
        search(a[i], T, 6, result,0);
        i++;
   
        
    }
    cout<<endl;
    cout<<tht<<endl;
   
    
    
    cout<<"请输入需要解码的二进制字符串:"<<endl;
    cin>>decode;
    
    decoded(decode, 0, T, 6);
    cout<<endl;
    
    
    
//    for (i=0; i<numOfB*2-1; i++) {
//        cout<<T[i].weight<<" "<<T[i].parent<<" "<<T[i].lChild<<" "<<T[i].rChild<<" "<<T[i].code<<" "<<T[i].s<<endl;
//    }
//    
    
//    
//    for (int i=0; i<numOfB; i++) {
//        cout<<keyAndCode[i]<<endl;
//    }
//    
    
    return 0;
}

//构造huffman树 

void CreateHuffmanTree(HuffmanTree T[],float fr[],int n,char b[]){

    for (int i=0; i<n; i++) {
        T[i].weight=fr[i];
        T[i].code=b[i];
    }
    for (int i=0; i<2*n-1;i++) {
        T[i].lChild=-1;
        T[i].rChild=-1;
        T[i].parent=-1;
      
       
    }
    for (int i=n; i<2*n-1; i++) {
        T[i].weight=-1;
        T[i].code='\0';
    }
    
   
    
    for (int i=n; i<2*n-1; i++) {
        int min1=10000,min2=10000;
        int pos1 = 0,pos2;
        for (int j=0; j<i; j++) {
            if (T[j].parent==-1) {
                if (T[j].weight<min1) {
                    pos2=pos1;
                    pos1=j;
                    min1=T[j].weight;
                }else if (T[j].weight<min2){
                    pos2=j;
                    min2=T[j].weight;
                }
            }
        }
        T[i].weight=T[pos1].weight+T[pos2].weight;
        T[i].lChild=pos1;
        T[i].rChild=pos2;
        T[pos1].parent=T[pos2].parent=i;
    }
}

//遍历树进行分组编码
int  PreList(HuffmanTree T[],int layer,char a[],char b,char key[]){
    
    char temp[codeNum];

    for (int i=0; i<codeNum; i++) {
        temp[i]='\0';
    }
    int i=0;
    while (a[i]!='\0') {
        temp[i]=a[i];
      
        i++;
    }
   
    temp[i]=b;
   // cout<<temp<<endl;
    if ((T[layer].lChild==-1)&&(T[layer].rChild==-1)) {

        cout<<T[layer].code<<":"<<temp<<endl;
        
        int t=0;
        while (temp[t]!='\0') {
            T[layer].s[t]=temp[t];
            t++;
        }
        T[layer].s[t]='\0';
        
       // T[layer].s=temp;
        //cout<<T[layer].s<<endl;
//        
//        for (int i=0; i<codeNum; i++) {
//        if (T[layer].code==key[i]) {
//            int j=0;
//            while (j<codeNum) {
//                keyAndCode[i][j]=temp[j];
//                j++;
//            }
//            keyAndCode[i][j]='\0';
//        }
//    }
        return 0;
    }
    PreList(T, T[layer].lChild, temp,'0',key);
    PreList(T, T[layer].rChild, temp,'1',key);

    return 0;
}

//遍历树输出编码
int  search(char a,HuffmanTree T[],int layer,char temp[],int f){
  //      cout<<T[layer].weight<<" "<<T[layer].parent<<" "<<T[layer].lChild<<" "<<T[layer].rChild<<" "<<T[layer].code<<" "<<T[layer].s<<endl;
    //int tht=f;
    if ((T[layer].lChild==-1)&&(T[layer].rChild==-1)) {
        
        if (T[layer].code==a) {
            //cout<<"Count 1"<<endl;
            cout<<T[layer].s;
            int i=0;
            while (T[layer].s[i]!='\0') {
                
                i++;
                tht++;
            }
        }
        
        return 0;
    }
    
    search(a, T, T[layer].lChild, temp,tht);
    search(a, T, T[layer].rChild, temp,tht);
     return 0;
    
}

//遍历树，进行解码

int decoded(char decode[],int num,HuffmanTree T[],int layer){
    if (decode[num]=='\0') {
        return 0;
    }else if ((T[layer].lChild==-1)&&(T[layer].rChild==-1)){
        cout<<T[layer].code;
        decoded(decode,num,T,6);
    }else  if(decode[num]=='0'){
        num++;
        decoded(decode, num, T, T[layer].lChild);
    }else if(decode[num]=='1'){
        num++;
        decoded(decode, num, T, T[layer].rChild);
    }
}

