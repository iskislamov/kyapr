#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


std::map<std::string, std::string> virtualTable;
std::map<std::string, std::set<std::string>> availableFunctions;


#define VIRTUAL_CLASS(baseName) \
  struct baseName {             \
    std::string name_;          \
    baseName() { name_ = #baseName; }

#define VIRTUAL_CLASS_DERIVED(derivedName, baseName) \
  struct derivedName {                               \
    std::string name_;                               \
    std::string base_name_;                          \
    derivedName() {                                  \
      name_ = #derivedName;                          \
      base_name_ = #baseName;                        \
      virtualTable.insert(std::make_pair(name_, base_name_));        \
    }

#define END(name) \
  }               \
  ;

#define DECLARE_METHOD(name, method)                       \
  {                                                        \
    auto iter = availableFunctions.find(#name);            \
    if (iter == availableFunctions.end()) {                \
      availableFunctions.insert(                           \
          std::make_pair(#name, std::set<std::string>())); \
      iter = availableFunctions.find(#name);               \
    }                                                      \
    iter->second.insert(#method);                          \
  }

#define VIRTUAL_CALL(exemplar, method)                                  \
{\
std::string name = (*exemplar).name_;                                     \
bool found = false;                                                     \
auto iter_func = availableFunctions.find(name);                         \
if(iter_func != availableFunctions.end() &&                            \
   iter_func->second.find(#method) != iter_func->second.end()) {        \
    std::cout << iter_func->first << "::" << #method << std::endl;      \
    found = true;                                                       \
  }                                                                     \
if(!found) {                                                            \
    auto iter_table = virtualTable.find(name);                          \
    if (iter_table != virtualTable.end()) {                             \
      auto iter_func = availableFunctions.find(iter_table->second);     \
      if (iter_func != availableFunctions.end() &&                      \
          iter_func->second.find(#method) != iter_func->second.end()) { \
        std::cout << iter_func->first << "::" << #method << std::endl;  \
        found = true;                                                   \
      }                                                                 \
    }                                                                   \
  }                                                                     \
if(!found) {                                                            \
    std::cout << "no method found" << std::endl;                        \
}\
}