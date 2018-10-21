- Indentation is four spaces.

- If the body of an if statement is only one line, omit the braces.
  Example:
```  
    if(true)
    {
        printf("It is true");
    }
```
	
  becomes
  ```
    if(true)
        printf("It is true");
```


- `struct`s are declared in a header file and their fields are shown in
  the source file.
  Example:
```
    struct SomeStruct
    {
        int x;
        double y;
    };
```
  becomes

  - In header file:
```
    typedef struct _SomeStruct SomeStruct;
```
  - In source file:
```
   struct _SomeStruct
   {
        int x;
        double y;
    };
```
  This allows us to control what the user can access directly and what
  they must access using functions that allow reading/writing of the data.

  Braces should be on their own lines.

  Example:

  ```
  if(true) {

  }
  ```

  becomes

  ```
  if(true)
  {

  }
  ```