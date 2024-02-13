/*
 User Extensions
*/

#include <Keyboard.h>

// Definitions
object *fn_now (object *args, object *env) {
  (void) env;
  static unsigned long Offset;
  unsigned long now = millis()/1000;
  int nargs = listlength(args);

  // Set time
  if (nargs == 3) {
    Offset = (unsigned long)((checkinteger(first(args))*60 + checkinteger(second(args)))*60
      + checkinteger(third(args)) - now);
  } else if (nargs > 0) error2(PSTR("wrong number of arguments"));
  
  // Return time
  unsigned long secs = Offset + now;
  object *seconds = number(secs%60);
  object *minutes = number((secs/60)%60);
  object *hours = number((secs/3600)%24);
  return cons(hours, cons(minutes, cons(seconds, NULL)));
}

object *fn_keyboard_begin (object *args, object *env) {
  (void) env;
  Keyboard.begin();
  return tee;
}

object *fn_keyboard_end (object *args, object *env) {
  (void) env;
  Keyboard.end();
  return tee;
}

object *fn_keyboard_press (object *args, object *env) {
  (void) env;
  return number(Keyboard.press((unsigned int) checkinteger(first(args))));
}

object *fn_keyboard_release (object *args, object *env) {
  (void) env;
  return number(Keyboard.release((unsigned int) checkinteger(first(args))));
}

object *fn_keyboard_release_all (object *args, object *env) {
  (void) env;
  Keyboard.releaseAll();
  return tee;
}

// Symbol names
const char stringnow[] PROGMEM = "now";
const char string_keyboard_begin[] PROGMEM = "keyboard/begin";
const char string_keyboard_end[] PROGMEM = "keyboard/end";
const char string_keyboard_press[] PROGMEM = "keyboard/press";
const char string_keyboard_release[] PROGMEM = "keyboard/release";
const char string_keyboard_release_all[] PROGMEM = "keyboard/release-all";

// Documentation strings
const char docnow[] PROGMEM = "(now [hh mm ss])\n"
"Sets the current time, or with no arguments returns the current time\n"
"as a list of three integers (hh mm ss).";
const char doc_keyboard_begin[] PROGMEM = "(keyboard/begin)\n";
const char doc_keyboard_end[] PROGMEM = "(keyboard/end)\n";
const char doc_keyboard_press[] PROGMEM = "(keyboard/press key)\n";
const char doc_keyboard_release[] PROGMEM = "(keyboard/release key)\n";
const char doc_keyboard_release_all[] PROGMEM = "(keyboard/release-all)\n";

// Symbol lookup table
const tbl_entry_t lookup_table2[] PROGMEM = {
  { stringnow, fn_now, 0203, docnow },
  { string_keyboard_begin, fn_keyboard_begin, 0200, doc_keyboard_begin },
  { string_keyboard_end, fn_keyboard_end, 0200, doc_keyboard_end },
  { string_keyboard_press, fn_keyboard_press, 0211, doc_keyboard_press },
  { string_keyboard_release, fn_keyboard_release, 0211, doc_keyboard_release },
  { string_keyboard_release_all, fn_keyboard_release_all, 0200, doc_keyboard_release_all },
};

// Table cross-reference functions

tbl_entry_t *tables[] = {lookup_table, lookup_table2};
const unsigned int tablesizes[] = { arraysize(lookup_table), arraysize(lookup_table2) };

const tbl_entry_t *table (int n) {
  return tables[n];
}

unsigned int tablesize (int n) {
  return tablesizes[n];
}
