#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int nums[], int length);
void selectionSort(int nums[], int length);
void insertionSort(int nums[], int length);
void mergeSort(int nums[], int length);
void quickSort(int nums[], int length);

// auxiliary function
void __mergeSort_split(int nums[], int start, int end);
void __mergeSort_merge(int nums[], int start, int mid, int end);
void __quickSort(int nums[], int start, int end);

int main() {
    int nums[] = {5, 3, 2, 6, 32, 21, 35, 65, 1, 9};
    int length = sizeof(nums) / sizeof(int);

    // [Info] uncomment one line to execute one sort algorithm
    // bubbleSort(nums, length);        // 1.
    // selectionSort(nums, length);     // 2.
    // insertionSort(nums, length);     // 3.
    // mergeSort(nums, length);         // 4.
    // quickSort(nums, length);         // 5.

    // display the array "nums[]"
    for (int i = 0; i < length; i++) {
        printf("%d%s", nums[i], i == length - 1 ? "\n" : " ");
    }

    return 0;
}


void bubbleSort(int nums[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1 - i; j++) {
            if (nums[j] > nums[j+1]) {
                // swap(nums[j], nums[j+1])
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}

void selectionSort(int nums[], int length) {
    for (int i = 0; i < length - 1; i++) {
        int minIndex = i;
        for (int j = i+1; j < length; j++) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }

        // swap(nums[i], nums[minIndex]);
        int temp = nums[i];
        nums[i] = nums[minIndex];
        nums[minIndex] = temp;
    }
}

void insertionSort(int nums[], int length) {
    for (int i = 1; i < length; i++) {
        int preIndex = i-1;
        int currentValue = nums[i];
        while (preIndex >= 0 && nums[preIndex] > currentValue) {
            // move nums[preIndex] backward one step
            nums[preIndex+1] = nums[preIndex];
            preIndex--;
        }
        nums[preIndex+1] = currentValue;
    }
}

void mergeSort(int nums[], int length) {
    __mergeSort_split(nums, 0, length-1);
}

void __mergeSort_split(int nums[], int start, int end) {
    // prevent the index overflow
    int mid = start + (end - start) / 2;

    if (start >= end) {
        return ;
    }

    __mergeSort_split(nums, start, mid);
    __mergeSort_split(nums, mid+1, end);

    __mergeSort_merge(nums, start, mid, end);
}

void __mergeSort_merge(int nums[], int start, int mid, int end) {
    int *buffer = (int*)malloc((end-start+1) * sizeof(int));
    int cur_left = start;
    int cur_right = mid+1;
    int cur_buffer = 0;

    while (cur_left <= mid && cur_right <= end) {
        if (nums[cur_left] <= nums[cur_right]) {
            buffer[cur_buffer++] = nums[cur_left++];
        } else {
            buffer[cur_buffer++] = nums[cur_right++];
        }
    }

    // only one of the two "while" code blocks will be executed
    while (cur_left <= mid) {
        buffer[cur_buffer++] = nums[cur_left++];
    }
    while (cur_right <= end) {
        buffer[cur_buffer++] = nums[cur_right++];
    }

    for (int i = 0; i < cur_buffer; i++) {
        nums[start + i] = buffer[i];
    }

    free(buffer);
}

void quickSort(int nums[], int length) {
    __quickSort(nums, 0, length-1);
}

void __quickSort(int nums[], int start, int end) {
    if (start >= end) {
        return ;
    }

    // there are many ways to determine pivot
    int pivot = start;
    int index = pivot;
    for (int i = index + 1; i <= end; i++) {
        if (nums[i] < nums[pivot]) {
            index++;

            // swap(nums[i], nums[index]);
            int temp = nums[i];
            nums[i] = nums[index];
            nums[index] = temp;
        }
    }

    // swap(nums[index], nums[pivot])
    int temp = nums[index];
    nums[index] = nums[pivot];
    nums[pivot] = temp;

    __quickSort(nums, start, index-1);
    __quickSort(nums, index+1, end);
}