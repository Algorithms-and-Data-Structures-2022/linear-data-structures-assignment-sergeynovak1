#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* node = new Node(value);
    if (front_ == nullptr) {
      front_ = node;
      back_ = node;
    }
    else {
      back_->next = node;
      back_ = node;
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index >= 0 and index <= size_) {
      Node* node = new Node(value);
      if (front_ == nullptr) {
        front_ = node;
        back_ = node;
      }
      else {
        if (index == 0) {
          node->next = front_;
          front_ = node;
        }
        else {
          if (index == size_) {
            back_->next = node;
            back_ = node;
          }
          else {
            Node* prev_node = FindNode(index - 1);
            node->next = prev_node->next;
            prev_node->next = node;
          }
        }
      }
    size_ += 1;
    return true;
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index >= 0 and index <size_) {
      Node* node = front_;
      for (int i = 1; i <=index; ++i) {
        node = node->next;
      }
      node->value = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 and index <= size_ and front_ != nullptr and back_ != nullptr) {
      Node* node = front_;
      if (index == 0) {
        int value = front_->value;
        front_ = front_->next;
        size_ -= 1;
        return value;
      }
      else {
        if (index == size_) {
          int value = back_->value;
          node->next = back_;
          back_ = node;
          size_ -= 1;
          return value;
        }
        else {
          Node* prev_node = FindNode(index - 1);
          node = prev_node->next;
          int value = node->value;
          prev_node->next = node->next;
          size_ -= 1;
          return value;
          }
        }
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /* */) {
    Node* node_to_remove = curr;
    curr = curr->next;
    delete node_to_remove;
    }

    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= 0 and index <size_) {
      Node* node = front_;
      for (int i = 1; i <=index; ++i) {
        node = node->next;
      }
      return node->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    if (front_ != nullptr) {
      for (int i = 0; i < size_; i++) {
        if (node->value == value) {
          return i;
          break;
        }
        node = node->next;
      }
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* node = front_;
    if (front_ != nullptr) {
      for (int i = 0; i < size_; i++) {
        if (node->value == value) {
          return true;
          break;
        }
        node = node->next;
      }
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= 0 and index <size_) {
      Node* node = front_;
      for (int i = 1; i <=index; ++i) {
        node = node->next;
      }
      return node;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment