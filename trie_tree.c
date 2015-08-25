// stdafx.h : include file for standard system include files,  
// or project specific include files that are used frequently, but  
// are changed infrequently  
//  
  
#pragma once  
  
#include <stdio.h>    
#include "stdlib.h"  
#include <iostream>  
#include <string.h>  
using namespace std;  
  
//宏定义      
#define TRUE   1      
#define FALSE   0     
#define NULL 0  
#define OK    1      
#define ERROR   0    
#define INFEASIBLE -1      
#define OVERFLOW -2    
  
const int num_chars = 26;  
class Trie {  
public:  
    Trie();  
    Trie(Trie& tr);  
    virtual ~Trie();  
    int trie_search(const char* word, char* entry ) const;  
    int insert(const char* word, const char* entry);  
    int remove(const char* word, char* entry);  
protected:  
     struct Trie_node{  
           char* data; //若不为空，表示从root到此结点构成一个单词   
           Trie_node* branch[num_chars]; //分支   
           Trie_node(); //构造函数   
     };  
       
     Trie_node* root; //根结点(指针)   
  
};  


// Test.cpp : Defines the entry point for the console application.    
//    
#include "stdafx.h"   
Trie::Trie_node::Trie_node() {  
    data = NULL;      
    for (int i=0; i<num_chars; ++i)   
        branch[i] = NULL;  
}  
Trie::Trie():root(NULL) {}  
Trie::~Trie(){}  
int Trie::trie_search(const char* word, char* entry ) const {    
    int position = 0;  //层数   
    char char_code;      
  
    Trie_node *location = root;  //从根结点开始   
    while( location!=NULL && *word!=0 ) {       
        if (*word >= 'A' && *word <= 'Z')   
            char_code = *word-'A';       
        else if (*word>='a' && *word<='z')   
            char_code = *word-'a';       
        else return 0;// 不合法的单词     
        //转入相应分支指针   
        location = location->branch[char_code];       
        position++;       
        word++;    
    }    
    //找到，获取数据，成功返回   
    if ( location != NULL && location->data != NULL ) {       
        strcpy(entry,location->data);       
        return 1;    
    }    
    else  return 0;// 不合法的单词  
}  
int Trie::insert(const char* word, const char* entry) {     
    int result = 1, position = 0;     
    if ( root == NULL ) root = new Trie_node;   //初始插入，根结点为空   
    char char_code;     
    Trie_node *location = root;   //从根结点开始   
    while( location!=NULL && *word!=0 ) {         
        if (*word>='A' && *word<='Z') char_code = *word-'A';         
        else if (*word>='a' && *word<='z') char_code = *word-'a';         
        else return 0;// 不合法的单词      
  
        //不存在此分支   
        if( location->branch[char_code] == NULL )              
            location->branch[char_code] = new Trie_node;    //创建空分支     
  
        //转入分支   
        location = location->branch[char_code];         
        position++;word++;   }     
    if (location->data != NULL) result = 0;//欲插入的单词已经存在      
    else {    //插入数据       
        location->data = new char[strlen(entry)+1];     //分配内存      
        strcpy(location->data, entry);    //给data赋值表明单词存在   
    }     
    return result;    
}  
int main(){     
    Trie t;     
    char entry[100];     
    t.insert("a", "DET");          
    t.insert("abacus","NOUN");     
    t.insert("abalone","NOUN");     
    t.insert("abandon","VERB");     
    t.insert("abandoned","ADJ");    
    t.insert("abashed","ADJ");     
    t.insert("abate","VERB");      
    t.insert("this", "PRON");     
    if (t.trie_search("this", entry))        
        cout<<"'this' was found. pos: "<<entry<<endl;     
    if (t.trie_search("abate", entry))        
        cout<<"'abate' is found. pos: "<<entry<<endl;     
    if (t.trie_search("baby", entry))        
        cout<<"'baby' is found. pos: "<<entry<<endl;     
    else        
        cout<<"'baby' does not exist at all!"<<endl;  
}  




#define MAX 26    //26个字母
#define SLEN 100   //节点中存储的字符串长度
//Trie结构体定义
struct Trie
{
    struct Trie *next[MAX];
    char s[SLEN];      //节点处存储的字符串
    int isword;         //节点处是否为单词
    char val;           //节点的代表字符
} *root;
//初始化Trie树
struct Trie *init()
{
    struct Trie *root = (struct Trie *)malloc(sizeof(struct Trie));
    int i;
    for (i = 0; i < MAX; i++)
    {
        root -> next[i] = NULL;
    }
    root -> isword = 0;
    root -> val = 0;
    return root;
}
//按照指定路径path 插入字符串 s
void insert(char path[], char s[])
{
    struct Trie *t, *p = root;
    int i, j, n = strlen(path);

    for (i = 0; i < n; i++)
    {
        if (p -> next[path[i] - 'a'] == NULL)
        {
            t = (struct Trie *)malloc(sizeof(struct Trie));
            for (j = 0; j < MAX; j++)
            {
                t -> next[j] = NULL;
                t -> isword = 0;
            }
            t -> val = path[i];
            p -> next[path[i] - 'a'] = t;
        }
        p = p -> next[path[i] - 'a'];
    }
    p -> isword = 1;
    strcpy(p -> s , s);
}
//按照指定路径 path 查找
char *find(char path[], int delflag)
{
    struct Trie *p = root;
    int i = 0, n = strlen(path);
    while (p && path[i])
    {
        p = p -> next[path[i++] - 'a'];
    }
    if (p && p -> isword)
    {
        p -> isword = delflag;
        return p->s;
    }
    return NULL;
}
//删除整棵Trie树
void del(struct Trie *root)
{
    int i;
    if (!root)
        return;
    for (i = 0; i < MAX; i++)
    {
        if (root->next[i])
            del(root->next[i]);
        free(root->next[i]);
    }
}