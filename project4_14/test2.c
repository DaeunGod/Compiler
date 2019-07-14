int cnt;
int arr[10];

void swap(int i, int j){
    int tmp;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int init(void){
    int c;
    int i;
    i = 0;
    input(c);
    while(i<c){
        input(arr[i]);
        i = i+1;
    }
    return c;
}

void print(void){
    int i;
    i = 0;
    while(i<cnt){
        output(arr[i]);
        i = i + 1;
    }
}

void bubbleSort(void){
    int i;
    int j;
    int temp;

    i = 0;
    while(i<cnt){
        j=0;
        while(j<cnt){
            if(arr[i] < arr[j])
                swap(i, j);
            j = j + 1;
        }
        i = i + 1;
    }
}

void main(void){
    cnt = init();
    bubbleSort();
    print();
}