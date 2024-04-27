#ifndef CACHED_RUNNER_H
#define CACHED_RUNNER_H

#include <iostream>
#include "cache.h"
#include <string>
#include <fstream>

#define HASH_SIZE 10

class CachedRunner {
private:
  // TODO: private 멤버 변수와 함수 추가 가능
  int hit;
  int miss;
  Cache* c;
  
  class Hash {
  private:
    int size; 
    
    class HashLL {
    private:
      class Node {
      private:
        int val;
        Node* next;
      public:
        Node(int i) : val(i), next(NULL) {}
        int& getVal() {
          return val;
        }
        Node* getNext() {
          return next;
        }
        void setNext(Node* node) {
          next = node;
        }
      };
      Node* nodes;
      int size;
    public:
      HashLL() {}
      ~HashLL() {}
      void insert(int val) {
        Node* newNode = new Node(val);

        Node* cur = nodes;
        Node* pre = nodes;
        if(cur == nodes) {
            newNode->setNext(nodes);
            nodes = newNode;
        }else {
            if(cur == NULL) {
                pre->setNext(newNode);
            }else {
                pre->setNext(newNode);
                newNode->setNext(cur);
            }
        }

        size++;
        return;
      }
      void remove(int val) {
        Node* cur = nodes;
        Node* pre = nodes;
        bool exist = isExist(val);
        if (exist == true) {
            while(cur != NULL && cur->getVal() != val) {
                if(cur != nodes) {
                    pre = pre->getNext();
                }
                cur = cur->getNext();
            }

            if(pre == nodes && cur == nodes) {
                cur = cur->getNext();
                nodes = cur;
            }else {
                cur = cur->getNext();
                pre->setNext(cur);
            }

            size--;
        }

        return;
      }
      bool isExist(int val) {
        Node* cur = nodes;
        bool b = false;
        for (int i = 0; i < size; i++) {
            if (val == cur->getVal()) {
                bool b = true;
                break;
            }
            cur->getNext();
        }

        return b;
      }
    };

  HashLL* hashTable;

  public:
    Hash(int size) {
      hashTable[size];
    }
    int hash(std::string key) {
      int sum = 0;
      for (int i = 0; i < key.length(); i++) {
        sum += key[i];
      }
      return sum % size;
    }
  };

static bool isPalindrome(std::string str) {
  for (int i = 0; i < str.size() / 2; i++) {
    if (str[i] != str[str.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

void insert(double d);

void insert(int i);
public:
  CachedRunner(Cache &cache);

  // 파일의 숫자를 전부 곱하여 반환한다
  double multiply(std::string filename);

  // 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
  int palindrome(std::string filename);

  // 캐시에 히트한 횟수를 반환한다
  int hits();

  // 캐시에 미스한 횟수를 반환한다
  int misses();
};

#endif