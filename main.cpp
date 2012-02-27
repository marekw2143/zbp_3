#include <iostream>

template<class T> class Node
{
    public:
        Node(T x)
        {
            val = x;
        };

        T val;

        Node<T> *left, *right;
};

template<class T> class BST
{
    public:
        BST(int (*cmp)(T a, T b)): _root(NULL)
        {
            _comparer = cmp;
        };

        bool insert(T x)
        {
            Node<T> *nn = new Node<T>(x);
            if(_root == NULL)
            {
                _root = nn;
            } else 
            {
                Node<T> *tmp = _root;
    
                while(1)
                {
                    if(_comparer(nn->val, tmp->val))
                    {
                        if(tmp->right == NULL)
                        {
                            tmp->right = nn;
                            break;
                        } else
                        {
                            tmp = tmp->right;
                            continue;
                        }
                    } else 
                    {
                        if(tmp->left == NULL)
                        {
                            tmp->left = nn;
                            break;
                        } else
                        {
                            tmp = tmp->left;
                            continue;
                        }
                    }
                }
            }
        };

        Node<T> *find_node(T x)
        {
            Node<T> *tmp = _root;

            while( tmp != NULL && tmp->val != x)
            {
                if(_comparer(x, tmp->val))
                    tmp = tmp->right;
                else
                    tmp = tmp->left;
            }
            
            return tmp;
        };
    
        bool find(T x)
        {
            return find_node(x) == NULL ? false : true;
        }

        bool erase(T x)
        {
            Node<T> tmp = find_node(x);
            if(tmp)
            {
                
            }
        };

        T& min()
        {
            Node<T> *tmp = _root;
    
            while(tmp->left)
                tmp = tmp->left;
    
            return tmp->val;
        };

        T& max()
        {
            Node<T> *tmp = _root;
    
            while(tmp->right)
                tmp = tmp->right;
    
            return tmp->val;
        };

    protected:
        int (*_comparer)(T a, T b);
    
        Node<T> *_root;
};

int bigger_is_bigger(int a, int b)
{
    if(a>b)
        return 1;
    return 0;
}

int lower_is_bigger(int a, int b)
{
    if(a<b) 
        return 1;
    return 0;
}

int main()
{   
    BST<int> drzewo(lower_is_bigger);
    
    drzewo.insert(5);
    drzewo.insert(7);
    drzewo.insert(6);

    Node<int> *a = drzewo.find_node(6);

    std::cout<<"Max value: "<<drzewo.max()<<std::endl;
    std::cout<<"Min value: "<<drzewo.min()<<std::endl;
    return 0;
}
