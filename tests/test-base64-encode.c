#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"


Test(b64_encode_test, b64_all_chars) {
    const char *k = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";
    const char *k_enc = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";

    char *ek = base64_encode(k, strlen(k)+1);

    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", ek, k_enc);

    free(ek);
}


Test(b64_encode_test, b64_all_chars_noplusone) {
    const char *k = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";
    const char *k_enc = "QURGRzQxMyHCoyQlJiYoKC8/XsOnw6kqW10jKS0uLHw8Pis=";

    char *ek = base64_encode(k, strlen(k));

    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", ek, k_enc);

    free(ek);
}


Test(b64_encode_test, b64_rfc4648) {
    const char *k[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};
    const char *k_enc[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};

    for (int i = 0; i < 7; i++) {
        char *ek = base64_encode(k[i], strlen(k[i])+1);
        cr_expect(strcmp(ek, k_enc[i]) == 0, "Expected %s to be equal to %s", ek, k_enc[i]);
        free(ek);
    }
}


Test(b64_encode_test, b64_rfc4648_noplusone) {
    const char *k[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};
    const char *k_enc[] = {"", "Zg==" ,"Zm8=", "Zm9v", "Zm9vYg==" ,"Zm9vYmE=", "Zm9vYmFy"};

    for (int i = 0; i < 7; i++) {
        char *ek = base64_encode(k[i], strlen(k[i]));
        cr_expect(strcmp(ek, k_enc[i]) == 0, "Expected %s to be equal to %s", ek, k_enc[i]);
        free(ek);
    }
}


Test(b64_encode_test, b64_encode_input_exceeded) {
    const char *k = "test";
    size_t len = 65*1024*1024;

    char *ek = base64_encode(k, len);
    cr_expect_null(ek, "%s");
}