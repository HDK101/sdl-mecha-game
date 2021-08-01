#ifndef SOURCE_PRINT_H
#define SOURCE_PRINT_H

#define WRITE_LOG(...) { printf("%s: ", __FILE__); printf(__VA_ARGS__); }

#endif
