int nua;
int nub;
int aaa;

int power(int base, int n){
    int i;
    int p;

    p = 1;
    i = 0;
    while(i<=n){
        p = p * base;
        i = i + 1;
    }
    return p;
}

int gcda(int a, int b){
    int tmp;
    int n;

    if( a < b ){
        tmp = a;
        a = b;
        b = tmp;
    }

    while( b != 0){
        int re;
        re = a/b;
        n = a - b * re;
        a = b;
        b = n;
    }

    return a;
}

int gcdb(int a, int b){
    if( b == 0 ){
        return a;
    } else {
        int re;
        re = a/b;
        return gcdb(b, a-b*re);
    }
}

void main(void){
    int i;
    int resulta;
    int resultb;

    input(aaa);
    i = 1;
    while(i<aaa){
        int tmp;
        tmp = power(2, i);
        output(tmp);
        i = i + 1;
    }

    input(nua);
    input(nub);

    resulta = gcda(nua, nub);
    resultb = gcdb(nua, nub);

    output(resulta);
    output(resultb);
}
