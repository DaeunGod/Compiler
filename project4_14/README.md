# Project #4
###### code reference: http://www.cs.sjsu.edu/~louden/cmptext
###### 20131612 최대운/ 20131547 김한길

### Obejct
- A Code Generator

### TODO
- Modify code.h/code.c to incorporate frame pointer(fp)
- Extend and modify cgen.h/cgen.c significantly for C- language.
- The code generated should be able to run on SPIM machine.

### Implement
- AST(abstract syntax tree)를 순회하면서 각 노트 타입에 맞는 어셈블리 코드를 생성한다.
- input, output 함수는 사용자가 정의하지 않았지만 시스템에서 만들어줘야하는 입력과 출력으로 이용되는 함수다.
- 모든 연산의 결과나 리턴 값은 $v0에 저장된다.
- 함수 호출에 사용되는 Parameter는 $a0~$a3에 저장된다.
- 

### Execute
- make
- ./project4_14 [testfile].c
- spim -file [testfile].tm
