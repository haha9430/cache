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
  int turnN = 0;
  int hit;
  int miss;
  Cache* c;
  // 해시테이블의 시간 순서 저장을 위한 연결리스트
  class HashMap {
  private:
    class Node {
    private:
      std::string val;
      Node* next;
    public:
      Node(std::string s): val(s), next(NULL) {}
      std::string getVal() {
        return val;
      }
      Node* getNext() {
        return next;
      }
      void setNext(Node* node) {
        next = node;
      }
    };
    int size;
    Node* nodes;
  public:
    HashMap(): size(0), nodes(NULL) {}
    ~HashMap() { return; }
    void add(std::string s) {
      Node* newNode = new Node(s);
      Node* cur = nodes;
      Node* pre = nodes;
      if(cur == nodes) {
        newNode->setNext(nodes);
        nodes = newNode;
      }else {
        if (cur == NULL) {
          pre->setNext(newNode);
        }else {
          pre->setNext(newNode);
          newNode->setNext(cur);
        }
      }
      size++;
    }
    void remove(std::string s) {
      Node* cur = nodes;
      Node* pre = nodes;
      bool exist = isExist(s);
      if (exist == true) {
        while(cur != NULL && cur->getVal() != s) {
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
    }
    bool isExist(std::string s) {
      Node* cur = nodes;
      bool b = false;
      for (int i = 0; i < size; i++) {
          if(s == cur->getVal()) {
              b = true;
              break;
          }
          cur = cur->getNext();
      }
      return b;
    }
    // 첫번째 원소의 key값을 반환한다
    std::string firstKey() {
      Node* cur = nodes;
      std::string fK;
      while(cur->getNext() != NULL) {
        cur = cur->getNext();
      }
      fK = cur->getVal();
      return fK;
    }
    int mapSize() {
      return size;
    }
    std::string toString() {
    std::string printLL = "";
    Node* cur = nodes;
    
    printLL += cur->getVal();

    cur = cur->getNext();

    while(cur != NULL) {
        printLL += " -> ";
        
        printLL += cur->getVal();
        cur = cur->getNext();
    }

    printLL += "\n";
    return printLL;
  }
};

  // 해시테이블의 연결리스트
  class HashLL {
  private:
    // HashLL의 노드
    class Node {
    private:
      std::string val;
      Node* next;
    public:
      Node(std::string s): val(s), next(NULL){}
      std::string getVal() {
        return val;
      }
      Node* getNext() {
        return next;
      }
      void setNext(Node* node) {
        next = node;
      }
    };
    int size;
    Node* nodes;
  public:
    HashLL(): size(0), nodes(NULL) {}
    ~HashLL() { return; }
    // HashLL의 삽입 함수
    void add(std::string s) {
      Node* newNode = new Node(s);
      Node* cur = nodes;
      Node* pre = nodes;
      if(cur == nodes) {
        newNode->setNext(nodes);
        nodes = newNode;
      }else {
        if (cur == NULL) {
          pre->setNext(newNode);
        }else {
          pre->setNext(newNode);
          newNode->setNext(cur);
        }
      }
      size++;
    }
    // HashLL의 제거 함수
    void remove(std::string s) {
      Node* cur = nodes;
      Node* pre = nodes;
      bool exist = isExist(s);
      if (exist == true) {
        while(cur != NULL && cur->getVal() != s) {
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
    }
    // HashLL의 검색 함수
    bool isExist(std::string s) {
      Node* cur = nodes;
      bool b = false;
      for (int i = 0; i < size; i++) {
          if(s == cur->getVal()) {
              b = true;
              break;
          }
          cur = cur->getNext();
      }
      return b;
    }
  };
  // 해시테이블의 사이즈
  int size;
  // 해시테이블
  HashLL* table[HASH_SIZE];
  // 해시맵
  HashMap map = HashMap();
  // 해시 함수
  int hash(std::string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
      sum += key[i];
    }
    return sum % HASH_SIZE;
  }
  // 팰린드롬인지 판단하고 반환한다
  static bool isPalindrome(std::string str) {
    for (int i = 0; i < str.size() / 2; i++) {
      if (str[i] != str[str.size() - i - 1]) {
        return false;
      }
    }
    return true;
  }
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