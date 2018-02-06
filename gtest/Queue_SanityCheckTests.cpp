// Queue_SanityCheckTests.cpp
//
// ICS 46 Winter 2018
// Project #2: Time Waits for No One
//
// This is a set of unit tests that demonstrate various aspects of how
// your Queue<ValueType> class template should behave when
// you're finished.  When you're finished, all of these tests should
// pass.  (Note, too, that these tests are far from exhaustive; we'll
// be testing your implementation more thoroughly, so you might want
// to write your own tests, as well.)

#include <gtest/gtest.h>
#include "Queue.hpp"


TEST(Queue_SanityCheckTests, emptyWhenDefaultConstructed)
{
    Queue<int> q;
    EXPECT_TRUE(q.isEmpty());
}


TEST(Queue_SanityCheckTests, sizeIsZeroWhenDefaultConstructed)
{
    Queue<int> q;
    EXPECT_EQ(0, q.size());
}


TEST(Queue_SanityCheckTests, whenEnqueuing_SizeIncreases)
{
    Queue<int> q;

    for (unsigned int i = 1; i <= 10; ++i)
    {
        q.enqueue(i * 5);
        EXPECT_EQ(i, q.size());
    }
}


TEST(Queue_SanityCheckTests, afterEnqueuing_QueueIsNoLongerEmpty)
{
    Queue<int> q;
    q.enqueue(10);
    EXPECT_FALSE(q.isEmpty());
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


TEST(Queue_SanityCheckTests, enqueuingValuesOfVariousTypesIsSupported)
{
    Queue<int> intQueue;
    intQueue.enqueue(10);
    EXPECT_EQ(10, intQueue.front());

    Queue<std::string> stringQueue;
    stringQueue.enqueue("Boo");
    EXPECT_EQ("Boo", stringQueue.front());

    Queue<Date> dateQueue;
    dateQueue.enqueue({2005, 11, 1});
    EXPECT_EQ(2005, dateQueue.front().year);
    EXPECT_EQ(11, dateQueue.front().month);
    EXPECT_EQ(1, dateQueue.front().day);
}


TEST(Queue_SanityCheckTest, queueOrderingIsCorrect)
{
    Queue<int> q;

    for (unsigned int i = 1; i <= 10; ++i)
    {
        q.enqueue(i);
    }

    for (unsigned int i = 1; i <= 10; ++i)
    {
        EXPECT_EQ(i, q.front());
        q.dequeue();
    }
}


TEST(Queue_SanityCheckTests, whenDequeuing_SizeDecreases)
{
    Queue<int> q;

    for (unsigned int i = 0; i < 10; ++i)
    {
        q.enqueue(0);
    }

    for (unsigned int i = 10; i >= 1; --i)
    {
        q.dequeue();
        EXPECT_EQ(i - 1, q.size());
    }
}


TEST(Queue_SanityCheckTests, whenDequeuing_QueueIsEmptyAfterRemovingLast)
{
    Queue<int> q;

    for (unsigned int i = 0; i < 10; ++i)
    {
        q.enqueue(i);
    }

    for (unsigned int i = 0; i < 10; ++i)
    {
        EXPECT_FALSE(q.isEmpty());
        q.dequeue();
    }

    EXPECT_TRUE(q.isEmpty());
}


TEST(Queue_SanityCheckTests, cannotDequeueWhenEmpty)
{
    Queue<int> q;

    EXPECT_THROW({ q.dequeue(); }, EmptyException);
}


TEST(Queue_SanityCheckTests, cannotFrontWhenEmpty)
{
    Queue<int> q;

    EXPECT_THROW({ q.front(); }, EmptyException);
}


TEST(Queue_SanityCheckTests, canIterateQueuesInQueueOrder)
{
    Queue<int> q;

    for (unsigned int i = 1; i <= 10; ++i)
    {
        q.enqueue(i);
    }

    Queue<int>::ConstIterator iterator = q.constIterator();

    for (unsigned int i = 1; i <= 10; ++i)
    {
        ASSERT_EQ(i, iterator.value());
        iterator.moveToNext();
    }

    EXPECT_TRUE(iterator.isPastEnd());
}

