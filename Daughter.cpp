#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>

void merge(std::vector<int> &arr, int left,
           int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int partition(std::vector<int> &vec, int low, int high)
{

    int pivot = vec[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (vec[j] <= pivot)
        {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[high]);

    return (i + 1);
}

void quickSort(std::vector<int> &vec, int low, int high)
{

    if (low < high)
    {

        int pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main(int argc, char *argv[])
{
    std::string input = argv[1];
    std::istringstream s(input);
    int num;
    std::vector<int> numbers;
    while (s >> num)
    {
        numbers.push_back(num);
    }

    if (argv[2][0] == '1')
    {
        mergeSort(numbers, 0, numbers.size() - 1);
    }
    else if (argv[2][0] == '2')
    {
        quickSort(numbers, 0, numbers.size() - 1);
    }

    std::cout << "Result: ";
    for (int number : numbers)
    {
        std::cout << number << ' ';
    }
    std::cout << '\n';
}
