#include <iostream>
#include <tr1/memory> // for shared_ptr

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
    
                while(1) {
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
            return true;
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
            Node<T> *tmp = find_node(x);
            Node<T> *parent = _root;

            if(tmp)
            {
                // find parent node
                while( parent != NULL ) 
                {
                    if(_comparer(tmp->val, parent->val))
                    {
                        if(parent->right && parent->right->val == tmp->val)
                            break;
                        parent = parent->right;
                    }
                    else
                    {
                        if(parent->left && parent->left->val == tmp->val)
                            break;
                        parent = parent->left;
                    }
                }

                if( !tmp->left || !tmp->right )// have 0 or 1 children
                {
                    Node<T> **ref;
    
                    if(tmp == _root)
                    {
                        if(tmp->left)
                            _root = tmp->left;
                        else
                            _root = tmp->right;
                    } else {
                    

                        if(parent->left && parent->left->val == tmp->val)
                            ref = &(parent->left);
                        else
                            ref = &(parent->right);

                        *ref = tmp->left ? tmp->left : tmp->right;
                    }
                } else {
                    // find successor
                    Node<T> *succ = tmp->right;

                    while(succ->left)
                    {
                        succ = succ->left;
                    }

                    succ->left = tmp->left;

                    if(tmp == _root)
                        _root = succ;
                    else{
                        if(parent->left && parent->left->val == tmp->val)
                        {
                            parent->left = succ;
                        } else {
                            parent->right = succ;
                        }
                    }
                }
                return true;
            } else {
                return false;
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

        ~BST(){
            std::cout<<"Destructor called"<<std::endl;
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

void test_ordering(int (*cmp)(int a, int b))
{
    std::tr1::shared_ptr< BST<int> > drzewo( new BST<int>(cmp) );
    
    drzewo->insert(5); 
    drzewo->insert(7);
    drzewo->insert(6);
    drzewo->insert(8);

    Node<int> *a = drzewo->find_node(6);

    std::cout<<"Found value: "<<a->val<<std::endl;

    std::cout<<"Max value: "<<drzewo->max()<<std::endl;
    std::cout<<"Min value: "<<drzewo->min()<<std::endl;

    drzewo->erase(7);
    drzewo->erase(5);
    drzewo->erase(8);
    drzewo->erase(6);
}

void test_normal_ordering()
{
    std::cout<<"Testing normal ordering"<<std::endl;
    test_ordering(bigger_is_bigger);
}

void test_reverse_ordering()
{
    std::cout<<"Testing reverse ordering"<<std::endl;
    test_ordering(lower_is_bigger);
}

int main()
{   
    test_normal_ordering();
    test_reverse_ordering();
    return 0;
}
