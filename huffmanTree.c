#include <iostream>

#include <string>

#include <algorithm>

#define MAX 10000

using namespace std;

//赫夫曼树和赫夫曼编码的存储表示

typedef struct{
    
    char c;
    
    int weight;
    
    int parent,lchild,rchild;
    
}HTNode,*HuffmanTree;   //动态分配数组存储赫夫曼树

char e[MAX];

typedef char **HuffmanCode; //动态分配数组存储赫夫曼编码表

void Select(HuffmanTree &HT, int n,int &s1,int &s2)

{
    
    int i, j;
    
    for(i = 1;i <= n;i++)
        
        if(!HT[i].parent)
            
        {
            
            s1 = i;
            
            break;
            
        }
    
    for(j = i+1;j <= n;j++)
        
        if(!HT[j].parent)
            
        {
            
            s2 = j;
            
            break;
            
        }
    
    
    
    for(i = 1;i <= n;i++)
        
        if((HT[i].weight < HT[s1].weight) && (!HT[i].parent) && (s2 != i))
            
            s1 = i;
    
    for(j = 1;j <= n;j++)
        
        if((HT[j].weight < HT[s2].weight) && (!HT[j].parent) && (s1 != j))
            
            s2 = j;
    
    // 保证s1的weight比s2的小
    
    if(HT[s1].weight > HT[s2].weight)
        
    {
        
        int tmp = s1;
        
        s1 = s2;
        
        s2 = tmp;
        
    }
    
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,char *l,int *w,int n){
    
    //w存放n个字符的权值（均>0）,构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
    
    int m,i;
    
    int s1,s2;
    
    HuffmanTree p;
    
    char *cd;
    
    if(n <= 1) return;
    
    m = 2*n-1;
    
    HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));     //0号单元未用
    
    for(p = HT+1,i=1;i<=n;++i,++p,++w,++l){
        
        *p = {*l,*w,0,0,0};
        
    }
    
    for(;i<=m;++i,++p){
        
        *p = {' ',0,0,0,0};
        
    }
    
    for(i=n+1;i<=m;++i){       //建赫夫曼树
        
        //在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号分别为s1和s2
        
        Select(HT,i-1,s1,s2);
        
        HT[s1].parent = i;
        
        HT[s2].parent = i;
        
        HT[i].lchild = s1;
        
        HT[i].rchild = s2;
        
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        
    }
    
    //从叶子到根逆向求每个字符的赫夫曼编码
    
    int start,c,f;
    
    HC = (HuffmanCode)malloc((n+1)*sizeof(char*));  //分配n个字符编码的头指针向量
    
    cd = (char *)malloc(n*sizeof(char));        //分配求编码的工作空间
    
    cd[n-1] = '\0';     //编码结束符
    
    for(i = 1;i<=n;++i){
        
        start = n-1;
        
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){    //从叶子到根逆向求编码
            
            if(HT[f].lchild==c)
                
                cd[--start] = '0';
            
            else
                
                cd[--start] = '1';
            
        }
        
        HC[i] = (char*)malloc((n-start)*sizeof(char));
        
        strcpy(HC[i],&cd[start]);
        
    }
    
    free(cd);
    
}

void Display_HuffmanTree(HuffmanTree &HT, int n) {      //显示哈夫曼树信息
    
    printf("location    char	weight	 parent	 lchild	 rchild\n");
    
    for(int i=1; i<2*n; i++) {
        
        printf("%d\t%10c\t%7d\t%12d\t%12d\t%12d",i,HT[i].c,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        
        printf("\n");
        
    }
    
}

char* HuffmanDecoding(HuffmanTree &HT,HuffmanCode &HC,char *c,int n,long t,HuffmanCode &d){    //译码
    
    int i,j;
    
    d = (HuffmanCode)malloc((t+1)*sizeof(char*));
    
    for(i=0;i<t;i++){
        
        d[i] = (char*)malloc((t+1)*sizeof(char));
        
    }
    
    for(i = 0;i < t;i++){
        
        for(j = 1;j <= n;j++){
            
            if(*(c+i) == HT[j].c)
                
                strcpy(d[i],HC[j]);
            
            else if(*(c+i) == ' ')
                
                strcpy(d[i],"/");
            
        }
        
    }
    
    for(i = 0;i < t;i++){
        
        for(j=1;j<=n;j++){
            
            if(!strcmp(d[i],HC[j]))
                
                e[i]=HT[j].c;
            
            else if(!strcmp(d[i],"/"))
                
                e[i]=' ';
            
        }
        
    }
    
    return e;
    
}

int main(){
    
    int n,i;
    
    HuffmanTree HT;
    
    HuffmanCode HC;
    
    char *l,**d = nullptr;
    
    int *w;
    
    while(cin>>n && n>0){
        
        l = (char *)malloc((n+1)*sizeof(char));
        
        w = (int *)malloc((n+1)*sizeof(int));
        
        for(i=0;i<n;i++){
            
            cin>>*(l+i)>>*(w+i);
            
        }
        
        HuffmanCoding(HT,HC,l,w,n);
        
        for(i=1;i<=n;i++) {
            
            cout<<*(l+i-1)<<":";
            
            puts(HC[i]);
            
        }
        
        Display_HuffmanTree(HT,n);
        
        char k[MAX];
        
        getchar();
        
        gets(k);
        
        strcpy(e,HuffmanDecoding(HT,HC,k,n,strlen(k),d));
        
        for(i=0;i<strlen(k);i++){
            
            puts(d[i]);
            
        }
        
        puts(e);
        
    }
    
    return 0;
    
}
