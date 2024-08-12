#include "inc/ConcurrentHashMap.h"
#include <thread>
#include <iostream>
#include <mutex>

// we will test on (int,int) key-value pairs
std::mutex mt;   // will be used to lock cout to avoid both threads printing on same line

void thread1_work(CHML::ConcurrentHashMap<int,int> & mp){
    {
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"thread 1 started"<<std::endl;
    }
    mp.insert(1,10);
    mp.insert(2,20);
    mp.insert(3,9);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    int value;
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    if(mp.find(10,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: Key= "<<10<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: key= "<<10<<" does not exists in map"<<std::endl;
    }

    mp.insert(2,30);
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    mp.erase(2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    mp.insert(2,50);
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    mp.clear();
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread1:: key= "<<2<<" does not exists in map"<<std::endl;
    }

}


void thread2_work(CHML::ConcurrentHashMap<int,int> & mp){
    {
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"thread 2 started"<<std::endl;
    }
    mp.insert(1,100);
    mp.insert(2,200);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mp.insert(3,300);

    int value;
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    if(mp.find(10,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: Key= "<<10<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: key= "<<10<<" does not exists in map"<<std::endl;
    }

    mp.insert(2,70);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    mp.erase(2);
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    mp.insert(2,50);
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: key= "<<2<<" does not exists in map"<<std::endl;
    }

    mp.clear();
    if(mp.find(2,value)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: Key= "<<2<<" exists with value= "<<value<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<"Thread2:: key= "<<2<<" does not exists in map"<<std::endl;
    }

}

int main(){
    CHML::ConcurrentHashMap<int,int> mp;
    std::thread thread1(thread1_work,ref(mp));
    std::thread thread2(thread2_work,ref(mp));
    thread1.join();
    thread2.join();
    return 0;
}


