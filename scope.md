Example of scope 

```c++
//Header
class Foo{
private:
int i;
public:
Foo();
int bar1();
int bar2();
void printI();
};
```

```c++
Foo::Foo{
  i = 0;
}

int Foo::bar1(){
  int i = 1;
  return i;
}
int Foo::bar2(){
  return i;
}
void Foo::bar3(){
  printf("Print bar1: " + bar1() + "\n");
  printf("Print bar2: " + bar2() + "\n");
}

```
