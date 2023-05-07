#import "libs/database.h"

struct etc {
    core::int32_t   columns;
    core::int32_t     lines;
    core::int32_t condition;
}  __attribute__ ((packed));

SPtr<net>           api;
SPtr<DATABASE> data_api;

void DATABASE::init_db(FILE *file) {
    if (file == NULL) exit(GENERAL_ERROR);
}

void DATABASE::database(FILE *file) {
    sockaddr_in addr;
    SPtr<core::int8_t> buffer_t (1024);

    api.memory() -> init_socket(&addr, LISTENER, STANDART_PORT);
    if(api.memory() -> init(2, addr) != OK) { std::cout << "[!]Init error..."; exit(INIT_ERROR); }

    data_api.memory() -> init_db(file);

    while(1) {
        recv_data(addr, buffer_t.memory(), "_");
        printf("[DEBUG] write_f addr: %p - %s\n", buffer_t.memory(), buffer_t.memory());

        data_api.memory() -> write_data(file, buffer_t.memory());
        bzero(buffer_t.memory(), buffer_t.size());
    }
}

void DATABASE::output_database(FILE *file) {
    SPtr<core::int8_t> out_buffer(102400);
    file = fopen("/var/database", "r");
    data_api.memory() -> init_db(file);
    for (int i = 0; !feof(file); i++)
        fscanf(file, "%c", out_buffer[i]);
    printf("%s", out_buffer.memory());
    fclose(file);
}

void DATABASE::write_data(FILE *file, core::int8_t *buffer) {
    file = fopen("/var/database", "a");
    fprintf(file, "%s\n", buffer);
    fclose(file);
}

void DATABASE::recv_data(sockaddr_in addr, void *data_t, core::int8_t *string_char) {
    SPtr<core::int8_t> buffer(1024);
    sockaddr_in recv_addr;
    socklen_t size = sizeof(recv_addr);

    api.memory() -> _recv_loop(addr, buffer.memory(), (struct sockaddr *)&recv_addr, &size);

    memcpy((core::int8_t *)data_t, inet_ntoa(recv_addr.sin_addr), strlen(inet_ntoa(recv_addr.sin_addr)));

    data_t = (core::int8_t *)data_t + strlen((core::int8_t *)data_t);
    memcpy((core::int8_t *)data_t, string_char, strlen(string_char));
    data_t = (core::int8_t *)data_t + strlen((core::int8_t *)data_t);
    memcpy((core::int8_t *)data_t, buffer.memory(), buffer.size());
}