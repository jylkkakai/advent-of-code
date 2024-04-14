#include <iostream>
#include <openssl/evp.h>

int main() {
  EVP_MD_CTX *mdctx;
  const EVP_MD *md = EVP_md5();
  std::string mess[] = {"abcdef609043", "pqrstuv1048970"};
  std::string base = "bgvyzdsv";
  // std::string mess = "pqrstuv1048970";

  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;
  long long i = 0;
  bool found = false;
  std::string output = "";
  std::string input = "";

  mdctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex2(mdctx, md, NULL);
  while (!found) {

    input = base + std::to_string(i);
    EVP_DigestInit_ex2(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    // EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);

    output.resize(md_len * 2);
    for (unsigned int i = 0; i < md_len; ++i)
      std::sprintf(&output[i * 2], "%02x", md_value[i]);
    // std::cout << output << std::endl;
    if (output.substr(0, 6) == "000000") {
      found = true;
    }
    i++;
  }
  std::cout << input << " " << output << std::endl;
  EVP_MD_CTX_free(mdctx);

  return 0;
}
