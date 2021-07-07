#pragma once
extern int get_variable_mempool(unsigned int id, unsigned int size, void** dst);
extern int free_variable_mempool(unsigned int id, void* dst);
