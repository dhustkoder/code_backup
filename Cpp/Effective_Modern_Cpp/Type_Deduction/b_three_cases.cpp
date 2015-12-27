
// There are three cases for ParamType:

// ParamType is a pointer or reference type, but not a universal reference.

// ParamType is a universal reference.

// ParamType is neither a pointer nor a reference.



template<typename T>
void f(T *);    // T is pointer

void f(T& t);   // T is a reference

template<typename T>
void f(T&& t); // T is a universal reference

template<typename T>
void f(T t);  // T is neither a pointer nor reference.
