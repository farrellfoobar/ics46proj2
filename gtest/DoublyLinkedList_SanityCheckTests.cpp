// DoublyLinkedList_SanityCheckTests.cpp
//
// ICS 46 Winter 2018
// Project #2: Time Waits for No One
//
// This is a set of unit tests that demonstrate various aspects of how
// your DoublyLinkedList<ValueType> class template should behave when
// you're finished.  When you're finished, all of these tests should
// pass.  (Note, too, that these tests are far from exhaustive; we'll
// be testing your implementation more thoroughly, so you might want
// to write your own tests, as well.)

#include <string>
#include <gtest/gtest.h>
#include "DoublyLinkedList.hpp"


TEST(DoublyLinkedList_SanityCheckTests, emptyWhenDefaultConstructed)
{
    DoublyLinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
}


TEST(DoublyLinkedList_SanityCheckTests, sizeIsZeroWhenDefaultConstructed)
{
    DoublyLinkedList<int> list;
    EXPECT_EQ(0, list.size());
}


TEST(DoublyLinkedList_SanityCheckTests, whenAddingToStart_SizeIncreases)
{
    DoublyLinkedList<int> list;

    for (unsigned int i = 1; i <= 10; ++i)
    {
        list.addToStart(i * 5);
        EXPECT_EQ(i, list.size());
    }
}


TEST(DoublyLinkedList_SanityCheckTests, afterAddingAValue_ListIsNoLongerEmpty)
{
    DoublyLinkedList<int> list;
    list.addToStart(10);
    EXPECT_FALSE(list.isEmpty());
}


TEST(DoublyLinkedList_SanityCheckTests, whileAddingValues_FirstAndLastAreCorrect)
{
    DoublyLinkedList<int> list;

    list.addToStart(10);
    EXPECT_EQ(10, list.first());
    EXPECT_EQ(10, list.last());

    list.addToStart(20);
    EXPECT_EQ(20, list.first());
    EXPECT_EQ(10, list.last());

    list.addToEnd(30);
    EXPECT_EQ(20, list.first());
    EXPECT_EQ(30, list.last());
}


namespace
{
    struct Date
    {
        unsigned int year;
        unsigned int month;
        unsigned int day;
    };
}


TEST(DoublyLinkedList_SanityCheckTests, addingValuesOfVariousTypesIsSupported)
{
    DoublyLinkedList<int> intList;
    intList.addToStart(10);
    EXPECT_EQ(10, intList.first());

    DoublyLinkedList<std::string> stringList;
    stringList.addToStart("Boo");
    EXPECT_EQ("Boo", stringList.first());

    DoublyLinkedList<Date> dateList;
    dateList.addToStart({2005, 11, 1});
    EXPECT_EQ(2005, dateList.first().year);
    EXPECT_EQ(11, dateList.first().month);
    EXPECT_EQ(1, dateList.first().day);
}


TEST(DoublyLinkedList_SanityCheckTests, whenRemovingValues_SizeDecreases)
{
    DoublyLinkedList<int> list;

    for (unsigned int i = 0; i < 10; ++i)
    {
        list.addToEnd(0);
    }

    for (unsigned int i = 10; i >= 1; --i)
    {
        list.removeFromStart();
        EXPECT_EQ(i - 1, list.size());
    }
}


TEST(DoublyLinkedList_SanityCheckTests, whenRemovingValues_ListIsEmptyAfterRemovingLast)
{
    DoublyLinkedList<int> list;

    for (unsigned int i = 0; i < 10; ++i)
    {
        list.addToEnd(i);
    }

    for (unsigned int i = 0; i < 10; ++i)
    {
        EXPECT_FALSE(list.isEmpty());
        list.removeFromStart();
    }

    EXPECT_TRUE(list.isEmpty());
}


TEST(DoublyLinkedList_SanityCheckTests, whenRemovingValues_FirstAndLastAreCorrect)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);
    list.addToEnd(40);

    list.removeFromStart();
    EXPECT_EQ(20, list.first());
    EXPECT_EQ(40, list.last());
    
    list.removeFromEnd();
    EXPECT_EQ(20, list.first());
    EXPECT_EQ(30, list.last());

    list.removeFromStart();
    EXPECT_EQ(30, list.first());
    EXPECT_EQ(30, list.last());
}


TEST(DoublyLinkedList_SanityCheckTests, cannotObtainFirstElementFromEmptyList)
{
    DoublyLinkedList<int> list;

    EXPECT_THROW({ list.first(); }, EmptyException);
}


TEST(DoublyLinkedList_SanityCheckTests, cannotObtainLastElementFromEmptyList)
{
    DoublyLinkedList<int> list;

    EXPECT_THROW({ list.last(); }, EmptyException);
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsOnEmptyListsArePastStartAndPastEnd)
{
    DoublyLinkedList<int> list;

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();

    EXPECT_TRUE(iterator.isPastStart());
    EXPECT_TRUE(iterator.isPastEnd());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCanMoveForward)
{
    DoublyLinkedList<int> list;

    for (unsigned int i = 1; i <= 10; ++i)
    {
        list.addToEnd(i);
    }

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();

    for (unsigned int i = 1; i <= 10; ++i)
    {
        EXPECT_EQ(i, iterator.value());
        iterator.moveToNext();
    }

    EXPECT_TRUE(iterator.isPastEnd());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCanMoveBackward)
{
    DoublyLinkedList<int> list;

    for (unsigned int i = 1; i <= 10; ++i)
    {
        list.addToEnd(i);
    }

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();

    for (unsigned int i = 1; i <= 9; ++i)
    {
        iterator.moveToNext();
    }

    for (unsigned int i = 10; i >= 1; --i)
    {
        EXPECT_EQ(i, iterator.value());
        iterator.moveToPrevious();
    }

    EXPECT_TRUE(iterator.isPastStart());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCannotMoveBeyondPastEnd)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();
    
    iterator.moveToNext();
    iterator.moveToNext();

    ASSERT_TRUE(iterator.isPastEnd());
    EXPECT_THROW({ iterator.moveToNext(); }, IteratorException);
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCannotMoveBeyondPastStart)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();
    
    iterator.moveToPrevious();

    ASSERT_TRUE(iterator.isPastStart());
    EXPECT_THROW({ iterator.moveToPrevious(); }, IteratorException);
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCannotObtainValueWhenPastStart)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();

    iterator.moveToNext();
    iterator.moveToNext();

    ASSERT_TRUE(iterator.isPastEnd());
    EXPECT_THROW({ iterator.value(); }, IteratorException);
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCannotObtainValueWhenPastEnd)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);

    DoublyLinkedList<int>::ConstIterator iterator = list.constIterator();
    
    iterator.moveToPrevious();

    ASSERT_TRUE(iterator.isPastStart());
    EXPECT_THROW({ iterator.value(); }, IteratorException);
}


TEST(DoublyLinkedList_SanityCheckTests, canModifyValuesWithIterators)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);

    DoublyLinkedList<int>::Iterator iterator = list.iterator();

    iterator.moveToNext();
    iterator.value() = 5000;

    DoublyLinkedList<int>::ConstIterator constIterator = list.constIterator();

    constIterator.moveToNext();
    EXPECT_EQ(5000, iterator.value());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCanInsertValueBeforeCurrentOne)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);

    DoublyLinkedList<int>::Iterator iterator = list.iterator();

    iterator.moveToNext();
    iterator.insertBefore(5000);

    DoublyLinkedList<int>::ConstIterator constIterator = list.constIterator();

    ASSERT_EQ(10, constIterator.value());

    constIterator.moveToNext();
    ASSERT_EQ(5000, constIterator.value());

    constIterator.moveToNext();
    ASSERT_EQ(20, constIterator.value());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCanInsertValueAfterCurrentOne)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);

    DoublyLinkedList<int>::Iterator iterator = list.iterator();

    iterator.moveToNext();
    iterator.insertAfter(5000);

    DoublyLinkedList<int>::ConstIterator constIterator = list.constIterator();

    constIterator.moveToNext();
    ASSERT_EQ(20, constIterator.value());

    constIterator.moveToNext();
    ASSERT_EQ(5000, constIterator.value());

    constIterator.moveToNext();
    ASSERT_EQ(30, constIterator.value());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCanRemoveAndMoveForward)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);
    list.addToEnd(40);

    DoublyLinkedList<int>::Iterator iterator = list.iterator();

    iterator.moveToNext();
    iterator.remove();

    EXPECT_EQ(30, iterator.value());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCanRemoveAndMoveBackward)
{
    DoublyLinkedList<int> list;
    list.addToEnd(10);
    list.addToEnd(20);
    list.addToEnd(30);
    list.addToEnd(40);

    DoublyLinkedList<int>::Iterator iterator = list.iterator();

    iterator.moveToNext();
    iterator.remove(false);

    EXPECT_EQ(10, iterator.value());
}


TEST(DoublyLinkedList_SanityCheckTests, iteratorsCannotRemoveFromPastStartOrPastEndPosition)
{
    DoublyLinkedList<int> list;
    DoublyLinkedList<int>::Iterator iterator = list.iterator();

    EXPECT_THROW({ iterator.remove(); }, IteratorException);
}


TEST(DoublyLinkedList_SanityCheckTests, listsCanBeCopyConstructed_WithSeparateContents)
{
    DoublyLinkedList<int> list1;
    list1.addToEnd(10);
    list1.addToEnd(20);
    list1.addToEnd(30);
    list1.addToEnd(40);

    DoublyLinkedList<int> list2 = list1;
    
    EXPECT_EQ(4, list2.size());
    EXPECT_EQ(10, list2.first());
    EXPECT_EQ(40, list2.last());

    list2.removeFromStart();

    EXPECT_EQ(4, list1.size());
    EXPECT_EQ(10, list1.first());

    EXPECT_EQ(3, list2.size());
    EXPECT_EQ(20, list2.first());
}


TEST(DoublyLinkedList_SanityCheckTests, listsCanBeMoveConstructed_LeavingOriginalEmpty)
{
    DoublyLinkedList<int> list1;
    list1.addToEnd(10);
    list1.addToEnd(20);
    list1.addToEnd(30);

    DoublyLinkedList<int> list2 = std::move(list1);

    EXPECT_EQ(0, list1.size());

    EXPECT_EQ(3, list2.size());
    EXPECT_EQ(10, list2.first());
    EXPECT_EQ(30, list2.last());
}


TEST(DoublyLinkedList_SanityCheckTests, listsCanBeCopyAssigned_WithSeparateContents)
{
    DoublyLinkedList<int> list1;
    list1.addToEnd(10);
    list1.addToEnd(20);
    list1.addToEnd(30);
    list1.addToEnd(40);

    DoublyLinkedList<int> list2;
    list2.addToEnd(5);
    list2.addToEnd(15);
    list2.addToEnd(25);

    list1 = list2;
    
    EXPECT_EQ(3, list1.size());
    EXPECT_EQ(5, list1.first());
    EXPECT_EQ(25, list1.last());

    list1.removeFromStart();

    EXPECT_EQ(2, list1.size());
    EXPECT_EQ(15, list1.first());

    EXPECT_EQ(3, list2.size());
    EXPECT_EQ(5, list2.first());
}


TEST(DoublyLinkedList_SanityCheckTests, listsCanBeMoveAssigned_SwappingContents)
{
    DoublyLinkedList<int> list1;
    list1.addToEnd(10);
    list1.addToEnd(20);
    list1.addToEnd(30);
    list1.addToEnd(40);

    DoublyLinkedList<int> list2;
    list2.addToEnd(5);
    list2.addToEnd(15);
    list2.addToEnd(25);

    list1 = std::move(list2);

    EXPECT_EQ(3, list1.size());
    EXPECT_EQ(5, list1.first());
    EXPECT_EQ(25, list1.last());

    EXPECT_EQ(4, list2.size());
    EXPECT_EQ(10, list2.first());
    EXPECT_EQ(40, list2.last());
}

