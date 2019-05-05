# Ugly Range

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

This is a tiny range library inspired by stream in Java and Range library in C++20.

It's just a try to use C++14 to implement some basic range functionalities. It still need to provide the type information, but if I write some helper function, it will be helpful and more beautiful. To achieve most of the functionalities, we need C\++20, which already has such functionality.

# Features

  - Filter vectors with lambda
  - Map to each item.
  - Get the max and the min.


# Defect

- Value type needed. But it can be deducted by helper function.
- Only several function has been implemented. It's just a toy code for me to implement such feature, so it's far from perfect and won't be perfected I think.
- Because I have to do my revision for the exam, I don't have enough time to consider performance, not to mention the right value and left value.

# Usage
```c++
vector<int> hello{1,2,3,4,5};
```
Given a container like this.
```c++
    for(auto i:hello
    |filter<int>([](auto x){return x%2==0;})
    |map<int>([](auto x){return 2*x;}))
    {
        std::cout<<i<<std::endl;
    }
```
It will output 4 and 8 with the help of range.

```c++
auto mx= hello|view::max();
auto mn = hello|view::min();
```
It's also easy to get the max and the min value in a container.

# Future
Even though I don't think it has a future, but maybe I will modify it to fit all kinds of container rather than vector if I am boring. See you.

# Experimental
I have fitted it into all container which has `begin`,`end`,`value_type` and `iterator`. You can test it in the experimental namespace.
Here is a demo:
```c++
list<int> hello{1,2,3,4,5};
for(auto i:hello
    |filter<list<int>>([](auto x){return x%2==0;})
    |map<list<int>>([](auto x){return 2*x;}))
    {
        std::cout<<i<<std::endl;
    }
```
```c++
vector<int> hello1{1,2,3,4,5};
for(auto i:hello1
    |filter<vector<int>>([](auto x){return x%2==0;})
    |map<vector<int>>([](auto x){return 2*x;}))
    {
        std::cout<<i<<std::endl;
    }
```
OK, I am gonna sleep now. It's half to mid night in UK.

# OOP
I still provide the OOP interface in the namespace experimental2. It totally imitates the Stream system in `Java8`. It works fine and the example code is listed below:
> Get the Stream object:
```c++
auto a = getStream(hello);
// auto a = std::move(getStream(hello)); This will use move constructor
```
This line of code will create a temporary stream object and then assign it to a with copy constructor. If using move function, it will force to use move constructor.

> Add function
```c++
 auto temp = [&,f](){  };
```
It worth noticing that **I use value capture to get the function object. Because even though I need to use referece to assign new value to the container, but the function object is a local variable, which will be freed when the method ends. But for lambda funtion, it will be executed later in the program, so use value capture to get a copy of the function object will work fine.**

> GetStream function
```c++
template <typename T>
stream<T> getStream(T t){
    return stream<T>(t);
}
```

This is a helper function to create a stream without inputing the type arguments. 
**CAUTION**: DO NOT USE `stream<T>&&` AS RETURN TYPE. 
Because when using referece as return type, the local variable will always be freed, and then use move constructor to create a new object. In the move cosntrutor, the code assigns the two container (one is data, one is action) of the original temporary object which have been destroyed to the new one. So the actions and the data only contains undefined contents, which will cause crash of the program.
But when using `stream<T>` as the return type, the compiler will use RVO or NRVO (if the name is provided), where the original data won't be destroyed. So the whole program can run properly.

> Register the actions
```c++
a = a.filter([](auto x) {return x % 2 == 0;}).map([](auto x) {return 3 * x;});
```
It will register two actions into the stream, the actions will not be executed now.

> Run the actions
```c++
	for (auto i : a) {
		cout << i << endl;
	}
```
The actions will be executed in the `begin()` method, so that actions will be applied into the stream.

> DO NOT CREATE A STREAM LIKE THIS
```c++
	auto a = getStream(hello1).filter([](auto x) {return x % 2 == 0;}).map([](auto x) {return 3 * x;});
```
 Mostly, it will have no effect on the result. The result will still be the same as original one. No action will perform properly. That's because **in this statement, the actions has been registered into the temporary stream object. Then  the object will be assigned to another object named `a`. When the final operation or loop begins, the actions will be executed but they only influence the original container, which belongs to the temporary object, and there will be no effect on `a`. So the result could always be wired.** 
 
 # Conclusion
 Alright, I have finish most of the toy code, it implements OOP, performing on vector and performing on all kinds of containers. I don't think I will improve it later. I have other things to do :)