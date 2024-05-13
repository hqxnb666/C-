​
1. C++ Vector 简介与基本使用
C++ 的 vector 是一个序列容器，用于表示可变大小的数组。它结合了数组的高效元素访问和动态大小调整的灵活性。与静态数组相比，vector 的大小可以根据需要自动调整，这是通过在底层使用动态数组来实现的。当新元素被插入到 vector 中时，如果现有空间不足以容纳更多元素，将会自动重新分配一个更大的数组空间，并将所有现有元素移动到新的存储位置。这个动态扩容机制虽然提供了极大的灵活性，但也可能是性能的瓶颈，特别是在元素频繁插入的情况下。


1.1 Vector 的构造与初始化


vector 提供了多种构造函数：

默认构造函数：创建一个空的 vector。
填充构造函数：创建一个具有初始大小的 vector，每个元素都是拷贝指定值。
范围构造函数：通过迭代器指定的范围来构造 vector。
拷贝构造函数：通过复制另一个 vector 的所有元素来构造新的 vector。
1.2 Vector 的操作
vector 支持多种操作，包括访问（使用 operator[]）、插入（push_back 和 insert）、删除（pop_back 和 erase）和容量调整（resize 和 reserve）。特别需要注意的是，很多操作可能会导致 vector 进行重新分配空间，这将导致已有的迭代器、指针和引用失效。

1.2.1 Vector Iterator 的使用
vector 的迭代器是一种允许遍历容器元素的工具，表现得类似于指针。迭代器对于在 vector 中进行元素访问和修改都非常有用。了解如何正确地使用迭代器对于编写高效和安全的 C++ 代码至关重要。

迭代器类型
正向迭代器 (iterator, const_iterator): 允许读写操作或只读操作，并能向前移动（即递增操作）来访问 vector 的元素。
反向迭代器 (reverse_iterator, const_reverse_iterator): 允许从容器末尾开始向开始方向遍历元素。
迭代器的使用
迭代器最常见的用法是在循环中遍历 vector。例如，使用正向迭代器遍历所有元素：

std::vector<int> v = {1, 2, 3, 4, 5};
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
}
std::cout << std::endl;
基本操作
begin() 和 end(): begin() 返回指向 vector 第一个元素的迭代器，而 end() 返回指向 vector 末尾（最后一个元素的下一个位置）的迭代器。
rbegin() 和 rend(): rbegin() 返回指向 vector 最后一个元素的反向迭代器，rend() 返回指向 vector 开始前一个位置的反向迭代器。
1.2.2 vector 空间增长问题  


capacity的代码在vs和g++下分别运行会发现，vs下capacity是按1.5倍增长的，g++是按2倍增长的。这个问题经常会考察，不要固化的认为，vector增容都是2倍，具体增长多少是根据具体的需求定义的。vs是PJ版本STL，g++是SGI版本STLreserve只负责开辟空间，如果确定知道需要用多少空间，reserve可以缓解vector增容的代价缺陷问题。 resize在开空间的同时还会进行初始化，影响size。
// 如果已经确定vector中要存储元素大概个数，可以提前将空间设置足够
// 就可以避免边插入边扩容导致效率低下的问题了
void TestVectorExpandOP()
{
 vector<int> v;
 size_t sz = v.capacity();
 v.reserve(100); // 提前将容量设置好，可以避免一遍插入一遍扩容
 cout << "making bar grow:\n";
 for (int i = 0; i < 100; ++i) 
 {
 v.push_back(i);
 if (sz != v.capacity())
 {
 sz = v.capacity();
 cout << "capacity changed: " << sz << '\n';
 }
 }
}
 1.2.3 vector 增删查改


 https://github.com/hqxnb666/C-/blob/main/vector.h

1.2.4 vector 迭代器失效问题
迭代器的主要作用就是让算法能够不用关心底层数据结构，其底层实际就是一个指针，或者是对指针进行了 封装，比如：vector的迭代器就是原生态指针T* 。因此迭代器失效，实际就是迭代器底层对应指针所指向的空间被销毁了，而使用一块已经被释放的空间，造成的后果是程序崩溃(即如果继续使用已经失效的迭代器，程序可能会崩溃)。
对于vector可能会导致其迭代器失效的操作有：
1. 会引起其底层空间改变的操作，都有可能是迭代器失效，比如：resize、reserve、insert、assign、push_back等。
#include <iostream>
using namespace std;
#include <vector>
int main()
{
 vector<int> v{1,2,3,4,5,6};
 
 auto it = v.begin();
 
 // 将有效元素个数增加到100个，多出的位置使用8填充，操作期间底层会扩容
 // v.resize(100, 8);
 
 // reserve的作用就是改变扩容大小但不改变有效元素个数，操作期间可能会引起底层容量改变
 // v.reserve(100);
 
 // 插入元素期间，可能会引起扩容，而导致原空间被释放
 // v.insert(v.begin(), 0);
 // v.push_back(8);
 
 // 给vector重新赋值，可能会引起底层容量改变
 v.assign(100, 8);
 
 /*
 出错原因：以上操作，都有可能会导致vector扩容，也就是说vector底层原理旧空间被释放掉，
而在打印时，it还使用的是释放之间的旧空间，在对it迭代器操作时，实际操作的是一块已经被释放的
空间，而引起代码运行时崩溃。
 解决方式：在以上操作完成之后，如果想要继续通过迭代器操作vector中的元素，只需给it重新
赋值即可。
 */
 while(it != v.end())
 {
 cout<< *it << " " ;
 ++it;
 }
 cout<<endl;
 return 0;
}
而有的朋友就要问了：既然是由于it没有被及时更新，那我们为什么不直接传引用呢？

在 C++ 中，迭代器通常以值传递的形式在函数中传递。这是因为迭代器本身通常设计得很轻量（很多情况下，迭代器的实现仅是一个或一组指针），所以按值传递的开销很小。更重要的是，按值传递迭代器可以避免外部修改对内部逻辑的影响，从而保持函数的封装性和独立性。如果迭代器作为引用传递，那么在 insert 或其他修改容器的操作中，如果发生了容器的重新分配，迭代器可能就会指向无效的内存区域。函数外部的代码可能在不知情的情况下继续使用这个已经失效的迭代器，从而引发错误或崩溃。此外，引用传递迭代器可能会让函数的调用者误以为他们传入的迭代器在函数执行后仍然有效，从而忽略了必要的更新迭代器的操作。insert 函数返回新元素插入位置的迭代器，这提供了一种更新和使用新的有效迭代器的安全方式。调用者应该使用这个新返回的迭代器，而不是继续使用之前的迭代器。这种设计促使程序员在每次修改操作后都显式地更新他们的迭代器引用，从而增加代码的安全性和可维护性。

#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 4, 5};
    auto it = vec.begin() + 2; // 指向元素 4
    it = vec.insert(it, 3); // 在 4 之前插入 3

    // 输出新的 vector 内容
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 继续使用 it，现在 it 指向新插入的 3
    ++it; // 安全地移动到下一个元素，即原来的 4
    std::cout << "Next element after 3: " << *it << std::endl;
}
对于erase，如果我们不进行扩容，只删除会不会还会引起迭代器失效呢？

答案是：会的

#include <iostream>
using namespace std;
#include <vector>
int main()
{
 int a[] = { 1, 2, 3, 4 };
 vector<int> v(a, a + sizeof(a) / sizeof(int));
 // 使用find查找3所在位置的iterator
 vector<int>::iterator pos = find(v.begin(), v.end(), 3);
 // 删除pos位置的数据，导致pos迭代器失效。
 v.erase(pos);
 cout << *pos << endl; // 此处会导致非法访问
 return 0;
}
erase删除pos位置元素后，pos位置之后的元素会往前搬移，没有导致底层空间的改变，理论上讲迭代
器不应该会失效，但是：如果pos刚好是最后一个元素，删完之后pos刚好是end的位置，而end位置是
没有元素的，那么pos就失效了。因此删除vector中任意位置上元素时，vs就认为该位置迭代器失效
了。
2. Vector 深度剖析及模拟实现
vector 的实现细节可以深入理解其性能和存储特性。std::vector的核心框架接口的模拟实现bit::vector  

2.1 模拟实现 Vector
深入探讨 vector 的模拟实现可以帮助更好地理解其内部机制。例如，使用 memcpy 进行元素拷贝在面对非平凡数据类型时可能会出现问题，因为 memcpy 只进行浅拷贝。在自定义数据类型涉及深层资源管理时，浅拷贝可能导致资源泄漏或程序崩溃。

使用memcpy拷贝问题
假设模拟实现的vector中的reserve接口中，使用memcpy进行的拷贝，以下代码会发生什么问题？
问题分析：
1. memcpy是内存的二进制格式拷贝，将一段内存空间中内容原封不动的拷贝到另外一段内存空间中
2. 如果拷贝的是自定义类型的元素，memcpy既高效又不会出错，但如果拷贝的是自定义类型元素，并且自定义类型元素中涉及到资源管理时，就会出错，因为memcpy的拷贝实际是浅拷贝
 

结论
通过本文的学习，我们不仅理解了 vector 的基本用法和实现原理，还探讨了其在实际编程中的高级应用。理解这些概念将有助于开发更高效、更健壯的软件系统。对于希望深入学习 C++ 或进行系统性能优化的开发者来说，深入掌握 vector 的使用和原理是非常有价值的。

​
