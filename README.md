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