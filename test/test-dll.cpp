#include "../src/LinkedList.h"
#include <iostream>
#include "acutest.h"

using namespace std;

int comparator(int a, int b)
{
    return b - a;
}

// sample test file to verify tests are working correctly
void test_example()
{
    TEST_CHECK(2 == 2);
}

void test_add()
{
    LinkedList<int> list;
    list.add(2);
    TEST_CHECK(list.size() == 1);
    list.add(4);
    TEST_CHECK(list.get(0) == 2);
    TEST_CHECK(list.get(1) == 4);
    TEST_CHECK(list.size() == 2);
}

void test_update()
{
    LinkedList<int> list;
    list.add(2);
    list.update(0, 4);
    TEST_CHECK(list.get(0) == 4);
    TEST_CHECK(list.size() == 1);
}

void test_add_sorted()
{
    LinkedList<int> list;
    list.addSorted(5);
    list.addSorted(1);
    list.addSorted(6);
    TEST_CHECK(list.get(0) == 1);
    TEST_CHECK(list.get(1) == 5);
    TEST_CHECK(list.get(2) == 6);
    TEST_CHECK(list.size() == 3);
}

void test_remove()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    list.remove(2);
    TEST_CHECK(list.get(0) == 4);
    TEST_CHECK(list.size() == 1);
    list.add(5);
    list.removeIndex(0);
    TEST_CHECK(list.get(0) == 5);
    TEST_CHECK(list.size() == 1);
}

void test_size()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    TEST_CHECK(list.size() == 2);
    list.remove(2);
    TEST_CHECK(list.size() == 1);
}

void test_indexOf()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    list.add(2);
    TEST_CHECK(list.indexOf(4) == 1);

    TEST_CHECK(list.indexOf(2) == 0);
    
    TEST_CHECK(list.lastIndexOf(2) == 2);
    
    TEST_CHECK(list.indexOf(1) == -1);
    
    TEST_CHECK(list.lastIndexOf(1) == -1);
}

void test_occurences()
{
    LinkedList<int> list;
    list.add(2);
    list.add(3);
    list.add(2);
    
    TEST_CHECK(list.occurences(2) == 2);

    TEST_CHECK(list.occurences(3) == 1);

    TEST_CHECK(list.occurences(1) == 0);
}

void test_replace()
{
    LinkedList<int> list;
    list.add(2);
    list.add(3);
    list.add(2);
    list.replace(3, 4);
    TEST_CHECK(list.get(1) == 4);
    list.replaceAll(2, 1);
    TEST_CHECK(list.get(0) == 1);
    TEST_CHECK(list.get(2) == 1);
}

void test_pop()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    TEST_CHECK(list.size() == 2);
    list.pop();
    TEST_CHECK(list.size() == 1);
    TEST_CHECK(list.get(0) == 2);
    TEST_EXCEPTION(list.get(1), DSAException);
}

void test_shift()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    TEST_CHECK(list.size() == 2);
    list.shift();
    TEST_CHECK(list.size() == 1);
    TEST_CHECK(list.get(0) == 4);
    TEST_EXCEPTION(list.get(1), DSAException);
}

void test_includes()
{
    LinkedList<int> list;
    list.add(4);
    list.add(2);
    TEST_CHECK(list.includes(2));
    TEST_CHECK(!list.includes(1));
}

void test_get()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    TEST_CHECK(list.get(0) == 2);
    TEST_CHECK(list.get(1) == 4);
}

void test_reverse()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);

    TEST_CHECK(list.get(0) == 2);

    TEST_CHECK(list.get(1) == 4);

    LinkedList<int> list2 = list.reverse();

    TEST_CHECK(list2.get(0) == 4);

    TEST_CHECK(list2.get(1) == 2);
}

void test_sort()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);
    list.add(3);

    TEST_CHECK(list.get(0) == 2);

    TEST_CHECK(list.get(1) == 4);

    TEST_CHECK(list.get(2) == 3);

    LinkedList<int> sorted = list.sort();

    TEST_CHECK(sorted.get(0) == 2);

    TEST_CHECK(sorted.get(1) == 3);

    TEST_CHECK(sorted.get(2) == 4);
}

void test_clear()
{
    LinkedList<int> list;
    list.add(2);
    list.add(4);

    TEST_CHECK(list.get(0) == 2);
    
    TEST_CHECK(list.get(1) == 4);

    list.clearAll();

    TEST_CHECK(list.size() == 0);

    TEST_EXCEPTION(list.get(0), DSAException);
    TEST_MSG("Expected: DSAException");
}

TEST_LIST = {
    {"verification", test_example}, /* verifying tests library works correctly*/
    {"add", test_add},
    {"size", test_size},
    {"get", test_get},
    {"update", test_update},
    {"add sorted", test_add_sorted},
    {"remove", test_remove},
    {"indexof", test_indexOf},
    {"occurences", test_occurences},
    {"replace", test_replace},
    {"pop", test_pop},
    {"shift", test_shift},
    {"includes", test_includes},
    {"reverse", test_reverse},
    {"sort", test_sort},
    {"clear", test_clear},
    {NULL, NULL} /* zeroed record marking the end of the list */
};
