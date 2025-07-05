#include "hw08.h"
#include "gtest/gtest.h"

namespace {

bool is_data_equal(const LinkedList &list1, const LinkedList &list2) {
        if (list1.get_size() != list2.get_size()) return false;

        LinkedList::Node *list1_current = list1.at(0);
        LinkedList::Node *list2_current = list2.at(0);

        for (int i = 0; i < list1.get_size(); i++) {
                if (list1_current->data != list2_current->data) return false;
                list1_current = list1_current->next;
                list2_current = list2_current->next;
        }

        return true;
}

}

TEST(HW08, BASIC_CONSTRUCTOR) {

}

TEST(HW08, PARAM_CONSTRUCTOR_BASIC) {
        size_t arr_sizes[] = {1, 10, 3, 0};

        for (size_t size : arr_sizes) {
                int arr[size];
                for (int i = 0; i < size; i++) {
                        *(arr + i) = i;
                }
                LinkedList list(arr, size);

                LinkedList::Node *current = list.at(0);
                for (int i = 0; i < list.get_size(); i++) {
                        EXPECT_EQ(current->data, *(arr + i));
                        current = current->next;
                }
        }
}

TEST(HW08, COPY_CONSTRUCTOR_BASIC) {
        size_t arr_sizes[] = {1, 10, 3};

        for (size_t size : arr_sizes) {
                int arr[size];
                for (int i = 0; i < size; i++) {
                        *(arr + i) = i;
                }

                LinkedList src(arr, size);
                LinkedList dest(src);
                EXPECT_TRUE(is_data_equal(src, dest));

                dest.erase(dest.at(0));
                EXPECT_FALSE(is_data_equal(src, dest));

                src.erase(src.at(0));
                EXPECT_TRUE(is_data_equal(src, dest));
        }
}

TEST(HW08, MOVE_CONSTRUCTOR) {
        size_t arr_sizes[] = {1, 10, 3, 0};

        for (size_t size : arr_sizes) {
                int arr[size];
                for (int i = 0; i < size; i++) {
                        *(arr + i) = i;
                }

                LinkedList src(arr, size);
                LinkedList dest(std::move(src));

                EXPECT_EQ(src.get_size(), 0);
                EXPECT_EQ(dest.get_size(), size);
        }
}

TEST(HW08, SEARCH) {
        struct TestDefinition {
                int data;
                LinkedList::Node *expected_result;
        };

        int arr[] = {1, 2, 3, 4, 1, 6, 7, 8, 9};
        LinkedList list(arr, sizeof(arr) / sizeof(*(arr)));

        TestDefinition tests[] = {
                {1, list.at(0)},
                {2, list.at(1)},
                {3, list.at(2)},
                {9, list.at(8)},
                {0, nullptr},
                {42, nullptr},
        };

        for (TestDefinition test : tests) {
                EXPECT_EQ(list.search(test.data), test.expected_result);
        }
}

TEST(HW08, APPEND_BASIC) {
        LinkedList list;

        struct TestDefinitions {
                int data;
        };

        TestDefinitions tests[] = {1, 123, 4124, 12, 4000000};

        int i = 0;
        for (TestDefinitions test : tests) {
                EXPECT_EQ(list.append(test.data), list.at(i));
                i++;
        }
}

TEST(HW08, INSERT_BASIC) {
        LinkedList list;

        struct TestDefinitions {
                int data;
        };

        TestDefinitions tests[] = {1, 42, 412, 123, 12};

        for (TestDefinitions test : tests) {
                EXPECT_EQ(list.insert(test.data), list.at(0));
        }
}

TEST(HW08, ERASE) {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        LinkedList list(arr, sizeof(arr) / sizeof(*arr));

        struct TestDefinitions {
                LinkedList::Node *to_erase;
        };

        TestDefinitions tests[] = {
                list.at(0),
                list.at(1),
        };
}

TEST(HW08, AT) {

}
