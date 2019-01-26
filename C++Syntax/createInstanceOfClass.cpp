/*  1) Allocates some dynamic memory from the free store, and creates an object
   in that memory using its default constructor. You never delete it, so the
   memory is leaked. Usage: Don't, unless you like unnecessary decorations on
   your code.
*/
Foo* foo1 = new Foo();

/* 2) Does exactly the same as 1; in the case of user-defined types, the
   parentheses are optional. Usage: When you want to create an object that
   outlives the current scope. Remember to delete it when you've finished with
   it, and learn how to use smart pointers to control the lifetime more
   conveniently.
*/
Foo* foo2 = new Foo;

/* 3) Allocates some automatic memory, and creates an object in that memory
   using its default constructor. The memory is released automatically when the
   object goes out of scope. Usage: When you want an object that only exists in
   the current scope.
*/
Foo foo3;

/* 4) Similar to 3. Notionally, the named object foo4 is initialised by
   default-constructing, copying and destroying a temporary object; usually,
   this is elided giving the same result as 3. Usage: Don't, unless you think 3
   looks boring and what to add some unnecessary decoration.
*/
Foo foo4 = Foo::Foo();

/* 5) Allocates a dynamic object, then initialises a second by copying the
   first. Both objects are leaked; and there's no way to delete the first since
   you don't keep a pointer to it. Usage: Don't, because it leaks memory with no
   chance of recovery.
*/
Bar* bar1 = new Bar(*new Foo());

/* 6) Does exactly the same as 5.
        Usage: Don't, because it leaks memory with no chance of recovery.
*/
Bar* bar2 = new Bar(*new Foo);

/* 7) Does not compile. Foo foo5 is a declaration, not an expression; function
   (and constructor) arguments must be expressions. Usage: Don't, because it
   won't compile
*/
Bar* bar3 = new Bar(Foo foo5);

/* 8) Creates a temporary object, and initialises a dynamic object by copying
   it. Only the dynamic object is leaked; the temporary is destroyed
   automatically at the end of the full expression. Note that you can create the
   temporary with just Foo() rather than the equivalent Foo::Foo() (or indeed
   Foo::Foo::Foo::Foo::Foo()) Usage: When you want to create a dynamic Bar from
   a temporary Foo.
*/
Bar* bar3 = new Bar(Foo::Foo());
