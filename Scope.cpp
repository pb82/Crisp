//
// Created by peter on 12.12.17.
//

#include "Scope.h"

 namespace Crisp {

     Scope::Scope(Scope *parent) : parent(parent) {
         if (parent) {
             parent->registerChild(this);
         }
     }

     Scope::~Scope() {
         if (parent) {
             parent->deregisterChild(this);
         }
     }

     Sc_Value* Scope::lookup(const char *key) {
         if (bindings.find(key) == bindings.end()) {
             if (parent) {
                 return parent->lookup(key);
             } else {
                 return nullptr;
             }
         } else {
             return bindings[key];
         }
     }

     void Scope::assign(const char *key, Sc_Value *value) {
         bindings[key] = value;
     }

     void Scope::traverseMark(bool val) {
         for (auto &binding : bindings) {
             binding.second->mark(val);
         }

         for (auto childScope : childScopes) {
             childScope->traverseMark(val);
         }
     }

     void Scope::registerChild(Scope *childScope) {
         childScopes.push_back(childScope);
     }

     void Scope::deregisterChild(Scope *childScope) {
         auto it = std::find(childScopes.begin(), childScopes.end(), childScope);
         if (it != childScopes.end()) {
             auto index = std::distance(childScopes.begin(), it);
             childScopes.erase(childScopes.begin() + index);
         }
     }
 }
