#include <cstdlib>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <ctime>

#include <iostream>
using namespace std;

#define MAX_TREE_HT 50
char a[20];
int freq[20];
float prob[20];
float total[20],average;
int p=0,fin;

void countChar(char *str){
    int i,j,cnt=1;
    int l;
    for(l=0; str[l]; ++l)//to low case
        str[l] = tolower(str[l]);
    for(i=0;i<l;i++){
        if(!str[i])continue;
        for(j=i+1;j<l;j++){
            if(str[i] == str[j]){
                cnt++;
                str[j] = 0;
            }
        }
        a[p]=str[i];
        freq[p]=cnt;
        p++;
        cnt=1;
    }
    for(i=0;i<p;i++)
        prob[i]=freq[i]/(l*1.0);

	for(i=0;i<p;i++)
		cout<<a[i]<<"\t"<<prob[i]<<endl;

}

struct MinHeapNode
{
  char data;
  unsigned frequency;
  struct MinHeapNode *left, *right;
};

struct MinHeap
{
  unsigned size;
  unsigned capacity;
  struct MinHeapNode **array;
};

struct MinHeapNode *newNode(char data, unsigned frequency)
{
  struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));

  temp->left = temp->right = NULL;
  temp->data = data;
  temp->frequency = frequency;

  return temp;
}

struct MinHeap *createMinHeap(unsigned capacity)
{
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
  return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
  struct MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
    smallest = left;

  if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
    smallest = right;

  if (smallest != idx)
  {
    swapMinHeapNode(&minHeap->array[smallest],
            &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(struct MinHeap *minHeap)
{

  return (minHeap->size == 1);
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap)

{
  struct MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode)
{
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency)
  {

    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap)
{
  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
  {
      cout <<arr[i];
  }
  cout << "\n";
}

int isLeaf(struct MinHeapNode *root)
{

  return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char data[], int frequency[], int size)
{
  struct MinHeap *minHeap = createMinHeap(size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(data[i], frequency[i]);

  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}

struct MinHeapNode *buildHuffmanTree(char data[], int frequency[], int size)
{
  struct MinHeapNode *left, *right, *top;
  struct MinHeap *minHeap = createAndBuildMinHeap(data, frequency, size);

  while (!isSizeOne(minHeap))
  {
    left = extractMin(minHeap);
    right = extractMin(minHeap);

    top = newNode('$', left->frequency + right->frequency);

    top->left = left;
    top->right = right;

    insertMinHeap(minHeap, top);
  }
  return extractMin(minHeap);
}
void avg(struct MinHeapNode *root,int top)
{
    int i,m=0,j;
    for(i=0;i<26;i++)
    {
      if(root->data==a[i])
      {
          total[m]=prob[i]*top;
          m++;
      }
    }
    for(j=0;j<m;j++)
    {
        //cout<<total[j]<<endl;
        average+=total[j];

    }
    cout<<"-----------------------------------------------"<<endl;

}
void printCodes(struct MinHeapNode *root, int arr[], int top)
{
  if (root->left)
  {
    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
  }

  if (root->right)
  {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root))
  {
    cout << root->data << "  | "<<"the code length is\t"<<top<<"\t";
    printArr(arr, top);
    avg(root,top);
  }
}

void HuffmanCodes(char data[], int frequency[], int size)
{
  struct MinHeapNode *root = buildHuffmanTree(data, frequency, size);

  int arr[MAX_TREE_HT], top = 0;

  printCodes(root, arr, top);
}
void fixedlength(char *str)
{
	//cout<<endl;
	//cout<<str;
	int l,i=0;
	while(str[i]!='\0')
	{
		i++;
	}
	l=i*5;
	cout<<endl<<"fixedlength code-"<<l<<endl;
	cout<<"-------------------------------"<<endl;
}


int main()
{
  char str[100];
  char str1[100];
	int i=0;
	cout<<"enter string : ";
	gets(str);
	while(str[i]!='\0')
	{
		str1[i]=str[i];
		i++;
	}



	countChar(str);
	fixedlength(str1);
	HuffmanCodes(a, freq, p);
    cout<<"the average code length using huffman code is \t"<<average<<endl;

	return 0;
}
