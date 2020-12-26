#include "../lib/DSA.h"
#include <iostream>
#include <cstdarg>

using namespace std;

template <typename T>
int comparator(T a, T b)
{
    return a - b;
};

template <typename T>
class LinkedList
{
private:
    // will store the size of linked list
    int count;

    // will store the start pointer of linked list
    NODE<T> *start;

    // will store the end pointer of linked list
    NODE<T> *end;

public:
    // constructor to initializes
    LinkedList();

    // add new data to linked list
    void add(T data);

    // update the data at index
    // 0 <= index < size of list
    void update(int index, T data);

    // add new data to linked list in sorted fashion
    void addSorted(T data, int (*comparator)(T, T) = comparator);

    // returns size of list
    int size();

    // remove node from linked list that matches the data parameter using the passed comparator
    void remove(T data, int (*comparator)(T, T) = comparator);

    // remove node at index
    T removeIndex(int index);

    // first-index of data else -1
    int indexOf(T data, int (*comparator)(T, T) = comparator);

    // total occurences of data
    int occurences(T data, int (*comparator)(T, T) = comparator);

    // last index of data else -1
    int lastIndexOf(T data, int (*comparator)(T, T) = comparator);

    // concat another linkedlist(s) to the end of this
    //void concat(LinkedList<T>... items);

    // replace first occurence of value with newvalue
    void replace(T value, T newvalue, int (*comparator)(T, T) = comparator);

    // replace all occurences of value with newvalue
    void replaceAll(T value, T newvalue, int (*comparator)(T, T) = comparator);

    // remove last node
    T pop();

    // remove first node
    T shift();

    // check if linked list contains given data using passed comparator
    bool includes(T data, int (*comparator)(T, T) = comparator);

    // get node at index
    T get(int index);

    // return a new reversed linked list
    LinkedList<T> reverse();

    // return a new sorted linked list
    LinkedList<T> sort(int (*comparator)(T, T) = comparator);

    // clear the linked list
    void clearAll();

    //remove from publish
    void printAll();
};

template <typename T>
LinkedList<T>::LinkedList()
{
    count = 0;
    start = NULL;
    end = NULL;
};

template <typename T>
void LinkedList<T>::add(T data)
{
    NODE<T> *node = new NODE<T>();
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    if (start == NULL)
    {
        start = new NODE<T>();
        start->next = node;
        start->prev = NULL;
        end = new NODE<T>();
        end->prev = node;
        end->next = NULL;
        node->next = end;
        node->prev = start;
        count += 1;
        return;
    }
    node->prev = end->prev;
    node->next = end;
    end->prev->next = node;
    end->prev = node;
    end->next = NULL;
    count += 1;
    return;
};

template <typename T>
void LinkedList<T>::addSorted(T data, int (*comparator)(T, T))
{
    if (start == NULL)
    {
        return add(data);
    }
    //cout << "Start not null\n";
    NODE<T> *node = new NODE<T>();
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        if (temp->greaterthanorequal(node->data, comparator))
        {
            node->prev = temp->prev;
            node->next = temp;
            node->prev->next = node;
            node->next->prev = node;
            count += 1;
            return;
        }
        temp = temp->next;
    }
    node->next = end;
    node->prev = end->prev;
    node->prev->next = node;
    node->next->prev = node;
    count += 1;
    return;
};

template <typename T>
int LinkedList<T>::size()
{
    return count;
};

template <typename T>
void LinkedList<T>::remove(T data, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL)
    {
        return;
    }
    NODE<T> *temp = start->next;
    while (temp->next != NULL)
    {
        if (temp->equals(data, comparator))
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            count -= 1;
            /*if (start == NULL || start->next == NULL || count == 0 || end->prev == start)
            {
                onListEmptied();
            }*/
            return;
        }
        temp = temp->next;
    }
};

template <typename T>
T LinkedList<T>::removeIndex(int index)
{
    if (start == NULL || start->next == NULL || index >= count)
    {
        return NULL;
    }
    int distance_to_end = count - index;
    NODE<T> *temp;
    bool forward = true;
    int i = 0;
    if (index < distance_to_end)
    {
        temp = start->next;
    }
    else
    {
        temp = end->prev;
        forward = false;
        i = count - 1;
    }
    while ((forward ? temp->next : temp->prev) != NULL)
    {
        if (i == index)
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            count -= 1;
            /*if (start == NULL || start->next == NULL || count == 0 || end->prev == start)
            {
                onListEmptied();
            }*/
            return temp->data;
        }
        if (forward)
        {
            temp = temp->next;
            i += 1;
        }
        else
        {
            temp = temp->prev;
            i -= 1;
        }
    }
    return NULL;
};

template <typename T>
T LinkedList<T>::pop()
{
    if (count <= 0)
    {
        return NULL;
    }
    NODE<T> *popped = end->prev;
    end->prev->prev->next = end;
    end->prev = popped->prev;
    count -= 1;
    /*if (start == NULL || start->next == NULL || count == 0 || end->prev == start)
    {
        onListEmptied();
    }*/
    return popped->data;
};

template <typename T>
T LinkedList<T>::shift()
{
    if (count <= 0)
    {
        return NULL;
    }
    NODE<T> *popped = start->next;
    start->next->next->prev = start;
    start->next = popped->next;
    count -= 1;
    /*if (start == NULL || start->next == NULL || count == 0 || end->prev == start)
    {
        onListEmptied();
    }*/
    return popped->data;
};

template <typename T>
bool LinkedList<T>::includes(T data, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL)
    {
        return false;
    }
    NODE<T> *temp = start->next;
    while (temp->next != NULL)
    {
        if (temp->equals(data, comparator))
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
};

template <typename T>
T LinkedList<T>::get(int index)
{
    if (start == NULL || start->next == NULL || index >= count)
    {
        throw DSAException("EMPTY_LIST");
    }
    int distance_to_end = count - index;
    NODE<T> *temp;
    bool forward = true;
    int i = 0;
    if (index < distance_to_end)
    {
        temp = start->next;
    }
    else
    {
        temp = end->prev;
        forward = false;
        i = count - 1;
    }
    while ((forward ? temp->next : temp->prev) != NULL)
    {
        if (i == index)
        {
            return temp->data;
        }
        if (forward)
        {
            i += 1;
            temp = temp->next;
        }else {
            i -= 1;
            temp = temp->prev;
        }
    }
    return NULL;
};

template <typename T>
LinkedList<T> LinkedList<T>::reverse()
{
    LinkedList<T> reverselist;
    if (start == NULL || start->next == NULL || count == 0 || end->prev == NULL)
    {
        return reverselist;
    }
    NODE<T> *temp = end->prev;
    while (temp != NULL && temp != start)
    {
        reverselist.add(temp->data);
        temp = temp->prev;
    }
    return reverselist;
};

template <typename T>
LinkedList<T> LinkedList<T>::sort(int (*comparator)(T, T))
{
    LinkedList<T> sortedList;
    if (start == NULL || start->next == NULL || count == 0)
    {
        return sortedList;
    }
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        sortedList.addSorted(temp->data, comparator);
        temp = temp->next;
    }
    return sortedList;
};

template <typename T>
void LinkedList<T>::printAll()
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        cout << "Empty List\n";
        return;
    }
    int index = 0;
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        cout << "(" << index << ")" << temp->data << ":" << this->get(index) << " ";
        temp = temp->next;
        index += 1;
    }
    cout << "\n";
};

template <typename T>
void LinkedList<T>::clearAll()
{
    start = NULL;
    end = NULL;
    count = 0;
};

template <typename T>
int LinkedList<T>::indexOf(T data, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        return -1;
    }
    int index = 0;
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        if (temp->equals(data, comparator))
        {
            return index;
        }
        index += 1;
        temp = temp->next;
    }
    return -1;
};

template <typename T>
int LinkedList<T>::occurences(T data, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        return 0;
    }
    int occs = 0;
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        if (temp->equals(data, comparator))
        {
            occs += 1;
        }
        temp = temp->next;
    }
    return occs;
};

template <typename T>
int LinkedList<T>::lastIndexOf(T data, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        return -1;
    }
    int index = count - 1;
    NODE<T> *temp = end->prev;
    while (temp != NULL && temp != end)
    {
        if (temp->equals(data, comparator))
        {
            return index;
        }
        index -= 1;
        temp = temp->prev;
    }
    return -1;
};

template <typename T>
void LinkedList<T>::update(int index, T data)
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        throw DSAException("EMPTY_LIST");
    }
    else if (index >= count)
    {
        throw DSAException("INVALID_INDEX");
    }
    int i = 0;
    NODE<T> *temp;
    bool forward = true;
    int distance_from_end = count - index;
    if(index < distance_from_end) {
        temp = start->next;
    }else {
        temp = end->prev;
        i = count - 1;
        forward = false;
    }
    while (temp != NULL && temp != end)
    {
        if (i == index)
        {
            temp->data = data;
            return;
        }
        if(forward)
        {
            i += 1;
            temp = temp->next;
        }else {
            i -= 1;
            temp = temp->prev;
        }
    }
};

template <typename T>
void LinkedList<T>::replace(T value, T newvalue, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        return;
    }
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        if (temp->equals(value, comparator))
        {
            temp->data = newvalue;
            return;
        }
        temp = temp->next;
    }
};

template <typename T>
void LinkedList<T>::replaceAll(T value, T newvalue, int (*comparator)(T, T))
{
    if (start == NULL || start->next == NULL || count == 0)
    {
        return;
    }
    NODE<T> *temp = start->next;
    while (temp != NULL && temp != end)
    {
        if (temp->equals(value, comparator))
        {
            temp->data = newvalue;
        }
        temp = temp->next;
    }
};

/*template <typename T>
void LinkedList<T>::concat(LinkedList<T>... items)
{
    cout << "NOT IMPLEMENTED YET" ;
}*/