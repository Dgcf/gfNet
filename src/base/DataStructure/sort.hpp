namespace simsort
{

// 插入排序
template<typename _Ty>
void insertionsort(_Ty data[], int n)
{
    for(int i=0, j; i < n; ++i)
    {
        _Ty tmp = data[i];
        for(j = i; j > 0 && tmp < data[j-1]; j--)
        {
            
        }
    }
}

// 选择排序

// 冒泡排序
template<typename T>
void bubblesort(T data[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        for(int j = n-1; j>0; j--)
        {
            if(data[j]<data[j-1])
            {
                swap(data[j], data[j-1]);
            }
        }
    }
}

// 梳排序
template<typename T>
void combsort(T data[], const int n)
{
    int step = n, j, k;
    while ((step=int(step/1.3))>1)
    {
        for(j = n-1; j>=step; j--)
        {
            k = j - step;
            if(data[j] < data[k])
            {
                swap(data[j], data[k]);
            }
        }
    }

    bool again = true;
    for(int i = 0; i < n-1 && again; i++)
    {
        for(j = n-1, again = false;j>0;j--)
        {
            if(data[j]<data[j-1])
            {
                swap(data[j], data[j-1]);
                again = true;
            }
        }
    }
}


// 快速排序
template<typename T>
void quicksort(T data[], int first, int last)
{
    
}

}
