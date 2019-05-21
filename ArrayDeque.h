/**
 * authors: Basset Nils, Limem Wènes, Marques Fabio
 */
#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <algorithm>
#include <stdexcept>

#include <cstring>
#include <unordered_map>

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

private:
   pointer buffer;
   size_type capacite;
   size_type debut;
   size_type taille;

   /**
    * @return index physique qui correspond au dernier élément
    */
   size_type getLastPhisicalIndex() {
      return (debut + taille) % capacity();
   }

   /**
    * @param i index physique
    * @return adresse correspondant au buffer + i
    */
   pointer getBufferPointerAt(size_type i) {
      return buffer + i;
   }

   /**
    * @return vrai si le buffer est plein, false s'il est vide
    */
   bool full() const {
      return taille == capacity();
   }
public:
   ArrayDeque(size_type cap = 0) : debut(0), taille(0), capacite(cap){
      buffer = capacite != 0 ?
               (pointer) ::operator new(capacite * sizeof(value_type))
                             : nullptr;

   }

   ArrayDeque(const ArrayDeque& dq) : ArrayDeque(dq.capacity()) {
      for(size_type i = 0; i < dq.taille; i++)
         push_back(dq.at(i));
   }

   ~ArrayDeque() {
      while (taille > 0) {
         pop_front();
      }
      ::operator delete(buffer);
   }

   ArrayDeque& operator= (const ArrayDeque& dq) {
      ArrayDeque<value_type> tmp(dq.capacity());
      for (size_type i = 0; i < dq.capacity(); ++i) {
         tmp.push_back(std::move(dq.at(i)));
      }

      std::swap(tmp.buffer, buffer);
      std::swap(tmp.capacite, capacite);
      std::swap(tmp.debut, debut);
      std::swap(tmp.taille, taille);
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
    * Double la capacité de buffer, sauf si ça capacité = 0 et dans ce cas la capacité devient = 1
    */
   void resize() {
      size_type newCapacity = capacity() ? capacity() * 2 : 1;

      ArrayDeque<value_type> tmp(newCapacity);
      for (size_type i = 0; i < capacity(); ++i) {
         tmp.push_back(std::move(at(i)));
      }

      std::swap(tmp.buffer, buffer);
      std::swap(tmp.capacite, capacite);
      std::swap(tmp.debut, debut);
      std::swap(tmp.taille, taille);
   }

   /**
    * insére un élément a la fin de buffer
    * @param val : valeur a insérer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& push_back(const_reference val) {
      if (full()) {
         resize();
      }

      new(getBufferPointerAt(getLastPhisicalIndex())) value_type(val);
      ++taille;
      return *this;
   }

   /**
    * insére un élément a la fin de buffer
    * @param val : valeur a insérer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& push_back(rvalue_reference val) {
      if (full()) {
         resize();
      }

      new(getBufferPointerAt(getLastPhisicalIndex())) value_type(std::move(val));
      ++taille;
      return *this;
   }

   /**
    * insére un élément en première position de buffer
    * @param val : valeur a insérer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& push_front(const_reference val) {
      if (full()) {
         resize();
      }

      size_type newDebut = debut;
      if(!empty()) {
         newDebut = newDebut ? newDebut - 1 : capacity() - 1;
      }

      new(getBufferPointerAt(newDebut)) value_type(val);
      ++taille;
      debut = newDebut;

      return *this;
   }

   /**
    * insére un élément en première position de buffer
    * @param val : valeur a insérer
    * @return l'objet lui même pour pouvoir chainer les appels
    */
   ArrayDeque& push_front(rvalue_reference val) {
      if (full()) {
         resize();
      }

      size_type newDebut = debut;
      if(!empty()) {
         newDebut = newDebut ? newDebut - 1 : capacity() - 1;
      }


      new(getBufferPointerAt(newDebut)) value_type(std::move(val));
      ++taille;
      debut = newDebut;

      return *this;
   }

   /**
    * @return reference vers le dernier élément de buffer
    */
   const_reference back() const {
      return at(taille - 1);
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
      return at(0);
   }
   /**
    * @return reference vers le premier élément de buffer
    */
   reference front() {
      return const_cast<reference>(const_cast<const ArrayDeque*>(this)->front());
   }

   const_reference at(size_type i) const {
      return buffer[(debut + i) % capacity()];
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
         front().~value_type();
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
      if (!empty()) {
         back().~value_type();
         --taille;
      }

      return *this;
   }

};

#endif /* ArrayDeque_hpp */