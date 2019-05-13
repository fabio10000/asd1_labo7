#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <algorithm>
#include <stdexcept>

template < class T >
class ArrayDeque
{
public:
   using value_type = T;
   using reference = T&;
   using const_reference = const T&;
   using rvalue_reference = T&&;
   using pointer = T*;

   using size_type = std::size_t;
   using difference_type = std::ptrdiff_t;

public:
   pointer buffer;
   size_type capacite;
   size_type debut;
   size_type taille;

public:
   ArrayDeque(size_type cap = 0) : debut(0), taille(0), capacite(cap)
   {
      buffer = capacite != 0 ?
               (pointer) ::operator new(capacite * sizeof(value_type))
                             : nullptr;
   }

   /**
    * @return nb elements dans le buffer
    */
   size_type size() const {
      return taille;
   }

   /**
    * @return nb elements que peut contenir le buffer
    */
   size_type capacity() const {
      return capacite;
   }

   /**
    * @return si le buffer est vide
    */
   bool empty() const {
      return taille == 0;
   }

   /**
    * @return index physique du dernier élément de buffer
    */
   size_type getLastElemIndex() const {
      return !empty() ? (debut + taille - 1) % capacity() : 0;
   }

   /**
    * Double la taille de buffer, sauf si ça taille = 0 et dans ce cas la taille devient = 1
    */
   void resizeVector() {
      if (capacity() == 0) {
         capacite = 1;
      } else {
         capacite *= 2;
      }

      pointer tmp = (pointer) ::operator new(capacite * sizeof(value_type));
      for (size_type i = 0; i < capacity(); ++i) {
         *(tmp + i) = *(buffer + (i + debut) % capacity());
      }

      debut = 0;
      std::swap(tmp, buffer);
   }

   /**
    * insére un élément a la fin de buffer
    * @param val : valeur a insérer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& push_back(value_type val) {
      if (taille == capacity()) {
         resizeVector();
      }

      *(buffer + (getLastElemIndex() + 1) % capacity()) = val;
      ++taille;

      return *this;
   }

   /**
    * insére un élément en première position de buffer
    * @param val : valeur a insérer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& push_front(value_type val) {
      if (taille == capacity()) {
         resizeVector();
      }

      if(!empty()) {
         debut == 0 ? debut = capacity() - 1 : --debut;
      }
      ++taille;
      *(buffer + debut) = val;

      return *this;
   }

   /**
    * @return reference vers le dernier élément de buffer
    */
   const_reference back() const {
      return *(buffer + getLastElemIndex());
   }
   /**
    * @return reference vers le dernier élément de buffer
    */
   reference back() {
      return const_cast<reference>(const_cast<const ArrayDeque*>(this)->back());
   }

   /**
    * @return reference vers le premier élément de buffer
    */
   const_reference front() const {
      return *(buffer + debut);
   }
   /**
    * @return reference vers le premier élément de buffer
    */
   reference front() {
      return const_cast<reference>(const_cast<const ArrayDeque*>(this)->front());
   }

   const_reference at(size_type i) const {
      //return !empty() ? (debut + taille - 1) % capacity() : 0;
      return *(buffer + ((debut + i) % capacity()));
   }

   reference at(size_type i) {
      return const_cast<reference>(const_cast<const ArrayDeque*>(this)->at(i));
   }

   /**
    * Supprime le premier élément de buffer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& pop_front() {
      if (!empty()) {
         debut + 1 == capacity() ? debut = 0 : ++debut;
         --taille;
      }

      return *this;
   }

   /**
    * Supprime le dernier élément de buffer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& pop_back() {
      if (!empty())
         --taille;

      return *this;
   }

};

#endif /* ArrayDeque_hpp */