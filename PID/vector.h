//This Vector class is used everywhere in this whole program when we want to store an array of information

#ifndef VECTOR_H
#define VECTOR_H
// #include <iostream>
// #include <string>
// using namespace std;

template <class T>
class Vector
{
public:
    Vector();
    //deallocate function
    ~Vector();
    //copy constructor
    Vector(const Vector& vector);
    //copy assignment
    Vector& operator =(const Vector& vector);
    //add one more element at the end of the Vector
    void Add(T ToAdd);
    //find the ToDelete item and delete it
    void Delete(T ToDelete);
    //delete the item at this index
    void Delete(unsigned long index);
    //insert the ToInsert item at the index position
    Vector<T> Insert(T ToInsert, int index);
    //return the index of this ToFind item
    //if didnt find, return -1
    int Find(T &ToFind);
    //return the item at that index
    T& operator [](int index);
    T& at(int index);
    template <class S>
    friend ostream& operator<<(ostream& outs, Vector<S>& vector);

    //return the size of the Vector
    int getSize();
private:
    T* list;
    int size;
};

//used in the Add function in Vector class
//1. allocate new array with one more space
//2. copy the original array to the new array
//3. add new element at the end of array
//4. delete the original array
template <class T>
void addEntry(T* &SourceArray,int& size, T newEntry);

//used in the Delete function in Vector class
//1. allocate new array with one less space
//2. copy from 0 to the positionToDelete
//3. skip the deleting one and copy rest of the array
//4. delete the original array
template <class T>
void deleteEntry(T* &SourceArray, int &size, int positionToDelete);

//used in the addEntry and deleteEntry function
//also used in Insert Function in Vector class
template <class T>
void copy(T* SourceArray, T* DestinationArray, int count);

//used in the Find function in the Vector class
//1. initial the index = -1
//2. if find the element, return its index
//3. if didnt find the element, return index=-1
template <class T>
int Search(T* SourceArray, T& entryToDelete,int size);

//used in addEntry and deleteEntry
//also used in Insert Function
template <class T>
T* Allocate(int size,const T*type);



template <class T>
Vector<T>::Vector()
{
    size=0;
    list=new T[0];
}
template <class T>
Vector<T>::~Vector()
{
//    cout << "Vector getting deallocated" << endl;
    delete[] list;
}

template <class T>
T& Vector<T>::operator [](int index)
{
    return list[index];
}

template <class T>
T& Vector<T>::at(int index)
{
    return list[index];
}

template <class T>
int Vector<T>::getSize()
{
   return size;
}

template <class T>
T* Allocate(int size,const T* type)
{
    T* DestinationArray=new T[size];
    return DestinationArray;
}

template <class T>
Vector<T>::Vector(const Vector &vector)
{
    int count=vector.size;
    size = vector.size;
    T* source=vector.list;
    T* destination=Allocate(count, source);
    copy(source,destination,count);
    list=destination;
}


template <class T>
void copy(T* SourceArray, T* DestinationArray, int count)
{
    T* sourceWalker=SourceArray;
    T* destiWalker=DestinationArray;
    for(int i=0;i<count;i++)
    {
        *destiWalker=*sourceWalker;
        destiWalker++;
        sourceWalker++;
    }

}

template <class T>
Vector<T> &Vector<T>::operator =(const Vector& vector)
{
    if(this==&vector)
    {
        return *this;
    }
    delete[] list;
    int count=vector.size;
    size=count;

    list=Allocate(count,list);
    T* destination=list,* source=vector.list;
    copy(source,destination,count);
    list=destination;
    return *this;
}


template <class T>
void Vector<T>::Add(T ToAdd)
{
    addEntry(list,size,ToAdd);
}


template <class T>
void Vector<T>::Delete(T ToDelete)
{
    int PositionToDelete=Search(list,ToDelete,size);
    deleteEntry(list,size,PositionToDelete);
}

template <class T>
void Vector<T>::Delete(unsigned long index)
{
    deleteEntry(list,size,index);
}

template <class T>
Vector<T> Vector<T>::Insert(T ToInsert, int index)
{
   T* type=NULL;
   T* destinationArray=Allocate(size+1,type);
   T* desti_walker=destinationArray;
   T* source_walker=list;
   copy(source_walker,desti_walker,index);
   desti_walker+=index;
   *desti_walker=ToInsert;
   desti_walker++;
   source_walker+=index;
   copy(source_walker,desti_walker,size-index);
   size++;
   delete []list;
   list=destinationArray;
   return *this;
}

template <class T>
void addEntry(T* &SourceArray, int& size, T newEntry)
{
    //allocate new array with with one more size
    T* newDynamicArray=NULL;
    newDynamicArray=Allocate(size+1,SourceArray);

    T* SourceArrayWalker=SourceArray;
    T* newDynamicArrayWalker=newDynamicArray;

    //copy the original to destination for the size of elements
    copy(SourceArrayWalker,newDynamicArrayWalker,size);
    size++;
    newDynamicArrayWalker+=size-1;

    //add new element at the end of the array
    *newDynamicArrayWalker=newEntry;

    //delete and point to new array with one more size
    delete[] SourceArray;
    SourceArray=newDynamicArray;
}

template <class T>
void deleteEntry(T* &SourceArray, int &size, int positionToDelete)
{
    if(positionToDelete>=0)
    {
        int count=0;

        //allocate new array with with one less size
        T* newDynamicArray=NULL;
        newDynamicArray=Allocate(size-1,newDynamicArray);

        size--;

        T* SourceArrayWalker=SourceArray;
        T* newDynamicArrayWalker=newDynamicArray;

        count=positionToDelete;

        //copy from index 0 to positionToDelete
        copy(SourceArrayWalker,newDynamicArrayWalker, count);

        SourceArrayWalker+=positionToDelete+1;
        newDynamicArrayWalker+=positionToDelete;
        count=size-positionToDelete;

        //copy from positionToDelete+1 to the end
        copy(SourceArrayWalker,newDynamicArrayWalker, count);

        //delete and point to new array with one less size
        delete[] SourceArray;
        SourceArray=newDynamicArray;
    }
}


template <class T>
int Vector<T>::Find(T& ToFind)
{
    return Search(list,ToFind,size);
}

template <class T>
int Search(T* SourceArray, T& entryToDelete, int size)
{
    T* temp=SourceArray;
    for(int i=0;i<size;i++)
    {
        if(*temp==entryToDelete)
        {
           return i;
        }
        temp++;
    }
   return -1;
}

template <class TT>
ostream& operator<<(ostream& outs, Vector<TT>& vector)
{
    TT* temp=vector.list;
    for(int i=0;i<vector.size;i++)
    {
        outs<<*temp<<" ";
        temp++;
    }
    return outs;
}
#endif // VECTOR_H
