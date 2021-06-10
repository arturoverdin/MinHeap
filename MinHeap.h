#include <algorithm>
#include <vector>
#include <stdexcept>

template <class T>
  class MinHeap {
     public:

      /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/
      MinHeap (int d);
      ~MinHeap ();

      /* adds the item to the heap, with the given priority. */
      void add (T item, int priority);

      /* returns the element with smallest priority.  
        Break ties however you wish.  
        Throws an exception if the heap is empty. */
      const T & peek () const;

      /* removes the element with smallest priority.
          Break ties however you wish.
          Throws an exception if the heap is empty. */
      void remove ();
         
      /* returns true iff there are no elements on the heap. */
      bool isEmpty() const;
       

    private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
      std::vector<std::pair<T, int> > minStorage;
      int index;
      int dary;
      
  };


  template <class T>
  MinHeap<T>::MinHeap (int d) : dary(d) { index = -1;}


  template <class T>
  MinHeap<T>::~MinHeap () {}

  template <class T>
  void MinHeap<T>::add (T item, int priority) {

    /* creates item and updates index*/
    std::pair<T, int> minItem(item, priority);
    index++;

    if(isEmpty()) 
    {
      minStorage.push_back(minItem);

    } else {

      minStorage.push_back(minItem);

      int tempIndex = index;
      int parent = (tempIndex-1)/dary;
      
      /* while the child has a smaller priority than it's parent
         it will be moved up */
      while(minStorage[tempIndex].second < minStorage[parent].second) 
      {
        std::swap(minStorage[tempIndex], minStorage[parent]);
        tempIndex = parent;
        parent = (tempIndex-1)/dary;
      }
    }        
  }

  template <class T>
  const T& MinHeap<T>:: peek () const {

    if(isEmpty()) 
    {
      throw std::out_of_range("MinHeap is empty");

    } else {

      return minStorage[0].first;

    }
  }

  template <class T>
  void MinHeap<T>::remove () {

    if(isEmpty()) 
    {
      throw std::out_of_range("MinHeap is empty");
      
    } else if(minStorage.size() == 1) {

      minStorage.pop_back();
      index--;

    } else { 

      /* makes first value equal to last, deletes last node, 
      and updates index value of the last number */

      minStorage[0] = minStorage[index];       
      minStorage.pop_back(); 
      index--; 

      int parent = 0;
      int minIndex = (dary*parent)+1;

      while(minIndex <= index)  
      {
        /* finds the index of smallest priority child*/
        for(int i = 1; i <= dary; ++i) 
        {
          if( ((parent * dary) + i) > (int)minStorage.size()) {
            break;
          } else {
            if(minStorage[(parent * dary) + i].second 
                < minStorage[minIndex].second) 
            { 
              minIndex = (parent*dary)+i;
            }
          }
        }
          
        /* swaps the value at parent node and minimum index iff the 
           priority at the parent is larger than the childs */
        if(minStorage[parent].second > minStorage[minIndex].second) 
        {
          std::swap(minStorage[minIndex], minStorage[parent]);

        } else 
        {
          break;
        }

        /* reinitializes all of the parent and child indexes*/
        parent = minIndex;
        minIndex = (dary*parent) + 1;  

      }
    }
  }

  template <class T>
  bool MinHeap<T>::isEmpty() const {return minStorage.empty();}