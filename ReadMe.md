# Concurrent Thread Safe Hash Map implementation in C++
All source files are in inc. I will explain all in detail below:

## Implentation
This implementation of hash map is thread safe. It is quite optimal and efficient. I did not created a complete class implementation with iterators and other features, but created only general methods that I will be using in my Project Multithreading Cache implementation.

#### Basic approach
The basic approach to make hash map thrad safe is to keep lock on entire structure, but this is completely inefficient

### Better approach
Lets first define certain terms and data structures that are used in this approach.
1. HashNode-> A node in a linkedlist with key-value pair and next pointer
2. HashBucket -> linkedlist of HashNodes
   
We will create an array of HashBuckets and will store all the key-value pairs in corresponding Hash Buckets as HashNode. The size of the array has greate impact on efficiency. If it is too small, then it operations like insert,erase, find, etc perform same as on linkedlist; If too large , there will be empty spaces in array, so extra unnecessary memory usage occurs.
The index of array to which given key-value belongs depends on the hash value of key and size of array selected. the convention we are using is
>array index = hash_value(key)%array_size;

Hash Function should also be good enough for better distribution of key-value pairs.

###### For locking, I used shared_mutex which allows multiple reads at the same time , but single write at a tiime. The reason for choosing this lock is that I will be using this implementation for multithreaded cache implentation and In cache system, the cache miss is very low , so there will be very less number of writes as compared to reads.

### additional comments are provided in the code for better understandings



## API
+ ConcurrentHashMap(HashSize)
  Creates an ConcurrentHashMap with HashSize no of buckets

+ find(key, value)
  If key is present in map , then corresponding value is copied into provided value parameter and function return true, otherwise it return false

+ insert(key, value)
  Inserts new key-value in map if key is not present in map, otherwise updates value of the key in map 

+ erase(key)
  remove entry corresponding to given key in the map

+ clear()
removes all entries from map




