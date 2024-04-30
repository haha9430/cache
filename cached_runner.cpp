#include <iostream>
#include "cached_runner.h"
#include <string>
#include <fstream>

#define HASH_SIZE 10

CachedRunner::CachedRunner(Cache &cache): hit(0), miss(0), c(&cache) {
    Hash hash(HASH_SIZE);
}

// 파일의 숫자를 전부 곱하여 반환한다
double CachedRunner::multiply(std::string filename) {
    std::ifstream file(filename);
    double result = 1;
    double number;
    while (file >> number) {
      result *= number;
    }

    bool isExist = c->get(filename, result);
    if (isExist) {
      hit += 1;
    }else {
      miss += 1;
    }
    c->add(filename, result);
    return result;
}

// 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
int CachedRunner::palindrome(std::string filename) {
    std::ifstream file(filename);
    std::string fullText;
    std::string line;
    while (std::getline(file, line)) {
      fullText += line;
    }

    int maxLength = 0;
    int maxIndex = 0;
    std::string maxPalindrome;

    for (int i = 0; i < fullText.size(); i++) {
      for (int j = i + 1; j < fullText.size(); j++) {
        std::string sub = fullText.substr(i, j - i + 1);
        if (isPalindrome(sub) && sub.size() > maxLength) {
          maxLength = sub.size();
          maxIndex = i;
          maxPalindrome = sub;
        } 
      }
    }

    bool isExist = c->get(filename, maxIndex);
    if (isExist) {
      hit += 1;
    }else {
      miss += 1;
    }
    c->add(filename, maxIndex);
    return maxIndex;
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits() {
    return hit;
}

// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses() {
    return miss;
}
// 해쉬 테이블은 배열로 구현
// 임의의 파일을 해쉬 함수를 거쳐 해쉬 값을 출력
// 해쉬 값이 같은 경우를 충돌되었다고 표현
// 충돌되었을 경우 해쉬 테이블 내의 해쉬값을 링크드리스트로 구현
// 캐시러너가 히트했다는 것은 캐시 러너가 가지고 있는 값이 캐시 내에 있다는 것
// 그럴 경우 원래 있던 값을 맨 뒤로 옮김(원래 자리에서 삭제 후 추가)
// 캐시러너가 미스했다는 것은 캐시 러너가 가지고 있는 값이 캐시 내에 없다는 것
// 그럴 경우 캐시 러너가 가지고 있는 값은 테스크로 이동 후 캐시에 추가