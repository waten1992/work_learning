#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

char **ans;
int jindex = 0, iindex = 0, a[100];

char* myitoa(int value, char *str, int base)
{
    int i = 0;
    while(pow(base,i) <= value) {
        i++;
    }
    int len = --i;
    str[len+1] = '\0';
    while(value >= 0 && i >= 0) {
        int tmp = value % base;
        value /= base;
        str[len-i] = tmp+'0';
        i--;
    }
    return str;
}

char* addstr(int size)
{
    if(size == 0)
        return NULL;
    char *x = (char *)malloc(sizeof(char) * 100);
    x[0] = '\0';
    int in;
    char tmp[11];
    for(in = 0; in < size; in++) {
        if(in != 0)
            strcat(x,"->");
        strcat(x, myitoa(a[in], tmp, 10));
    }
    return x;
}

void dfs(struct TreeNode *root)
{
    if(root == NULL){
        ans[iindex++] = addstr(jindex);
    } else {
        a[jindex++] = root->val;
        if(root->left != NULL) {
            dfs(root->left);
            jindex--;
        }
        if(root->right != NULL) {
            dfs(root->right);
            jindex--;
        }
        if(root->left == NULL && root->right == NULL)
            dfs(NULL);
    }
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize)
{
    if(root == NULL) {
        *returnSize = 0;
        return NULL;
    } else {
        ans = (char **)malloc(sizeof(char *) * 100);
        dfs(root);
        *returnSize = iindex;
        return ans;
    }
}
int main()
{
    struct TreeNode one,two,three,four;
    one.val = 1;
    two.val = 2;
    three.val = 3;
    four.val = 4;

    one.left = &two;
    one.right = &three;
    two.left = NULL;
    two.right = &four;
    three.left = three.right =NULL;
    four.left = four.right = NULL;

    int num,m;
    binaryTreePaths(&one,&num);
    printf("size = %d\n",num);
    for(m = 0; m < iindex; m++)
        printf("%s\n",ans[m]);



    printf("hello,world\n");
    return 0;
}
