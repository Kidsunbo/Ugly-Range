//
// Created by SunBo on 2019-05-04.
//

#ifndef UNTITLED_RANGE_H
#define UNTITLED_RANGE_H

#include <iostream>
#include <vector>
#include <functional>

namespace view{
    using namespace std;

    template <typename T>
    class Range{
        vector<T> vec;
        typename vector<T>::iterator v;
    public:
        Range(){}
    public:
        Range(vector<T> t):vec(t){}
        void set(vector<T> t)const{
            this->vec=t;
        }
        auto getVec()const{return vec;}
        virtual Range<T> operator()(vector<T> v) const{};

        auto begin() const{
            return vec.begin();
        }

        auto end() const{
            return vec.end();
        }

    };

    template<typename T>
    class filter:public Range<T>{
        function<bool(T)> f;
    public:
        filter(function<bool(T)> f):f(f){}
        Range<T> operator()(vector<T> v)const{
            vector<T> t;
            for(T& i:v){
                if(f(i))t.push_back(i);
            }
            return Range<T>(t);
        }
    };

    template<typename T,typename R=T>
    class map:public Range<T>{
        function<R(T)> f;
    public:
        map(function<R(T)> f):f(f){}
        Range<R> operator()(vector<T> v)const{
            vector<R> t;
            for(T& i:v){
                t.push_back(f(i));
            }
            return Range<R>(t);
        }
    };

    class max{};

    class min{};

    template<typename T>
    auto operator |(const Range<T>& r1,const Range<T>& r2){
        return r2(r1.getVec());
    }

    template<typename T>
    auto operator |(const vector<T>& v,const Range<T>& r){
        return Range<T>(v)|r;
    }

    template <typename T>
    auto operator |(const Range<T>& r1,view::max){
        auto v = r1.getVec();
        T m = v[0];
        for(auto i:v) m=m>i?m:i;
        return m;
    }

    template <typename T>
    auto operator |(const Range<T>& r1,view::min){
        auto v = r1.getVec();
        T m = v[0];
        for(auto i:v) m=m<i?m:i;
        return m;
    }

    template<typename T>
    auto operator |(const vector<T>& v,view::max){
        return Range<T>(v)|max();
    }

    template<typename T>
    auto operator |(const vector<T>& v,view::min){
        return Range<T>(v)|min();
    }
}



#endif //UNTITLED_RANGE_H
