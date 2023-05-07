#import "netAPI.h"

// ---Коды ошибок---
#define OK          0
#define GEN_ERR    -1
#define WRITE_ERR  -2
#define READ_ERR   -3

// ---Константы---
#define WRITE       1
#define OUTPUT      2
#define SERVER      3
#define USER        4

class DATABASE {
public:
    void init_db(FILE *);
    void database(FILE *);
    void output_database(FILE *);
    void write_data(FILE *, core::int8_t *);
    void recv_data(sockaddr_in, void *, core::int8_t *);
};