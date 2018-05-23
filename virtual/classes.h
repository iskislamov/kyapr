#pragma once

#include <map>
#include <vector>
#include <functional>

#define VIRTUAL_CLASS(baseName) \
  struct baseName {             \
    std::map<std::string, std::function<void(void*)>> virtualTable_;

#define CONSTRUCTOR_BASE(baseName, ...) baseName(){__VA_ARGS__};

#define VIRTUAL_CLASS_DERIVED(derivedName, baseName) \
  struct derivedName {                               \
    std::map<std::string, std::function<void(derivedName*)>> virtualTable_;

#define CONSTRUCTOR_DERIVED(derivedName, baseName, ...)                     \
  derivedName() {                                                           \
    __VA_ARGS__                                                             \
    baseName exemplar;                                                      \
    for (auto iter = exemplar.virtualTable_.begin();                        \
         iter != exemplar.virtualTable_.end(); ++iter) {                    \
      if (this->virtualTable_.count(iter->first) == 0) {                    \
        this->virtualTable_.insert(std::make_pair(                          \
            iter->first, std::function<void(derivedName*)>(iter->second))); \
      }                                                                     \
    }                                                                       \
  \
};

#define ADD_METHOD(baseName, method) \
  this->virtualTable_.insert(        \
      std::make_pair(#method, std::function<void(void*)>(this->method)));

#define DECLARE_METHOD(baseName, method) \
  static void method(void* ptr) {        \
    baseName* ptr_ = (baseName*)ptr;     \
    std::cout << #baseName << "::" << #method << " ";

#define END_DECLARE       \
  std::cout << std::endl; \
  }                       \
  ;

#define END(baseName) \
  }                   \
  ;

#define VIRTUAL_CALL(exemplar, method) \
  \
(exemplar->virtualTable_[#method])(exemplar);