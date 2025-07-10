#include <cstddef>
#include <cstdlib>

#include "hw08.h"

namespace cppclass{
/// @brief Constructs an empty linked list.
LinkedList::LinkedList()
        : m_head(nullptr),
          m_tail(nullptr), 
          m_size(0) {}

/**
 * @brief Constructs a linked list from an array.
 *
 * @param arr Pointer to the array.
 * @param size Number of elements in the array.
 */
LinkedList::LinkedList(const int *arr, size_t size)
        : m_head(nullptr),
          m_tail(nullptr),
          m_size(0) {
        for (int i = 0; i < size; i++) {
                append(*(arr + i));
        }
}

/**
 * @brief Copy constructor.
 *
 * @param src Reference to the linked list to copy from.
 */

LinkedList::LinkedList(const LinkedList &src) : m_size(0){
        Node *src_curr = src.m_head;
        for (int i = 0; i < src.m_size; i++) {
                append(src_curr->data);
                src_curr = src_curr->next;
        }
}
 
/**
 * @brief Move constructor.
 *
 * @param src R-value reference to the linked list to move from.
 */
LinkedList::LinkedList(LinkedList &&src) 
        : m_head(src.m_head),
          m_tail(src.m_tail),
          m_size(src.m_size) {
        src.m_head = nullptr;
        src.m_tail = nullptr;
        src.m_size = 0;
}

/**
 * @brief Destructor.
 */
LinkedList::~LinkedList() {
        while (m_size > 0) {
                erase(m_head);
        }
}

/**
 * @brief Remove an element from the linked list.
 *
 * @param node Pointer to a valid node in this list. If nullptr, does nothing.
 */
void LinkedList::erase(Node *node) {
        if (m_size <= 0) return;

        if (m_size == 1) {
                m_tail = nullptr;
                m_head = nullptr;
                delete node;
                m_size--;
                return;
        }

        if (node == m_head) {
                node->next->prev = nullptr;
                m_head = node->next;
        } else if (node == m_tail) {
                node->prev->next = nullptr;
                m_tail = node->prev;
        } else {
                node->next->prev = node->prev;
                node->prev->next = node->next;
        }

        delete node;
        m_size--;
}

/**
 * @brief Appends a new node after the specified node.
 *
 * @param data Data to store in the new node.
 * @param node Pointer to a valid node in the list to append after. If nullptr, appends at end.
 *
 * @return Pointer to the newly created node.
 */
LinkedList::Node* LinkedList::append(int data, Node *node) {
        Node *new_node = new Node();
        new_node->data = data;

        if (node) {
                node->next->prev = new_node;
                new_node->next = node->next;
                node->next = new_node;
                new_node->prev = node;
        } else {
                if (m_size < 1) {
                        m_head = new_node;
                        m_tail = new_node;
                } else {
                        m_tail->next = new_node;
                        new_node->prev = m_tail;
                        m_tail = new_node;
                }
        }

        m_size++;
        return new_node;
}

/**
  * @brief Inserts a new node before the specified node.
  *
  * @param data Data to store in the new node.
  * @param node Pointer to a valid node in the list to insert before. If nullptr, inserts at the beginning.
  * @return Pointer to the newly created node.
  */
LinkedList::Node* LinkedList::insert(int data, Node *node) {
        Node *new_node = new Node();
        new_node->data = data;

        if (node) {
                new_node->prev = node->prev;
                node->prev->next = new_node;
                new_node->next = node;
                node->prev = new_node;
        } else {
                if (m_size < 1) {
                        m_tail = new_node;
                        m_head = new_node;
                } else {
                        m_head->prev = new_node;
                        new_node->next = m_head;
                        m_head = new_node;
                }
        }

        m_size++;
        return new_node;
}

/**
 * @brief Searches for the first node containing given data.
 *
 * @param data Data to search for in the list.
 * @return Pointer to the first node found with @p data. If not found, returns nullptr.
 */
LinkedList::Node* LinkedList::search(int data) const {
        Node *scout = m_head;
        for (int i = 0; i < m_size; i++) {
                if (scout->data == data) return scout;
                scout = scout->next;
        }
        return nullptr;
}

/**
 * @brief Accesses element at the given index.
 *
 * @param index Zero-based index of a node.
 * @return Pointer to the node. If index is out of bounds, returns nullptr.
 */
LinkedList::Node* LinkedList::at(unsigned int index) const {
        if (index >= m_size) return nullptr;

        Node *current;
        if (index > m_size / 2) {
                current = m_tail;
                for (int i = m_size - 1; i > index; i--) {
                        current = current->prev;
                }
        } else {
                current = m_head;
                for (int i = 0; i < index; i++) {
                        current = current->next;
                }
        }

        return current;
}

/**
 * @brief Returns number of nodes in the list.
 *
 * @return Current size of list.
 */
size_t LinkedList::get_size() const { return m_size; }

/**
 * @brief Returns equality between two linked lists
 *
 * @return true if all elements in linked list are equal to each other in order and value
 */
bool LinkedList::operator==(const LinkedList &other) const {
    return false;
}

/**
 * @brief Returns non-equality between two linked lists
 *
 * @return false if all elements in linked list are equal to each other in order and value
 */
bool LinkedList::operator!=(const LinkedList &other) const {
    return false;
}
}