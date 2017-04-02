#include <ctype.h>
#include <stdlib.h>
#include "golf.h"

static Array stack;

void init_stack() {
  stack = new_array();
}

void stack_push(Item item) {
  array_push(&stack, item);
}

String next_token(String *str, uint32_t *code_pos) {
  String token = new_string();

  if (*code_pos >= str->length)
    return token;

  char c = str->str_data[*code_pos];
  if (c == '-') {
    string_add_char(&token, c);
    c = str->str_data[++(*code_pos)];
    while (isdigit(c)) {
      string_add_char(&token, c);
      c = str->str_data[++(*code_pos)];
    }
  }
  else if (isdigit(c)) {
    do {
      string_add_char(&token, c);
      c = str->str_data[++(*code_pos)];
    } while (isdigit(c));
  }
  else {
    string_add_char(&token, c);
    *code_pos += 1;
  }

  return token;
}

void execute_string(String *str) {
  uint32_t code_pos = 0;

  while (code_pos < str->length) {
    String tok = next_token(str, &code_pos);
    if (isdigit(tok.str_data[0]) || (tok.str_data[0] == '-' && tok.length > 1))
    {
      stack_push(make_integer(atoll(tok.str_data)));
    }
    free(tok.str_data);
  }
}

void output_final_stack() {
  for (uint32_t i = 0; i < stack.length; i++) {
    output_item(&stack.items[i]);
  }
}
