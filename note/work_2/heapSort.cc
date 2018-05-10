 ///
 /// @file    heapSort.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-24 23:07:01
 ///
 
#include <iostream>
using std::cout;
using std::endl;

template <typename T,typename Compare=std::less<T>>
class HeapSort
{
public:
	HeapSort(T *arr,int size);
	void heapAdjust();
	void sort();

private:
	T *_arr;
	int _size;
};

HeapSort::HeapSort(T *arr,int size)
:_arr(new T[size+1]())
,_size(size)
{
	memcpy(_arr,arr,size*sizeof(T));

}

heapSort::heapAdjust()
{
	for(int i=_size/2-1;i!=0;i--)
	{
		int left=2*i+1;
		int right=2*i+2;
		int large=i;

		if(left<_size&&arr[left]>arr[i])
		{
			large=left;
		}

		if(right<_size&&arr[right]>arr[large])
		{
			large=right;
		}

		if(large!=i)
		{
			int temp=arr[large];
			arr[large]=arr[i];
			data[i]=temp;
			

		}


	}
}

