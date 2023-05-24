# C++ Guide 

This guide will define parts of c++ that is not an other languages, such as namepaces, pointers, and preprocessor definitions

* Namespaces
* Pointers
* Preprocessing


## Namespaces
Namespaces are used to differentiate functions with the same name. Multiple libraries can have functions with the same name. We need to use a namespace to
clarify which function to use.

## Pointers
A pointer is a variable that stores the memory address of another variable. We can declare a variable `int x = 5` and then declare a pointer to x, `int *p = &x`. A pointer is defined by an asteric either inbetween the data type and the variable name. To store the memory address of x, you use the ampersand to signify the address of x.

```
#include <iostream>

using namespace std;

int main()
{
    int x = 5;
    int *p = &x;

    cout << x << endl;
    cout << p << endl;
    cout << &x << endl;
}
```
### output
```
5
0xecf29ffe54
0xecf29ffe54
 ```
 
 ## Preprocessing
