1a. `std::unique_ptr` should be used to manage a single non-shareable resource. Its constructor
should be used over the `new` keyword.

1b. `std::shared_ptr` should be used when multiple objects need to access the same resource. Its constructor
should be used over the `new` keyword. Copy semantics should be used to create additional pointers to the same object.

1c.
`std::weak_ptr` should be used when one or more objects need to view and access a resource managed by a `std::shared_ptr`. `std::weak_ptr` is not considered when determining whether the resource should be destroyed
and therefore one can check for a deleted resource by using `lock()`

1d.
`std::auto_ptr` is deprecated as of C++17 and should not be used.

2a.
Move semantics is focused around r-values but it is only with r-values that can confidently assume we are not accidentally 'stealing' another objects resources. R-values are temporary and when passing or returning an r-value by value, it's generally more efficient to use move semantics as opposed to making a copy.

3a.

```
#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
 Resource() { std::cout << "Resource acquired\n"; }
 ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
 auto* res{ new Resource{} };
  // ptr1 and ptr2 both be created using `make_shared()`
 std::shared_ptr<Resource> ptr1{ res };
  // ptr2 should be created using ptr1. With current implementation
  // we have 2 independent shared pointers managing the same resource
 std::shared_ptr<Resource> ptr2{ res };

 return 0;
}
```

3b.

```
#include <iostream>
#include <memory> // for std::shared_ptr

class Foo; // assume Foo is a class that can throw an exception

int main()
{
  // Compiler could dynamically allocate first Foo then second Foo and initialize the two shared_ptrs.
  // If the second Foo allocated throws and exception, the first Foo will not be deallocated because the
  // smart pointer has not been created yet.
  // These smart pointers should be created using `make_shared()`
 doSomething(std::shared_ptr<Foo>{ new Foo{} }, std::shared_ptr<Foo>{ new Foo{} });

 return 0;
}
```
