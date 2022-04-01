***Note: To test my functions, I custom-wrote several other functions in `main.cpp`. Some of them are extremely effective (the simpler ones, like generating a 1D vector of ints); others are either a bit too random, leading my functions to always return the same thing, or don't cover some edge cases (like `generateRomanNumeralString`).***
<br>
---
This `README.md` is really just the culmination of things I learned while coding the solutions to the LeetCode problems (see `HashMapSolutions.h` for a list of the problems).
<br>
Let's start with the easiest topics.
---
## Strings (std::string)
There are really only two things here I want to talk about: The `find()` and `substr()` functions.
### std::string.find()
There are several constructors for this function, but I only needed one:<br>
> string (1): size_t find (const string& str, size_t pos = 0) const noexcept;

(...pasted directly from [the CPP Reference Manual](https://www.cplusplus.com/)).
<br>
Notice the two parameters:
1. `const string& str`:
   2. Though I included the constructor that takes a pointer to a string as input, you may also input the pointer to a singular character.
   3. In my experience, for this parameter, you may input either a string literal or a substring.
2. `size_t pos = 0`:
   1. By default, this value is set to 0, meaning the function will search for `const string& str` in the range from `index = 0` to `index = std::string.size() - 1`, inclusive.
      1. If specified, the search will begin at `index = SPECIFICATION` to `index = std::string.size() - 1`, inclusive.

There are two possible outputs of this function:
1. If there is a match, the function returns the index of the starting character of the string you're searching.
2. Otherwise, the function returns `std::string::npos`, equivalent to the size of the string, usually indicating that a math was not found.

### std::string.substr()
There's only one constructor for this function: 
> string substr (size_t pos = 0, size_t len = npos) const;

The `size_t pos = 0` parameter has all the same constraints as before.
<br><br>
The `size_t len = npos`, however, is a bit different:
1. By default, you'll see the second parameter has a value of `npos`. You may either write this in manually, or you may call the `substr()` function, without specifying a `size_t len = npos`. Both produce the same output: Copying all characters from `pos` to the end of the string.  
2. If you decide to specify a value, you may pass in **not** an index, but the **number of characters** you'd like to copy from one string to another.
   1. You will not have to worry if your input value for `len` is longer than the string you're extracting from. The function will simply take as many characters as it can, and return. 
---
   
## rand() and srand()
These are both random number generators. In context, one may be better than the other.

### rand()
By default, you may call this function, as is, and it will return the next random number in the pseudorandom sequence ranging from `0 to RAND_MAX`.
<br>
Note the term "pseudorandom sequence". A pseudorandom sequence is, yes, a random sequence of numbers; however, the sequence of numbers are chosen systematically, such that they are completely deterministic. See the [Wikipedia](https://en.wikipedia.org/wiki/Pseudorandomness).
<br>
Thus, when you call this function repeatedly, say, in a for-loop, the function will simply return the next pseudorandom number within the pseudorandom sequence.
<br><br>
Additionally, you may specify the range of values you'd like to pull from. For instance, you may write:
<br>
`rand() % 100` to pull from values 0 to 99, <br>
`rand() % 100 + 1` to pull from values 1 to 100, or <br>
`rand() % 30 + 1985` to pull from values 1985 to 2014.

### srand()
While `rand()` was a void function, `srand()` takes in an `unsigned int seed`, responsible for producing a true, random sequence of numbers, for each seed. Thus, for every subsequent call to `rand()`, instead of grabbing the next "random" number in the pseudorandom sequence, `rand()` pulls any random number in the specified range.
<br><br>
Typically, the seed is set to `time(NULL)`, which returns the current time, in seconds, the moment this line is executed. Note, though, the `srand()` function is called once, for the most part, and it's probably done at the start of your program. Multiple calls to `srand(time(NULL))` within a short time frame will generate the same sequence of numbers, since the seed will be the same, and at this point, we've regressed to a pseudorandom sequence. 
<br><br>
Moral of the story?<br>
If you need a true random number generator, call `srand(time(NULL))` at the start of your program, and call `rand()`, as you please.
<br>
If you just need to continuously pull a number from a known sequence, use `rand()`. I suppose this might be useful within a for-loop, dedicated to running N test cases. Otherwise, I'm not so sure. We're programmers, though, someone will need it.
---

## Vector (std::vector<>) functions - assign, clear, rbegin vs begin

I touched on vectors before, so I won't necessarily dive into the nitty gritty of how they work. I'm here only to discuss these functions, as I encountered them as I tried to solve problems related to hash maps.

### std::vector<>.assign()

There are three ways to assign content to a vector:
1. For starters, you may do it upon initialization: <br>
`std::vector<int> vec = {1, 2, 3, 4, 5};`

The other two require function calls, with their own constructors:
2. `vec2.assign(auto it = someOtherVec.begin(), auto itEnd = someOtherVec.size()`.
   1. This one's a tad bit verbose. All that really matters is the inputs to this type of function call, called "range".
      1. You may assign either an uninitialized vector, or an initialized vector with the contents of another vector, so long as you have iterators pointing to locations in the vector you're copying from. 
      2. **Note**: The documentation specifies the input parameters as "first" and "last" iterators. This type of function call copies all values from the original vector within the range `[first, last)`. 
3. `vec.assign(7, 10)` -- Assume `vec` is initially empty.
   1. This call is simple. The parameters are `n = 7`, or the number of elements you'd like to be in the vector, and `val == 10`, the value each of the `n` elements will be defaulted to.
   2. I assume this works only for uninitialized/empty vectors. There may be some clashing elements with this type of function call on an already initialized vector. I don't know whether `n` would add to the size of the array, like `push_back()` would, or if it replaces elements in the array from `[0, n]` with `val`.

### std::vector<>.clear()

This function takes no input parameters. It simply takes any vector, and destroys all content within it, resulting in a vector with size 0. 

### rbegin() vs begin()

These functions both return iterators.
1. `begin()` returns an iterator to the beginning of some object, in this case, an array.
   1. Incrementing this returned iterator increases its position, forwards. 
      1. For instance, if you had an iterator pointing to the first location (index = 0) of some vector, after executing `iterator++`, your iterator would then point to the second location (index = 1).
2. `rebgin()` returns an iterator to the **back** of some object.
   1. Incrementing this returned iterator increases its position, **backwards**. 
      1. For instance, the default iterator returned by `rbegin()` points to the last element in the vector (*i.e.*, the size of the vector, minus one). Incrementing this iterator via `rIterator++` increases its position **backwards**, so that it now points to the size of the vector, minus two (*i.e.*, the penultimate, or second-to-last, element in the vector).
      
I'll touch on iterators next, but consider them just as pointers, for now.
<br><br>
What's important here is:<br>
Both of these functions are extremely useful for, well, iterating through some object. The issue lies within whether you're calling other functions which *require* iterators.<br>
Technically, an iterator is **not** the sae as a reverse iterator, so an attempt to pass a reverse iterator into a function that requires an iterator will produce an error.<br><br>
Keep this in mind when you try calling a function that requires an iterator, and not a reverse iterator, or vice versa. Or, I don't know, create the exact same function that takes, as input, a reverse iterator, instead.
---
## Iterators, auto, and auto&

### Iterators

Iterators are actually quite simple. They follow, generally, the same syntax as any other data type you'd use to iterate through and grab values from some container:
1. You may increment, `iterator++`, the iterator;
2. Decrement it, `iterator--`;
3. You may dereference it, `*iterator`.

Pointers *are* iterators. Though, different kinds of iterators exist for different kinds of containers, and those iterators may have their own set of functions/abilities unavailable to other iterators.<br>
This is made possible due to the function template features of C++. I'm not going to dive into templates here, though. Just know that's what provides us with different types of iterators. Visit the iterator reference [here](https://www.cplusplus.com/reference/iterator/), and the function template reference [here](https://www.cplusplus.com/doc/oldtutorial/templates/). If confused about what types of iterators you should be using, visit the reference manual for the data type/structure you're working with. In my experience, there are built in functions, like `auto it = vec.begin()`, that return iterators. 

### auto vs auto&
At its base, you can use `auto` in place of a data type when declaring a variable (*i.e.*, `auto randNum = 7`). The compiler will figure out `randNum` is of integer type. The same goes for `decltype()`.
<br><br>
When used in conjunction with iterators and loops, the `auto` keyword becomes a bit more complicated.<br>
Typically, when defining an iterator, I'd always use:<br>
`for (auto it = someObject.begin(); it != someObject.end(); it++`
I'd do this specifically if I needed to access every element within, in my experience, a hash map. It seemed easier this way, instead of writing: <br>
` for (auto& it : someObject)`, <br>
as then I'd have to deal with the abstractions of hash maps, like buckets, and the first/second of specific buckets. The first way, I could simply write: `it.first and it.second, or someObject[it.first]`.
<br><br>
But there are two different uses of `auto` there. What's the difference?
<br>
For starters, I'd visit this [StackOverflow post](https://stackoverflow.com/questions/29859796/c-auto-vs-auto). This seems to have covered `auto`, `auto&`, and `auto&&` in depth. Though, I never used `auto&&`, so I won't be covering it.
<br>
Really, I'll only cover the use of `auto` and `auto&` in range-based for-loop's:
<br><br>
Pulling directly from the SO post:<br><br> *"Use auto when you need a local copy. This will never produce a reference. The copy (or move) constructor must exist, but it might not get called, due to the copy elision optimization."* <br><br>
Pay attention to the "local copy" part. They're suggesting that, when you have a for-loop of the form, <br>
`for (auto num : nums)`--assume there's an integer vector called nums, <br>
then, by using the `auto` keyword, `num` is a temporary copy of the Nth element in `nums`, which can be modified easily, but will **not** change the contents of the vector `nums`. 
<br><br>
*"auto & guarantees that you are sharing the variable with something else. It is always a reference and never to a temporary"*
<br><br>
Here, notice the phrase "..sharing the variable with something else." In this case, the "something else" is the `nums` vector. `num` still has the same value's as before; now, it's just a reference. Thus, it is **still modifiable**, and modifying said `num` will effectively **change the contents of the vector `nums`**.<br>
Sometimes, it may be safer to use `auto const &`, if you'd like a reference variable that is **non-modifiable**.
---

## std::unordered_map; more functions

### map.at()/map[] vs map.find()
These are pretty simple, too. Follow the general rule of thumb: <br><br>
If you need to search through the keys within your map, use `someMap.find()`. It will return an iterator to the element, if found, and an iterator to the end of your map (`someMap::end`), if not found.
<br>
If looking for the mapped value of a certain key within your map, use `someMap.at()`. The return value will be a reference to the mapped value at the key you provided to the function.
<br>
The `[]` operator acts in the same way that `someMap.at()` works. 

### map.clear()
The outcome is the same as clearing a vector, but the procedure behind the scenes is slightly different. We don't need to worry about these, though. We simply call:<br>
`someMap.clear()`<br>
and go about our day. We now have an empty map of size 0.
---
## Multimap; it.first/second, instead of map.at/map[]

### Multimap's (std::unordered_multimap)
The difference between an unordered multimap and an unordered map is the uniqueness of keys.<br><br>
In an unordered map, you're only "allowed" to have unique keys. That is, a specific key should not be associated with two different mapped values. *Technically*, you *can* do this, but you will **not** get the result you want. Accessing the mapped value from whichever repeated key will return the mapped value of the first instance of that key within the map.
<br>
In an unordered multimap, you *are* allowed to have identical keys. The only immediate issue is how to distinguish between keys for specific mapped values.

### it.first/second, instead of map.at()/map[]
Using `someMap.at()` or the `[]` operator are not your friends here. I have a strange feeling their behavior will be wildly similar to accessing the mapped value of a shared key in an unordered map. You will get back whichever is first in the map.<br> 
Thus, for me, in my experience, I used `it.first` and `it.second`. *Technically*, I believe that, even if you used this method, the multimap may return values you did not expect. This method probably only worked for me since I needed to iterate through the entirety of a map, so, either way, I needed to access every element.<br>
If you're searching for a specific mapped value in a multimap, this may require an additional if statement, or even a searching algorithm at your fingertips.
---
This is what I learned in my elementary introduction to hash maps.<br>
That is all for today.<br>
Happy coding!