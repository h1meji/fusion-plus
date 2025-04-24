# Fusion+ Code Style Guide

## Naming Conventions

### Variables
- **Local variables & Public Member variables**: camelCase
  ```cpp
  int itemCount = 0;
  std::string userName = "default";
  ```
- **Private Member variables**: m_camelCase
  ```cpp
  class User
  {
  private:
      int m_userId;
      std::string m_userName;
  };
  ```
- **Constants**: UPPER_SNAKE_CASE
  ```cpp
  const int MAX_USERS = 100;
  constexpr double PI = 3.14159265359;
  ```
- **Global variables**: g_camelCase
  ```cpp
  int g_errorCount = 0;
  ```

### Functions and Methods
- Use PascalCase
  ```cpp
  void CalculateTotal();
  int GetUserCount();
  ```
- Verb-first for actions: `SaveUser()`, `LoadData()`
- Boolean functions use "is", "has", "can": `IsValid()`, `HasPermission()`

### Classes and Types
- **Classes**: PascalCase
  ```cpp
  class UserManager {};
  struct ConnectionParams {};
  ```
- **Namespaces**: lowercase
  ```cpp
  namespace utils {}
  namespace database {}
  ```
- **Enums**: PascalCase
  ```cpp
  enum class ErrorCode {};
  ```
- **Enum values**: UPPER_SNAKE_CASE
  ```cpp
  enum class ErrorCode
  {
      SUCCESS,
      NOT_FOUND,
      PERMISSION_DENIED
  };
  ```
- **Macros**: UPPER_SNAKE_CASE
  ```cpp
  #define MAX_BUFFER_SIZE 1024
  ```

## Code Style

### Formatting
<!-- - **Indentation**: 2 spaces -->
- **Braces**: Opening brace on next line
  ```cpp
  if (condition)
  {
    doSomething();
  }
  ```

### Include Order
1. Related header file
2. C standard library headers
3. C++ standard library headers
4. External libraries
5. Project libraries (use `""`, instead of `<>`)

Example:
```cpp
#include "user_manager.h"  // Related header first

#include <cstdlib>         // C standard library
#include <cstring>

#include <string>          // C++ standard library
#include <vector>
#include <algorithm>

#include <imgui/imgui.h>  // External libraries

#include "database/connection.h"       // Project libraries
#include "utils/logging.h"
```

## General Practices
- Use `nullptr` instead of `NULL` or `0`