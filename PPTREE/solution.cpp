# include <iostream>
# include <vector>
# include <utility>
# include <cstdio>

using namespace std;

class TreeNode;
typedef pair<TreeNode *, unsigned long int> PTI;
typedef vector<PTI> VPTI;

/* Class for node of the binary tree 
   Methods are pretty self-explainatory 
 */
class TrieNode
{
   unsigned long int value;
   bool isLeaf;
   TrieNode *left;
   TrieNode *right;
   
   public:
      TrieNode()
      {
         value = 0;
         isLeaf = false;
         left = NULL;
         right = NULL;
      }
      void setValue(unsigned long int n)
      {
         value = n;
      }
      unsigned long int getValue()
      {
         return value;
      }
      void setIsLeaf(bool flag)
      {
         isLeaf = flag;
      }
      bool getIsLeaf()
      {
         return isLeaf;
      }
      void setLeftChild(TrieNode *n)
      {
         left = n;
      }
      TrieNode *getLeftChild()
      {
         return left;
      }
      void setRightChild(TrieNode *n)
      {
         right = n;
      }
      TrieNode *getRightChild()
      {
         return right;
      }
};

class Trie
{
   TrieNode *root;
   unsigned int height;
   unsigned long int numLeaves;
   public:
      Trie()
      {
         root = new TrieNode();
         root->setValue(0);
         height = 0;
         numLeaves = 0;
      }
      ~Trie()
      {
         cleanNode(root);
      }
      
      void cleanNode(TrieNode *n)
      {
         if(n == NULL)
         {
            return;
         }
         if(n->getIsLeaf())
         {
            delete n;
            return;
         }
         cleanNode(n->getLeftChild());
         cleanNode(n->getRightChild());
         delete n;         
      }
      
      void setHeight(unsigned int h)
      {
         height = h;
      }
      unsigned int getHeight()
      {
         return height;
      }      
      unsigned int getNumLeaves()
      {
         return numLeaves;
      }      
      void insertNode(TrieNode *n, unsigned long int val, 
                      unsigned int bitPosition)
      {
         TrieNode *newNode = NULL, *leafNode = NULL;
         bool bitIsSet = val & (1 << bitPosition) ? true : false;
         
         if(bitIsSet)
         {
            if(n->getRightChild() == NULL)
            {
               newNode = new TrieNode();
               newNode->setValue(1);
               n->setRightChild(newNode);
            }
            else
            {
               newNode = n->getRightChild();
            }
            if(bitPosition == 0)
            {
               if(!newNode->getIsLeaf())
               {
                  leafNode = new TrieNode();
                  newNode->setIsLeaf(true);
                  leafNode->setValue(val);
                  newNode->setLeftChild(leafNode);
                  numLeaves++;
               }
            }
            else
            {
               insertNode(n->getRightChild(), val, bitPosition - 1);
            }
         }
         else
         {
            if(n->getLeftChild() == NULL)
            {
               newNode = new TrieNode();
               newNode->setValue(0);
               n->setLeftChild(newNode);
            }
            else
            {
               newNode = n->getLeftChild();
            }
            if(bitPosition == 0)
            {
               if(!newNode->getIsLeaf())
               {
                  leafNode = new TrieNode();
                  newNode->setIsLeaf(true);
                  leafNode->setValue(val);
                  newNode->setLeftChild(leafNode);
                  numLeaves++;
               }
            }
            else
            {
               insertNode(n->getLeftChild(), val, bitPosition - 1);
            }
         }
      }
      void insert(unsigned long int n)
      {
         insertNode(root, n, height);         
      }
      unsigned long int findMaximal(TrieNode *ptr1, TrieNode *ptr2)
      {
         unsigned long int val1, val2;
         val1 = 0;
         val2 = 0;
         bool pathTaken = false;
         TrieNode *child1, *child2;
         
         /* Base case for recursion:
            If either ptr1 or ptr2 has reached a leaf node, end the recursion
            and return the xor of the values pointed to by ptr1 and ptr2.
          */
         if(ptr1 == NULL || ptr2 == NULL)
         {
            cout << "Alert! : ptr1 or ptr2 is NULL in Tree::findMaximal()" << endl;
            return 0;
         }
         if(ptr1->getIsLeaf())
         {
            return   ptr1->getLeftChild()->getValue() ^ 
                     ptr2->getLeftChild()->getValue();
         }
         else
         {
            if(ptr1->getLeftChild() != NULL && ptr2->getRightChild() != NULL)
            {
               child1 = ptr1->getLeftChild();
               child2 = ptr2->getRightChild();
               val1 = findMaximal(child1, child2);
               pathTaken = true;
            }
            if(ptr1->getRightChild() != NULL && ptr2->getLeftChild() != NULL)
            {
               child1 = ptr1->getRightChild();
               child2 = ptr2->getLeftChild();
               val2 = findMaximal(child1, child2);
               pathTaken = true;
            }
            if(!pathTaken)
            {
               child1 = ptr1->getLeftChild();
               child2 = ptr2->getLeftChild();
               
               if(child1 != NULL && child2 != NULL)
               {
                  val1 = findMaximal(child1, child2);
               }
               else
               {
                  child1 = ptr1->getRightChild();
                  child2 = ptr2->getRightChild();               
                  val2 = findMaximal(child1, child2);
               }
            }
            return val1 > val2 ? val1 : val2;
         }
      }
      unsigned long int getMaximalValue()
      {
         return findMaximal(root, root);
      }
};

class TreeNode
{
   VPTI connections;
   unsigned long int xorSum;
   bool xorSumComputed;
   
   public:
      TreeNode()
      {
         connections.clear();
         xorSum = 0;
         xorSumComputed = false;
      }
      ~TreeNode()
      {
         //cout << "Called ~TreeNode()" << endl;
         connections.clear();
         return;
      }
      void addConnection(TreeNode *c, unsigned long int w)
      {
         connections.push_back(PTI(c, w));
      }
      VPTI getConnections()
      {
         return connections;
      }
      void setXorSum(unsigned long int x)
      {
         xorSum = x;
      }
      unsigned long int getXorSum()
      {
         return xorSum;
      }
      void setXorFlag(bool x)
      {
         xorSumComputed = x;
      }
      bool getXorFlag()
      {
         return xorSumComputed;
      }      
};

/* Class used to store the initial tree structure 
   Arbitrarily make node 1 as the root of the tree and for each node, 
   compute the xor sum from the root to that node.
   Hence once this computation is done, we have the xor sum of weights from the 
   root to every other node.
 */
class Tree
{
   TreeNode *tree;
   unsigned long int numVertices;
   public:
      Tree(unsigned long int n)
      {
         /* Node 0 is not used, since the vertices are named 1 through 
            numVertices
          */
         tree = new TreeNode[n + 1];
         numVertices = n;
      }
      ~Tree()
      {
         delete [] tree;
      }
      /* Connect the nodes (vertices) v1 & v2 with an edge of weight w
         The connection is registered with both vertices, so that traversal is 
         bi-directional for the tree datastructure.
       */
      void connect(unsigned long int v1, unsigned long int v2, 
         unsigned long int w)
      {
         (tree + v1)->addConnection(tree + v2, w);
         (tree + v2)->addConnection(tree + v1, w);
      }
      TreeNode *getNode(unsigned long int v)
      {
         return tree + v;
      }
      /* The recursive method that computes the xor sum for each node, starting
         with the root node.
       */
      void computeXorSum(TreeNode *n)
      {
         VPTI connections = n->getConnections();
         TreeNode *c;
         unsigned long int v;
         /* Base case, if the xor sum for this node (from the root) has already 
            been computed, then return
          */
         if(n->getXorFlag())
            return;
         
         n->setXorFlag(true);
         
         for(VPTI::iterator it = connections.begin(); it != connections.end(); 
            ++it)
         {
            c = (*it).first;
            v = (*it).second;
            if(!c->getXorFlag())
            {
               c->setXorSum(n->getXorSum() ^ v);
               computeXorSum(c);
            }
         }
      }
      /* Wrapper method for computing the xor sums for every node in the tree
       */
      void computeAllXorSum()
      {
         computeXorSum(tree + 1);
      }
};

int main()
{
   unsigned int numTests;
   unsigned long int numVertices;
   unsigned long int v1, v2;
   unsigned long int weight;
   
   scanf("%u\n", &numTests);
   //cin >> numTests;
   
   Tree *tree = NULL;
   Trie *trie = NULL;
   for(int i = 0; i < numTests; i++)
   {
      scanf("%lu\n", &numVertices);
      //cin >> numVertices;
      tree = new Tree(numVertices);
      trie = new Trie();
      
      /* Read the connections and populate the tree
       */
      for(int j = 1; j < numVertices; j++)
      {
         //cin >> v1 >> v2 >> weight;
         scanf("%lu %lu %lu\n", &v1, &v2, &weight);
         tree->connect(v1, v2, weight);
      }
      
      /* Compute xor sum for every node (from the root)
       */
      tree->computeAllXorSum();
      
      /* Computation to find the required height for the Trie, which would be
         the no. of bits required to store the largest xor sum of the nodes in 
         the Tree
       */
      unsigned long int val, maxVal;
      unsigned int trieHeight;
      maxVal = 0;
      for(int j = 1; j <= numVertices; j++)
      {
         val = tree->getNode(j)->getXorSum();
         if(maxVal < val)
         {
            maxVal = val;
         }
      }
      for(unsigned int j = 0; j < sizeof(unsigned long int) * 8; j++)
      {
         if(1 << j >= maxVal)
         {
            trieHeight = j;
            break;
         }
      }
      
      /* Set the Trie Height
       */
      trie->setHeight(trieHeight);
      
      /* Populate the Trie with the xor sums from the Tree
       */
      for(int j = 1; j <= numVertices; j++)
      {
         val = tree->getNode(j)->getXorSum();
         trie->insert(val);
      }
      
      /* Retrieve the largest "xor of any two xor sums" from the Trie
         This would be the required xor sum of the problem.
       */
      unsigned long int numLeaves = trie->getNumLeaves();
      switch(numLeaves)
      {
         case 0:  //cout << 0 << endl;
                  printf("0\n");
                  break;
         case 1:  //cout << weight << endl; // TODO: Verify this
                  printf("%lu\n", weight);
                  break;
         default: //cout << trie->getMaximalValue() << endl;
                  printf("%lu\n", trie->getMaximalValue());
                  break;
      }
      
      /* Memory Management
       */
      delete tree;
      delete trie;
   }
   return 0;
}
