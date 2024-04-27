#include "cache.h"
#include <string>
#include <iostream>
#include <sstream>

Cache::Cache(): size(0), inners(NULL) {}

Cache::~Cache() {
    return;
}

// int를 cache에 추가한다
void Cache::add(std::string key, int value) {
    Inner* newInner = new Inner(key, value);
    
    Inner* cur = inners;
    Inner* pre = inners;
 
    // 캐시에 동일한 원소가 있는가?
    if (get(key, value) == true) {
        // 해당 원소 삭제
        remove(key, value);
        cur = inners;
        // 새로 추가
        if(cur == inners) {
            newInner->setNext(inners);
            inners = newInner;
        }else {
            if (cur == NULL) {
                pre->setNext(newInner);
            }else {
                pre->setNext(newInner);
                newInner->setNext(cur);
            }
        }    
    }else {
        // 캐시의 크기를 체크한다.
        if (size == CACHE_SIZE) { // 꽉 찼다면
            // 첫번째 원소 삭제 후
            while(cur->getNext() != NULL) {
                cur = cur->getNext();
            }            
            if (cur->getDoubleVal() == -1) {
                remove(cur->getKey(), cur->getIntVal());
            }else {
                remove(cur->getKey(), cur->getDoubleVal());
            }
            cur = inners;
            // 추가
            if(cur == inners) {
                newInner->setNext(inners);
                inners = newInner;
            }else {
                if (cur == NULL) {
                    pre->setNext(newInner);
                }else {
                    pre->setNext(newInner);
                    newInner->setNext(cur);
                }
            }    
        }else { // 꽉 차지 않았다면 바로 추가
            if(cur == inners) {
                newInner->setNext(inners);
                inners = newInner;
            }else {
                if (cur == NULL) {
                    pre->setNext(newInner);
                }else {
                    pre->setNext(newInner);
                    newInner->setNext(cur);
                }
            }
        }
    }
    size++;
    //std::cout << size << std::endl;
    return;
}

// double을 cache에 추가한다
void Cache::add(std::string key, double value) {
    Inner* newInner = new Inner(key, value);
    
    Inner* cur = inners;
    Inner* pre = inners;

    // 캐시에 동일한 원소가 있는가?
    if (get(key, value) == true) {
        // 해당 원소 삭제
        remove(key, value);
        cur = inners;
        // 새로 추가
        if(cur == inners) {
            newInner->setNext(inners);
            inners = newInner;
        }else {
            if (cur == NULL) {
                pre->setNext(newInner);
            }else {
                pre->setNext(newInner);
                newInner->setNext(cur);
            }
        }    
    }else {
        // 캐시의 크기를 체크한다.
        if (size == CACHE_SIZE) { // 꽉 찼다면
            // 첫번째 원소 삭제 후
            while(cur->getNext() != NULL) {
                cur = cur->getNext();
            }
            if (cur->getIntVal() == -1) {
                remove(cur->getKey(), cur->getDoubleVal());
            }else {
                remove(cur->getKey(), cur->getIntVal());
            }
            cur = inners;
            // 추가
            if(cur == inners) {
                newInner->setNext(inners);
                inners = newInner;
            }else {
                if (cur == NULL) {
                    pre->setNext(newInner);
                }else {
                    pre->setNext(newInner);
                    newInner->setNext(cur);
                }
            }
        }else { // 꽉 차지 않았다면 바로 추가
            if(cur == inners) {
                newInner->setNext(inners);
                inners = newInner;
            }else {
                if (cur == NULL) {
                    pre->setNext(newInner);
                }else {
                    pre->setNext(newInner);
                    newInner->setNext(cur);
                }
            }
            
        }
    }
    size++;
    //std::cout << size << std::endl;
    return;
}

// key에 해당하는 value를 cache에서 가져온다
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, int &value) {
    Inner* cur = inners;
    bool b = false;
    for (int i = 0; i < size; i++) {
        if(value == cur->getIntVal()) {
            b = true;
            break;
        }
        cur = cur->getNext();
    }
    return b;
}

// key에 해당하는 value를 cache에서 가져온다.
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, double &value) {
    Inner* cur = inners;
    bool b = false;
    for (int i = 0; i < size; i++) {
        if(value == cur->getDoubleVal()) {
            b = true;
            break;
        }
        cur = cur->getNext();
    }
    return b;
}

// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString() {
    std::string printLL = "";
    Inner* cur = inners;


    if (cur->getIntVal() == -1) {
        printLL += ("[multiply(" + cur->getKey() + "): " + doubleToString(cur->getDoubleVal()) + "]");
    }else {
        printLL += ("[palindrome(" + cur->getKey() + "): " + std::to_string(cur->getIntVal()) + "]");
    }
    
    cur = cur->getNext();

    while(cur != NULL) {
        printLL += " -> ";
        
        if (cur->getIntVal() == -1) {
        printLL += ("[multiply(" + cur->getKey() + "): " + doubleToString(cur->getDoubleVal()) + "]");
        }else {
            printLL += ("[palindrome(" + cur->getKey() + "): " + std::to_string(cur->getIntVal()) + "]");
        }
        cur = cur->getNext();
    }

    printLL += "\n";
    return printLL;
}

// int를 cache에서 삭제한다
void Cache::remove(std::string key, int value) {
    Inner* cur = inners;
    Inner* pre = inners;
    bool exist = get(key, value);
    if (exist == true) {
        while(cur != NULL && (cur->getIntVal() != value && cur->getKey() != key)) {
            if(cur != inners) {
                pre = pre->getNext();
            }
            cur = cur->getNext();
        }

        if(pre == inners && cur == inners) {
            cur = cur->getNext();
            inners = cur;
        }else {
            cur = cur->getNext();
            pre->setNext(cur);
        }

        size--;        
    }

    //std::cout << toString() << std::endl;
    return;
}

// double를 cache에서 삭제한다
void Cache::remove(std::string key, double value) {
    Inner* cur = inners;
    Inner* pre = inners;
    bool exist = get(key, value);
    if (exist == true) {
        while(cur != NULL && (cur->getDoubleVal() != value && cur->getKey() != key)) {
            if(cur != inners) {
                pre = pre->getNext();
            }
            cur = cur->getNext();
        }

        if(pre == inners && cur == inners) {
            cur = cur->getNext();
            inners = cur;
        }else {
            cur = cur->getNext();
            pre->setNext(cur);
        }

        size--;        
    }

    //std::cout << toString() << std::endl;
    return;
}

// double 값을 문자열로 변환한다
std::string Cache::doubleToString(double value) {
  std::ostringstream ss;
  ss << value;
  return ss.str();
}