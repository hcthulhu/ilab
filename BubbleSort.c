void BubbleSort (char* text[], int size, int (* cmp_func_ptr)(const char* str1,
                                                              const char* str2)) {
    for (int n = 0; n < size; n++)
      for (int i = 0; i < n; i++)
        if ( cmp_func_ptr (text[i], text[i+1]) < 0)
          swap ( &text[i], &text[i+1]);
}

int strcmpfrrghtsd (const char* strA, const char* strB) {
    int len1 = strlen (strA);
    ...
    return ...;
}

PrintTrig (...... double (* func)(double x) ) {
    for (...x...) {
        y = func(x);
        printf(...y...);
    }
}

PrintTrig(sin);
PrintTrig(cos);
