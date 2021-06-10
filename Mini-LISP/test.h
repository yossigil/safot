#include "io.h"
#include "basics.h"
inline auto operator == (const S s1,const S s2) { return s1.handle == s2.handle; }
inline auto operator != (const S s1,const S s2) { return s1.handle != s2.handle; }

inline S parse(const char *s) {
    Parser::reset();
    Parser::supply(strdup(s));
    if (Parser::status() != Parser::Status::accept) {
        throw std::runtime_error("Unexpected parser error"); // should not be here - we assume all unittest inputs are valid
    }
    return Parser::result();
}

inline S parse(const std::string& s) {
    return parse(s.c_str());
}

#define STRINGIFY(X) #X 

#define LINE_STRING STRINGIZE(__LINE__)
#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x

#define UNIQUE "UNIQUE" LINE_STRING

#define CAREFULLY(...) try { __VA_ARGS__; } catch (Pair p) { \
  ADD_FAILURE() << p << " exception on " << #__VA_ARGS__; }  

#define EXPECT_EXCEPTION(x, value, code)  \
{ \
  bool caught = true; \
  try{\
    x;\
    caught = false; \
  } catch (Pair p) { \
    EXPECT_EQ(p.cdr, code); \
    EXPECT_EQ(p.car, value); \
  } \
  if (!caught) \
      ADD_FAILURE() << "Evaluating " << #x << " should have thrown " << S(value,code); \
}
